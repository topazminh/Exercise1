import network
import time

ssid = 'Ten_WiFi'
password = 'Mat_khau'

sta = network.WLAN(network.STA_IF)
sta.active(True)
sta.connect(ssid, password)

print("Đang kết nối WiFi...")
while not sta.isconnected():
    time.sleep(1)
    print(".", end="")

print("\nĐã kết nối WiFi thành công!")
print("Địa chỉ IP:", sta.ifconfig())
