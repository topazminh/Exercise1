#include <WiFi.h>
#include <DNSServer.h>

const char* STA_SSID     = "TEN_MANG_WIFI_CUA_BAN";      // ← thay tên Wi-Fi nhà bạn
const char* STA_PASSWORD = "MAT_KHAU_WIFI_CUA_BAN";       // ← thay mật khẩu

const char* AP_SSID      = "ESP32_Gateway";
const char* AP_PASSWORD  = "12345678";            // mật khẩu AP (tối thiểu 8 ký tự)

IPAddress apIP(192, 168, 4, 1);
IPAddress netMask(255, 255, 255, 0);

DNSServer dnsServer;
const byte DNS_PORT = 53;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== AP + STA Dual Mode (core 3.x) - KHONG BAO 'KHONG CO INTERNET' ===");

  WiFi.mode(WIFI_AP_STA);

  // 1. Kết nối STA lấy Internet (nếu sai pass thì vẫn chạy AP bình thường)
  WiFi.begin(STA_SSID, STA_PASSWORD);
  Serial.print("Dang ket noi WiFi nha ban: ");
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 20) {
    delay(500);
    Serial.print(".");
    count++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nSTA ket noi thanh cong!");
    Serial.print("IP STA: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nKhong ket noi duoc STA (van chay AP binh thuong)");
  }

  // 2. Bật AP
  WiFi.softAPConfig(apIP, apIP, netMask);
  WiFi.softAP(AP_SSID, AP_PASSWORD);
  Serial.println("AP da bat!");
  Serial.print("IP AP : ");
  Serial.println(WiFi.softAPIP());

  // 3. Bật DNS server
  dnsServer.start(DNS_PORT, "*", apIP);   // trả về 192.168.4.1 cho mọi request DNS

  Serial.println("\n=== HOAN TAT! Ket noi dien thoai vao ESP32_Gateway === ");
  Serial.println("   → Sẽ KHÔNG có thông báo 'Không có Internet' nữa!");
}

void loop() {
  dnsServer.processNextRequest();   // quan trọng, phải có dòng này
  Serial.printf("So thiet bi ket noi AP: %d\n", WiFi.softAPgetStationNum());
  delay(5000);
}
