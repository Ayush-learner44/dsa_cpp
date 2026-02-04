Alright. **System Design – Part C** is where the parser’s extracted info is **actually used to make decisions**.
I’ll explain **what Part C is**, **what Fig. 2 shows**, and **the equations**, clean and grounded.

---

## System Design — **Part C: Policy Enforcement Blocks (Ingress Control)**

![Image](https://cdn.prod.website-files.com/6704482c45ef6ead081645ff/67378ff3a22e7755326bb240_67378dff70f0666a04490d79_2.webp)

![Image](https://www.researchgate.net/publication/326364156/figure/fig4/AS%3A680967446462467%401539366699983/P4-based-NDN-packet-control-flow-of-the-ingress-pipeline_Q320.jpg)

![Image](https://www.researchgate.net/publication/399707917/figure/fig1/AS%3A11431281855250137%401768399104562/Five-node-P4-BMv2-testbed-broker-Port-1-telemetry-Port-2-control-Port-3_Q320.jpg)

---

## 1️⃣ What Part C is (one sentence)

> **Part C is the decision engine**: using parsed MQTT metadata and per-client state to **allow, drop, or flag** packets—**all at line rate**, in one pass.

Nothing is parsed here. **Everything here is logic + state.**

---

## 2️⃣ What Fig. 2 shows (how to read it)

Fig. 2 is a **left-to-right flow** of checks inside the **ingress pipeline**.
Think of it as a **checklist** each packet goes through:

```
Client ID → Session check → Topic ACL → Limits/Meter → Anomaly checks → Decision
```

Each box is a table or stateful check. If a packet fails a check, it’s **dropped immediately**.

---

## 3️⃣ Per-client identification (Equation 3)

### Why this exists

The switch needs to remember things **per device** (session open, counters, timers).

### How they do it

They hash the source IP into a small index:

**Equation (3):**

```
idx = srcAddr mod 512
```

### Meaning (plain)

* Take the client’s source IP
* Map it into **one of 512 slots**
* Use that slot to access registers/meters

This keeps memory **bounded and fast**.

---

## 4️⃣ Session-order enforcement (first real check)

### What it checks

* **CONNECT** → opens session
* **PUBLISH without CONNECT** → **DROP (reason 180)**

### How

* A 1-bit register per client:

  ```
  reg_session_open[idx] = 0 or 1
  ```

### Why it matters

Stops:

* Protocol abuse
* Unauthenticated floods
* Broker workload before validation

---

## 5️⃣ Topic-prefix authorization (ACL)

### What it checks

For **PUBLISH only**:

* Does the **topic prefix** (first 16 bytes) match an allowed rule?

### How

* Ternary (TCAM) match on bytes `t0…t15`
* Rules like:

  ```
  device/sensor/* → ALLOW
  device/admin/*  → DENY
  ```

### If no match

→ **DROP**

This enforces **who can publish where** at the edge.

---

## 6️⃣ Per-client protection (two parallel controls)

### A) Soft cap (volume control)

* Counts **PUBLISH messages per client**
* If exceeds `pub_soft_limit` (default 20,000):
  → **DROP (reason 181)**

**Purpose:** stop long-term flooding.

---

### B) Meter (rate control)

* Three-color meter per client:

  * GREEN → allow
  * YELLOW → allow
  * RED → **DROP (reason 150)**

**Purpose:** stop sudden bursts.

---

## 7️⃣ Anomaly detection (behavior checks)

These do **not necessarily drop**—they **flag + clone**.

### A) KeepAlive gap (Equations 4 & 5)

**Equation (4):**

```
Δt = (ingress_ts − reg_last_ka_ts[idx]) / 10^9
```

→ time since last keepalive (seconds)

**Equation (5):**

```
Δt > γ × KeepAlive
```

* `γ` = tolerance (e.g., 1.5)

If violated:

* **Clone to CPU (reason 182)**
* Don’t reset baseline (observe sustained issues)

---

### B) Remaining Length screening

If decoded Remaining Length ≥ threshold **or**
uses ≥3 bytes to encode:

* **Clone (reason 183)**

**Purpose:** detect payload-size DoS patterns early.

---

## 8️⃣ Final action + metadata

Each packet is tagged with:

* **Action:** Forward / Drop / Clone
* **Reason code** (Table III)
* **Rule ID**
* **MQTT context** (type, QoS, topic bytes)

Cloned packets go to the control plane **without slowing the fast path**.

---

## 9️⃣ Why this works (key insight)

* **One pass**
* **No CPU in the decision path**
* **Stateful but bounded**
* **Protocol-aware**

Everything happens **before the broker** sees the packet.

---

## One-paragraph wrap-up

> Part C implements the ingress enforcement logic that turns parsed MQTT metadata into real security actions. Each packet is mapped to a per-client state index, validated for correct session order, authorized against topic-prefix ACLs, checked against per-client volume and rate limits, and screened for behavioral anomalies using KeepAlive timing and Remaining Length heuristics. Based on these checks, packets are forwarded, dropped, or cloned for diagnosis—entirely at line rate and in a single pipeline pass.

If you want, next we can **walk one packet end-to-end through Fig. 2** (normal vs attack) so it fully clicks.
