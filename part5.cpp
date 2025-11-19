#include <WiFi.h>

void print_wifi_status() {
  Serial.println("--- Wi-Fi Status ---");
  Serial.print("Connection Status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("CONNECTED");
    Serial.print("IP: "); Serial.println(WiFi.localIP());
    Serial.print("SSID: "); Serial.println(WiFi.SSID());
    Serial.print(" RSSI (Signal Strength): "); 
    Serial.print(WiFi.RSSI()); Serial.println(" dBm"); // RSSI
    Serial.print(" MAC Address: "); 
    Serial.println(WiFi.macAddress()); // MAC
  } else {
    Serial.println("DISCONNECTED");
  }
  Serial.println("--------------------");
}

void scan_networks() {
  Serial.println("--- 1. Scan mang Wi-Fi ---");
  // Lấy danh sách mạng Wi-Fi
  int n = WiFi.scanNetworks(); 
  
  if (n == 0) {
    Serial.println("Khong tim thay mang nao!");
  } else {
    Serial.print(n);
    Serial.println(" mang tim thay:");
    for (int i = 0; i < n; ++i) {
      // In SSID và RSSI
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm)");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?"":"*"); // Có mật khẩu
      delay(10);
    }
  }
  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- 5. Thao tac nang cao ---");
  
  // Bắt đầu chế độ STA để có thể có RSSI và MAC khi kết nối
  WiFi.mode(WIFI_STA); 
  WiFi.begin("TEN_WIFI_CUA_BAN", "MAT_KHAU");
  // Bạn có thể thêm WiFi.begin(SSID, PASS) ở đây nếu muốn kiểm tra status khi đã kết nối
}

void loop() {
  // Scan mạng mỗi 20 giây
  static unsigned long lastScanTime = 0;
  if (millis() - lastScanTime > 20000) {
    scan_networks();
    lastScanTime = millis();
  }
  
  // Hiển thị status mỗi 5 giây (chức năng WiFi reconnect được tích hợp trong WiFi.begin()
  // nếu bạn sử dụng nó để kết nối)
  static unsigned long lastStatusTime = 0;
  if (millis() - lastStatusTime > 5000) {
    print_wifi_status();
    lastStatusTime = millis();
  }
  
  delay(100);
}
