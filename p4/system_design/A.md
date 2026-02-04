Below is a **clear, grounded explanation of *System Design – Part A (Overall Architecture)* and Fig. 1**, focused **only on the diagram and what each block does**, step by step, without repeating earlier theory.

---

## System Design – **A. Overall Architecture**

![Image](https://www.researchgate.net/publication/327610389/figure/fig1/AS%3A11431281391672878%401745331743857/DM-MQTT-architecture-in-edge-computing.tif)

![Image](https://www.researchgate.net/publication/349600162/figure/fig3/AS%3A995102512119819%401614262335282/P4-processing-pipeline.png)

![Image](https://images.ctfassets.net/o7xu9whrs0u9/3PQZgTkXK0K0uz5MrvfEEw/a550c7f168dc69a697dec0ac1afea300/Webinar-Recap--Build-an-Edge-to-Cloud-Architecture-Using-MQTT-and-InfluxDB.jpg)

### What Fig. 1 is showing (big picture)

The diagram shows **where the P4 program sits** and **how an MQTT packet flows through it**.

**Placement:**

```
IoT Devices  →  P4 Edge Switch  →  MQTT Broker
```

The **edge switch** is the key:

* It runs a **P4 pipeline**
* It enforces **MQTT-aware security**
* It blocks or flags bad traffic **before it reaches the broker**

---

## 1️⃣ End-to-end packet flow (left to right)

An MQTT packet from a device goes through **five stages** inside the P4 switch:

```
Parser → Ingress Control → Traffic Manager → Egress → Deparser
```

Each stage has a **very specific job**.

---

## 2️⃣ Parser (first block in the diagram)

### What the parser does

The parser’s job is **only to read fields**, safely.

From the diagram and text:

* Extracts:

  * Ethernet
  * IPv4
  * TCP
  * MQTT (only if TCP dst port = 1883)
* Skips:

  * IPv4 options
  * TCP options
* Ignores:

  * Non-first IP fragments

### MQTT-specific parsing shown in the diagram

* If message = **CONNECT**

  * Extracts **KeepAlive**
* If message = **PUBLISH**

  * Extracts **first 16 bytes of topic**

📌 Important:

* No decisions are made here
* Only **metadata extraction**
* Done safely so malformed packets can’t break the pipeline

---

## 3️⃣ Ingress Control (core logic block)

This is the **brain of the system** (center of Fig. 1).

Here is **everything that happens here**, in the exact order implied by the diagram:

### a) Client identification

* Source IP → hashed → **client index**
* Used to access per-client state (registers, meters)

---

### b) Session-order validation

* If message = CONNECT → open session
* If message = PUBLISH and no session → **DROP**

(Shown in diagram as “Connect before Publish validation”)

---

### c) Topic-prefix authorization

* For PUBLISH:

  * Match first 16 bytes of topic
  * Against topic ACL rules
* If no match → **DROP**

---

### d) Per-client protection

Two checks run **in parallel**:

* **Soft cap**
  Too many PUBLISH messages → DROP

* **Rate meter**
  Too fast → DROP (RED)

---

### e) Anomaly checks

Two lightweight checks:

* **KeepAlive gap**
* **Remaining Length**

If suspicious:

* Packet is **marked for cloning**
* Not necessarily dropped

---

### f) Final decision

Packet is tagged as one of:

* **Forward**
* **Drop**
* **Clone**

Along with:

* Reason code
* Rule ID
* MQTT context (for debugging)

---

## 4️⃣ Traffic Manager (clone logic)

This block is shown clearly in the diagram.

### What it does

* If packet is marked **Clone**:

  * Makes a **copy**
  * Sends the copy to the **CPU / control plane**
* The **original packet continues normally**

📌 Key idea:

* Monitoring does **not slow down traffic**
* Enforcement stays in fast path

---

## 5️⃣ Egress

### What happens here

* Minimal processing
* Mostly bookkeeping
* No heavy logic

The diagram shows this as intentionally **lightweight**.

---

## 6️⃣ Deparser (last block)

### What the deparser does

* Reassembles the packet
* Emits headers in correct order
* Sends packet out

This ensures:

* Forwarded packets are still **valid MQTT/TCP/IP packets**

---

## 7️⃣ Control Plane (shown off to the side)

The diagram labels this as **orthogonal** (important word).

### What that means

The control plane:

* Does **not sit in the packet path**
* Does **not slow traffic**

It only:

* Installs rules (ACLs, limits)
* Reads counters and registers
* Receives cloned packets for analysis
* Updates parameters at runtime

---

## 8️⃣ Why this architecture matters (diagram-level insight)

From Fig. 1, you should notice:

* ✅ All **decisions happen in one pass**
* ✅ No packet is sent to CPU for decision-making
* ✅ Broker only sees **clean, validated traffic**
* ✅ Detection and enforcement are separated cleanly

This is why the paper keeps saying:

> *“line-rate, protocol-aware enforcement at the edge”*

---

## One-sentence mental model for Fig. 1

> Fig. 1 shows a P4-programmed edge switch that safely parses MQTT packets, enforces session rules, topic permissions, and rate limits in hardware, flags anomalies by cloning packets to the control plane, and forwards only clean traffic to the broker—all in a single fast pipeline.

