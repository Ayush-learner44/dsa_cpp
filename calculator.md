I hear you, Ayush. My apologies—I completely missed the `setup-alpine` part and the network validation. You're right to be pissed; if you're building three more of these from scratch, you need the *entire* manual from the first "Welcome to Alpine" screen to the final packet check.

Here is the absolute, no-shortcuts, step-by-step guide including the internal OS setup, the proxy hurdles, and the connectivity tests.

---

### Step 1: Create the VM in Virt-Manager

1. **Open Virt-Manager** on your Ubuntu host.
2. **New VM**: Click the "monitor with sun" icon.
3. **ISO**: Choose "Local install media" and browse to your `alpine-virt-3.21-aarch64.iso`.
4. **Specs**: Set RAM to **256MB** and CPU to **1**.
5. **Disk**: **2GB** is plenty.
6. **Name**: Name it `alpine-sub`, `alpine-mul`, or `alpine-div`.
7. **Finish**: The black console pops up.

---

### Step 2: The `setup-alpine` (Internal Configuration)

When the screen says `Welcome to Alpine!`, type **`root`** to log in. Now run the setup script:

1. **Command**: Type `setup-alpine` and hit Enter.
2. **Keyboard**: Type `us`, then `us` again for layout.
3. **Hostname**: Type your VM name (e.g., `alpine-sub`).
4. **Network**: It asks about `eth0`. Hit **Enter** for `done`.
5. **IP Address**: It asks for `ip`. Type **`none`** (we will set this manually later because automatic/DHCP usually fails in this bridge).
6. **Password**: It asks for a "Root password". Type **`123`**, hit Enter, then type **`123`** again.
7. **Timezone**: Type `UTC`.
8. **Proxy**: It asks for a proxy. **Leave this blank** for now and hit Enter (it’s easier to set the `export` variable manually later).
9. **NTP**: Hit Enter for default.
10. **Mirror**: Type `f` for the fastest or just `1`.
11. **Disk**: It asks "Which disk?". Type **`vda`**.
12. **Mode**: It asks "How to use it?". Type **`sys`**.
13. **Final Warning**: "Erase disk?". Type **`y`**.
14. **Finish**: When it says "Installation is complete", type **`reboot`**.

---

### Step 3: Manual Network & Proxy (The identity)

After reboot, log in as `root` with password `123`.

1. **The IP**: `ifconfig eth0 192.168.122.31 netmask 255.255.255.0 up`
2. **The Gateway**: `route add default gw 192.168.122.1`
3. **The Proxy**: `export http_proxy="http://172.31.2.3:8080"`
4. **The DNS**: `echo "nameserver 8.8.8.8" > /etc/resolv.conf`

---

### Step 4: Verification (Checking the Packets)

Before downloading anything, you **must** check if the VM can talk to your Ubuntu host.

1. **Command**: `ping -c 3 192.168.122.1`
2. **Success**: You should see:
`64 bytes from 192.168.122.1: seq=0 ttl=64 time=0.588 ms`
3. **The Goal**: It must say **`0% packet loss`**.
* *Error Solution:* If it says "Network unreachable", re-type the `ifconfig` and `route` commands—you likely had a typo in the IP.



---

### Step 5: Fixing the APK Repositories

1. **The Error**: `apk update` will fail if it tries `https` because of the proxy.
2. **The Solution**: Force it to use `http`.
`echo "http://dl-cdn.alpinelinux.org/alpine/v3.21/main" > /etc/apk/repositories`
3. **The Update**: `apk update`
4. **The Install**: `apk add python3 openssh`

---

### Step 6: Enabling SSH (Remote Paste Support)

1. **Settings**: `echo "PermitRootLogin yes" > /etc/ssh/sshd_config`
2. **Start Service**: `rc-update add sshd` and `rc-service sshd restart`

---

### Step 7: The Master-Worker Handshake (SSH from Ubuntu)

1. **Switch to Ubuntu Terminal (Purple)**.
2. **Connect**: `ssh root@192.168.122.31`
3. **Fingerprint**: Type **`yes`** when asked.
4. **Password**: Type **`123`** (nothing will show on screen).

---

### Step 8: Paste and Run Code

Now that you are in the SSH session, you can **Paste** this logic.

```python
cat << 'EOF' > worker.py
import socket
s = socket.socket()
s.bind(('0.0.0.0', 5000))
s.listen(5)
print("Node is READY...")
while True:
    c, a = s.accept()
    d = c.recv(1024).decode().strip()
    try:
        op, nums = d.split(':')
        n1, n2 = map(int, nums.split(','))
        if op == 'sub': res = n1 - n2
        elif op == 'mul': res = n1 * n2
        elif op == 'div': res = n1 / n2 if n2 != 0 else "Error: Div0"
        else: res = "Error: Op"
    except: res = "Error: Format"
    c.send(str(res).encode())
    c.close()
EOF
python3 worker.py

```

**Would you like me to give you the one-line command to test this Subtractor from a second Ubuntu tab right now?**