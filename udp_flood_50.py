# -*- coding: utf-8 -*-
import socket
import time
import threading

# Configuration
UDP_IP = "192.168.1.2"
UDP_PORT = 12345
MESSAGE = b"A" * 1350
THREAD_COUNT = 50
TOS_VALUE = 0x10  # ToS 값을 0x20으로 설정

# Function to send packets
def send_packets():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_TOS, TOS_VALUE)  # ToS 설정
    try:
        while True:
            sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
    finally:
        sock.close()

# Start multiple threads to send packets simultaneously
threads = []
for _ in range(THREAD_COUNT):
    t = threading.Thread(target=send_packets)
    t.start()
    threads.append(t)

# Wait for all threads to finish (in this case, they won't finish as they are in infinite loops)
for t in threads:
    t.join()
