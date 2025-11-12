# a) TCP Server
import network, socket

ssid = 'ESP32_AP'
password = '12345678'

ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=ssid, password=password)

addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)
print("TCP Server đang chờ kết nối tại:", addr)

while True:
    cl, addr = s.accept()
    print('Kết nối từ', addr)
    cl.send('Hello from ESP32!')
    cl.close()

# b) UDP ví dụ
import socket

udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp.bind(('0.0.0.0', 8888))
print("UDP Server sẵn sàng nhận gói tin...")

while True:
    data, addr = udp.recvfrom(1024)
    print("Nhận từ", addr, ":", data)
    udp.sendto(b'ESP32 da nhan duoc!', addr)
