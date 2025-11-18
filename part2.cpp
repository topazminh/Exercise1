#include <WiFi.h>

// --- Cấu hình ---
const char* AP_SSID = "ESP32_Access_Point";
const char* AP_PASSWORD = "esp32password"; // Tối thiểu 8 ký tự
IPAddress localIP(192, 168, 4, 1); // IP mặc định cho AP mode

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- 2. Wi-Fi Access Point (AP Mode) ---");

  // Thiết lập IP tĩnh cho AP
  if (!WiFi.softAPConfig(localIP, localIP, IPAddress(255, 255, 255, 0))) {
    Serial.println(" AP Config failed!");
    return;
  }

  // Cấu hình ESP32 phát Wi-Fi AP riêng (SSID/PASS)
  if (WiFi.softAP(AP_SSID, AP_PASSWORD)) {
    Serial.println(" AP da bat!");
    Serial.print(" SSID: ");
    Serial.println(AP_SSID);
    Serial.print(" IP Address: ");
    Serial.println(WiFi.softAPIP()); // Địa chỉ IP mặc định (192.168.4.1)
  } else {
    Serial.println(" AP failed!");
  }
}

void loop() {
  // Kiểm tra số lượng client đã kết nối (Kiểm tra chức năng)
  int clientCount = WiFi.softAPgetStationNum(); 
  if (clientCount > 0) {
    Serial.print(" So luong client ket noi: ");
    Serial.println(clientCount);
  }
  delay(5000);
}
