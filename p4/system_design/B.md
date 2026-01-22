Alright. Deep breath.
Now that the **MQTT + TCP + edge confusion is cleared**, **System Design – Part B** will finally make sense.

I’ll do **exactly this**:

1. Explain **what Part B is responsible for**
2. Explain the **diagram logic**
3. Explain **each equation** and **why it exists**
4. Tie everything back to **“what problem it prevents”**

No repetition of earlier stuff.

---

# SYSTEM DESIGN — **Part B**

## **Protocol-Aware Parser and Header Extraction**

![Image](https://www.researchgate.net/publication/353837052/figure/fig3/AS%3A1055795508678656%401628732673434/Pipeline-of-the-P4-programmable-switch-supporting-VNFs-deployment-For-the-sake-of.jpg)

![Image](https://us1.discourse-cdn.com/flex019/uploads/p4/optimized/1X/fa40792677c05ed2f7a1121d3889e14cc07b077c_2_517x217.png)

![Image](https://miro.medium.com/v2/resize%3Afit%3A1200/1%2Agi8p36C9_EYKPWhlnnS3GA.png)

---

## 1️⃣ What Part B is doing (ONE sentence)

> Part B explains how the P4 switch **safely reads (parses) MQTT packets** without crashing, looping, or being tricked—before any security decision is made.

This is **purely about reading bytes correctly**.

---

## 2️⃣ Why parsing is a BIG DEAL (context)

Remember:

* Switch parser is **hardware**
* No loops
* No dynamic memory
* No “try–catch”

If parsing goes wrong:

* Pipeline stalls
* Packet drops
* Or switch crashes

Attackers **love** parser bugs.

So Part B = **defensive parsing**.

---

## 3️⃣ What the parser extracts (from the diagram)

From the diagram + text, the parser reads headers **in this order**:

```
Ethernet → IPv4 → TCP → MQTT
```

But **ONLY if safe to do so**.

---

## 4️⃣ IPv4 parsing + Equation (1)

### Problem

IPv4 header is **not fixed size**.

* Minimum: 20 bytes
* Can include **options**

### Field involved

```
IHL = Internet Header Length
```

* IHL = number of 32-bit words
* Normal IHL = 5 (5 × 4 = 20 bytes)

---

### Equation (1)

```
opt_len_IPv4 = (IHL − 5) × 4 bytes
```

### Meaning (simple)

* If IHL > 5 → options exist
* Skip exactly that many bytes
* Don’t try to parse them

### Why this matters

* Prevents malformed IPv4 options from breaking the parser
* Avoids allocating fixed-size option headers

---

## 5️⃣ TCP parsing + Equation (2)

### Problem

TCP header is ALSO variable-length.

### Field involved

```
doff = Data Offset
```

* doff = number of 32-bit words
* Normal doff = 5 (20 bytes)

---

### Equation (2)

```
opt_len_TCP = (doff − 5) × 4 bytes
```

### Meaning

* If TCP options exist → skip them safely
* Do not inspect TCP options

### Why this matters

TCP option abuse is a **classic evasion trick**.

---

## 6️⃣ Fragment filtering (VERY important)

### The rule

```
Only parse packets where fragOffset = 0
```

### Meaning

* Only first IP fragment is allowed
* All other fragments are ignored for MQTT parsing

### Why?

MQTT headers split across fragments = **evasion attack**

Attacker could:

* Hide MQTT type
* Confuse parser
* Bypass checks

So:

> **No first fragment → no MQTT parsing**

---

## 7️⃣ MQTT fixed header parsing

Once TCP is safe and complete:

### MQTT fixed header fields extracted:

* **Type** (CONNECT, PUBLISH, etc.)
* **Flags**
* **Remaining Length (first two bytes)**

---

## 8️⃣ Remaining Length early check (DoS defense)

### What they do

They read:

```
rl_b0, rl_b1
```

If:

```
rl_b1 == 1
```

→ Remaining Length uses **≥3 bytes**

### Why this matters

* Multi-byte Remaining Length = very large payload
* Classic broker DoS vector

⚠️ They **do not drop yet**
They just **flag it**.

---

## 9️⃣ CONNECT parsing (special case)

If MQTT type = CONNECT:

Parser extracts:

* Protocol name length
* Skips protocol name
* Reads:

  * Protocol level
  * Flags
  * **KeepAlive (2 bytes)**

### Why only KeepAlive?

Because:

* Used later for anomaly detection
* No need to parse everything else

---

## 🔟 PUBLISH parsing (topic slicing)

This is the **most important parser trick**.

### Problem

Topic strings are:

* Variable length
* Potentially huge
* Impossible to fully parse in hardware

---

### Solution

1. Read topic length
2. Extract **only first 16 bytes**

   ```
   t0, t1, t2, … t15
   ```
3. Skip the rest

### Why 16 bytes?

* Enough to represent topic **prefix**
* Bounded memory
* Works with TCAM (ACL tables)

This enables **topic authorization later**.

---

## 1️⃣1️⃣ Why this parser is called “parser-safe”

Because it:

* Never loops
* Never allocates variable memory
* Never trusts length fields blindly
* Never follows fragments

So:

> Malformed packets cannot crash or confuse it

---

## 1️⃣2️⃣ How this connects to the next stage

The parser **does NOT decide anything**.

It only:

* Extracts metadata
* Sets flags

This metadata is then used by **Ingress Control (Part C)**.

---

## 1️⃣3️⃣ Mental model (THIS IS IMPORTANT)

Think of the parser as:

> “A bouncer who only checks IDs and writes notes—he doesn’t decide who gets in.”

Ingress Control decides.

---

## ONE-SHOT SUMMARY (lock this in)

> System Design Part B describes a hardware-safe parser that carefully skips variable-length IPv4 and TCP options (Equations 1 and 2), ignores fragmented packets, extracts only critical MQTT fields like message type, KeepAlive, Remaining Length, and the first 16 bytes of the topic, and flags suspicious packets early—ensuring the switch can understand MQTT without being crashed or evaded.

---

If you’re ready, **Part C (Ingress Control + Fig. 2)** is where:

* Session validation
* Topic ACL
* Rate limiting
* Anomaly detection

**actually happen**.

Say the word and we continue.

doubt...Prevents malformed IPv4 options from breaking the parser..TCP header is ALSO variable-length.TCP option abuse is a classic evasion trick. Remaining Length uses ≥3 bytes