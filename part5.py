import network

sta = network.WLAN(network.STA_IF)
sta.active(True)

# Quét mạng WiFi
print("Các mạng WiFi xung quanh:")
for wifi in sta.scan():
    print("SSID:", wifi[0].decode(), " - RSSI:", wifi[3])

# Thông tin WiFi hiện tại
if sta.isconnected():
    print("\nWiFi đang kết nối:")
    print("IP:", sta.ifconfig()[0])
    print("MAC:", sta.config('mac'))
else:
    print("\nChưa kết nối WiFi.")
