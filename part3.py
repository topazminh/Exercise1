import network
import time

# Kết nối WiFi bên ngoài (Station)
sta = network.WLAN(network.STA_IF)
sta.active(True)
sta.connect('Ten_WiFi', 'Mat_khau')

# Tạo WiFi riêng (AP)
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid='ESP32_AP', password='12345678')

while not sta.isconnected():
    time.sleep(1)
    print(".", end="")

print("\nKết nối thành công!")
print("IP STA:", sta.ifconfig())
print("IP AP :", ap.ifconfig())
