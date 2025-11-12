import network

ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid='ESP32_AP', password='12345678')

print("WiFi AP đang phát...")
print("Địa chỉ IP:", ap.ifconfig())
