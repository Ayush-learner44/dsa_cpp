I understand. When you're looking at bits and bytes, words just aren't enough. You need to see the "containers."

The P4 switch in this paper is basically a high-speed surgeon. It cuts through the **Ethernet**, **IP**, and **TCP** headers to get to the **MQTT** packet inside.

Here are the 3 critical MQTT packets visualized byte-by-byte.

---

### 1. The CONNECT Packet (The "Login" Message)

This is what the client sends to start a session. The switch looks at this to "open" the session in its memory.

```text
       0      1      2      3      4      5      6      7
    +------+------+------+------+------+------+------+------+
    | TYPE | FLAGS|         REMAINING LENGTH                | <- FIXED HEADER
    | (1)  | (0)  |            (Byte 1-4)                   [cite_start]| [cite: 130]
    +------+------+------+------+------+------+------+------+
    |      PROTOCOL NAME LENGTH (2) |   "MQTT" string (4)   | <- VARIABLE
    +------+------+------+------+------+------+------+------+    HEADER
    | LEVEL| FLAGS|       [cite_start]KEEPALIVE TIMER (2)               | [cite: 132]
    +------+------+------+------+------+------+------+------+
    |      CLIENT ID LENGTH (2)     |   CLIENT ID (Var)     | <- PAYLOAD
    [cite_start]+------+------+------+------+------+------+------+------+ [cite: 132]

```

* 
**What the P4 Switch does:** It grabs the **KeepAlive** value (2 bytes) and stores it in a register linked to your IP.


* 
**The "Session Open" Flag:** It sets a bit in its memory from `0` to `1` for your IP address.



---

### 2. The PUBLISH Packet (The "Data" Message)

This is what a hacker tries to send *without* connecting. This is also where your actual temperature data lives.

```text
       0      1      2      3      4      5      6      7
    +------+------+------+------+------+------+------+------+
    | TYPE | FLAGS|         REMAINING LENGTH                | <- FIXED HEADER
    | (3)  | (Var)|            (Byte 1-4)                   [cite_start]| [cite: 130]
    +------+------+------+------+------+------+------+------+
    |      TOPIC NAME LENGTH (2)    |  TOPIC NAME (Var)     | <- VARIABLE
    |                               | (Switch reads first16)|    HEADER
    [cite_start]+------+------+------+------+------+------+------+------+ [cite: 133, 148]
    |      PACKET ID (2) *Only if QoS > 0                   | 
    +------+------+------+------+------+------+------+------+
    |                                                       | <- PAYLOAD
    |              ACTUAL DATA (Temperature, etc.)          | (The "Thing")
    |                                                       |
    +------+------+------+------+------+------+------+------+

```

* 
**The Switch Logic:** It sees **Type 3** (Publish). It immediately checks: *"Is the session flag for this IP set to 1?"*.


* **The Topic Check:** It looks at the **Topic Name**. The P4 switch in this paper extracts only the **first 16 bytes** ( to ) to see if you are allowed to post to that topic.


* 
**The Drop:** If the session flag is `0` OR the topic is not on your allowed list, the switch **Drops** the packet before it even reads the Payload.



---

### 3. The CONNACK Packet (The "Acknowledge" Message)

This is sent by the **Broker** back to the **Client** to say "You are logged in".

```text
       0      1      2      3      4      5      6      7
    +------+------+------+------+------+------+------+------+
    | TYPE | FLAGS|       REMAINING LENGTH (Always 2)       | <- FIXED HEADER
    | (2)  | (0)  |                                         |
    +------+------+------+------+------+------+------+------+
    | FLAGS (Reserved)   |   RETURN CODE (0 = Success)      | <- VARIABLE
    +------+------+------+------+------+------+------+------+    HEADER
                                                              (NO PAYLOAD)

```

---

### How the Switch "Skips" and "Processes"

When the packet hits the switch, the P4 **Parser** follows these steps:

1. 
**Skip Ethernet:** Move the pointer 14 bytes.


2. 
**Read IP Header:** Read the **IHL** (Internet Header Length). If it's `5`, move 20 bytes. If it's more, skip the "Options" bytes.


3. 
**Read TCP Header:** Read the **Data Offset**. If it's `5`, move 20 bytes.


4. 
**The Target:** The pointer is now exactly at **MQTT Byte 0**.


5. 
**The Decision:** * Read 4 bits: **Type**.


* If Type = 1: Go to **CONNECT** processing.


* If Type = 3: Go to **PUBLISH** processing.





This is how it handles "Variable Length" headers. It doesn't guess; it reads the "Length" fields in the IP and TCP headers and jumps exactly that many bytes to find the MQTT start point.

Would you like me to show you the **Access Control List (ACL)** diagram to see how it matches those 16 bytes of the Topic Name?