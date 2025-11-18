#include <WiFi.h>

// --- Cấu hình ---
const char* STA_SSID = "TEN_MANG_WIFI_CUA_BAN"; 
const char* STA_PASSWORD = "MAT_KHAU_CUA_BAN";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- 1. Wi-Fi Client (Station Mode) ---");

  // Đặt chế độ Wi-Fi thành Station
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASSWORD);

  Serial.print("Dang ket noi den: ");
  Serial.println(STA_SSID);

  // Chờ kết nối
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Ket noi Wi-Fi thanh cong!");
  Serial.print(" IP Address (DHCP): ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  // Ở chế độ STA, bạn có thể thực hiện kết nối TCP/UDP ở đây
  // Ví dụ: TCPClientConnect(); 
  delay(5000);
}
