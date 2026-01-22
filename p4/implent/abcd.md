Got it. I’ll explain **the Implementation section** **cleanly**, **concretely**, and **only what’s new there**—no re-teaching design logic.

---

## Implementation (What they actually built)

![Image](https://build-a-router-instructors.github.io/images/V1Model.png)

![Image](https://www.researchgate.net/publication/399707917/figure/fig1/AS%3A11431281855250137%401768399104562/Five-node-P4-BMv2-testbed-broker-Port-1-telemetry-Port-2-control-Port-3.png)

![Image](https://www.researchgate.net/publication/343586922/figure/fig2/AS%3A932608674394113%401599362643965/Mininet-Network-Topology.jpg)

---

## 1️⃣ What “implementation” means here

This section answers one question:

> **How did they turn the design (parser + ingress logic) into a working system that can be tested?**

So it covers:

* Tools
* Code structure
* Runtime configuration
* Testbed setup

---

## 2️⃣ P4 program structure (what files do)

They implemented **one P4 program** with these logical parts:

### a) Parser

* Implements **System Design Part B**
* Safe extraction:

  * IPv4 / TCP
  * MQTT type
  * KeepAlive
  * Remaining Length
  * First 16 bytes of topic

### b) Ingress control

* Implements **System Design Part C**
* Tables + registers + meters:

  * Session validation
  * Topic ACL
  * Soft cap
  * Rate limiting
  * Anomaly flags

### c) Egress + Deparser

* Minimal logic
* Rebuild packet
* Forward / drop / clone

No magic here—just clean separation.

---

## 3️⃣ Why they use **BMv2**

### What BMv2 is

* **BMv2 = Behavioral Model v2**
* A **software implementation of a P4 switch**
* Runs on CPU
* Behaves like real P4 hardware (logically)

### Why they chose it

* Real P4 hardware is:

  * Expensive
  * Hard to get
* BMv2 is:

  * Standard for research
  * Deterministic
  * Supported by Mininet

📌 Important:
They are **not claiming hardware speed here**—only **functional correctness and scalability trends**.

---

## 4️⃣ Mininet testbed (how everything is connected)

### What Mininet does

* Emulates a full network on one machine:

  * Hosts
  * Switches
  * Links

### Their topology (simple)

```
IoT Clients ──► BMv2 P4 Switch ──► MQTT Broker
```

* Clients:

  * Legit sensors
  * Malicious clients
* Broker:

  * Standard MQTT broker (e.g., Mosquitto)

All traffic **must pass through the P4 switch**.

---

## 5️⃣ Control plane implementation

### What the control plane does (and does NOT do)

✅ Does:

* Install topic ACL rules
* Set rate limits and soft caps
* Read counters and registers
* Receive cloned anomaly packets

❌ Does NOT:

* Inspect packets inline
* Decide forwarding
* Add latency

### How it’s implemented

* Python scripts using P4Runtime / Thrift
* Periodic polling (not per packet)

---

## 6️⃣ How per-client state is implemented

### Registers

Used for:

* `session_open`
* `publish_counter`
* `last_keepalive_timestamp`

Indexed by:

```
idx = srcIP mod 512
```

This keeps:

* Memory bounded
* Lookup O(1)

---

## 7️⃣ Meters (rate limiting)

* One **meter per client index**
* Configured with:

  * CIR (committed rate)
  * CBS (burst size)

Returns:

* GREEN / YELLOW / RED

RED ⇒ packet dropped immediately.

---

## 8️⃣ Soft cap implementation

* Simple register counter:

  ```
  publish_counter[idx]++
  ```
* Compared against:

  ```
  pub_soft_limit
  ```
* If exceeded:

  * Packet dropped
  * Counter not reset automatically

This is **volume-based**, not time-based.

---

## 9️⃣ Clone-to-CPU implementation

When anomaly detected:

* Packet is **cloned**
* Metadata attached:

  * Reason code
  * MQTT type
  * Client index

Original packet:

* Still forwarded (unless policy says drop)

This allows:

* Debugging
* Forensics
* Policy tuning

---

## 🔟 Why this implementation is realistic

The authors emphasize:

* No unbounded loops
* No variable memory allocation
* No string processing
* No heavy computation

Which means:

> The same design can run on **real P4 hardware** with minor adjustments.

---

## One-paragraph summary (lock this in)

> The implementation realizes the proposed MQTT-aware security pipeline as a single P4 program running on a BMv2 software switch within a Mininet testbed. The parser and ingress logic directly implement the design’s safe extraction, session validation, topic authorization, rate limiting, and anomaly detection using registers, meters, and tables. A lightweight control plane configures policies and receives cloned diagnostic packets, while all enforcement decisions remain in the data plane. This setup demonstrates functional correctness and feasibility under realistic IoT traffic patterns.

If you want next, the **Evaluation section** is where they prove this thing actually works (accuracy, kpps, latency).


Alright. **System Design – Part D** only.
Short, clean, no repetition.

---

# System Design — **Part D: Control Plane Interaction & Runtime Adaptation**

## What Part D is about (one line)

> **Part D explains how the P4 data plane is configured, monitored, and adjusted at runtime—without touching packet forwarding speed.**

This section is **NOT about packet logic**.
It’s about **management and visibility**.

---

## 1️⃣ Why a Control Plane is needed at all

The **data plane**:

* Drops / forwards packets
* Must be fast
* Must not run heavy logic

The **control plane** exists to:

* Install rules
* Read statistics
* React to alerts
* Tune thresholds

Think:

> Data plane = muscles
> Control plane = brain (slow, strategic)

---

## 2️⃣ What the control plane DOES

### A) Policy installation

It programs:

* Topic ACL rules
* Rate limits (meters)
* Soft-cap thresholds
* KeepAlive tolerance (γ)

This happens:

* At startup
* Or dynamically
* NOT per packet

---

### B) Reading state (telemetry)

It periodically reads:

* Counters
* Registers
* Meter stats

Used for:

* Monitoring device behavior
* Detecting misbehaving clients
* System health checks

---

### C) Receiving anomaly packets (clone-to-CPU)

From Part C:

* Suspicious packets are **cloned**
* Sent to control plane

Control plane can:

* Log them
* Analyze patterns
* Decide future policy changes

Important:

* The original packet path is **not blocked**
* No latency added to normal traffic

---

## 3️⃣ What the control plane does **NOT** do

❌ It does NOT:

* Inspect every packet
* Decide forward/drop in real time
* Sit in the data path
* Add latency

All enforcement decisions are still **100% in the data plane**.

---

## 4️⃣ Runtime adaptation (why Part D matters)

Because of the control plane:

* Thresholds can be changed **without recompiling P4**
* Policies can adapt to:

  * Traffic surges
  * New devices
  * Observed anomalies

Example:

* See many Remaining Length alerts
* Lower allowed threshold
* Push new config to switch

---

## 5️⃣ Why this design is scalable

* Data plane stays simple and fast
* Control plane work scales with **events**, not packets
* No bottleneck at high traffic rates

This avoids:

* CPU-bound firewalls
* Centralized SDN latency

---

## One-paragraph summary (lock this in)

> System Design Part D describes the control-plane mechanisms that configure and observe the P4-based MQTT security pipeline without participating in per-packet processing. The control plane installs topic ACLs, rate limits, and anomaly thresholds, periodically reads stateful statistics, and receives cloned packets flagged as suspicious. This separation allows the data plane to enforce security at line rate while enabling runtime policy adaptation and diagnostics without impacting forwarding performance.

That’s **D**.
Next logical step (only if you want): **Evaluation** — where they prove all this actually works.
