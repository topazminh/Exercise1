#include <WiFi.h>

// --- Cấu hình ---
// STA
const char* STA_SSID = "TEN_MANG_WIFI_CUA_BAN"; 
const char* STA_PASSWORD = "MAT_KHAU_CUA_BAN";
// AP
const char* AP_SSID = "ESP32_Gateway";
const char* AP_PASSWORD = "dualmode_pass"; 
IPAddress localIP(192, 168, 4, 1);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- 3. AP + STA (Dual Mode) ---");

  // Đặt chế độ kết hợp
  WiFi.mode(WIFI_AP_STA); 

  // 1. Cấu hình STA (Kết nối đến Router)
  WiFi.begin(STA_SSID, STA_PASSWORD);
  Serial.print("Dang ket noi STA den: ");
  Serial.println(STA_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("c"); // c - client
  }
  Serial.println("\n Ket noi STA thanh cong!");
  Serial.print(" STA IP: ");
  Serial.println(WiFi.localIP()); // IP nhận từ Router

  // 2. Cấu hình AP (Phát mạng riêng)
  if (!WiFi.softAPConfig(localIP, localIP, IPAddress(255, 255, 255, 0))) {
    Serial.println(" AP Config failed!");
    return;
  }
  
  if (WiFi.softAP(AP_SSID, AP_PASSWORD)) {
    Serial.println(" AP da bat!");
    Serial.print(" AP IP: ");
    Serial.println(WiFi.softAPIP()); // IP của AP (192.168.4.1)
  } else {
    Serial.println(" AP failed!");
  }
}

void loop() {
  // Có thể kiểm tra trạng thái kết nối và client count ở đây
  delay(5000);
}
