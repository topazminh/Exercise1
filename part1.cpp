#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "TEN_WIFI_CUA_BAN";     //tự nhập 
const char* password = "MAT_KHAU_WIFI";        //tự nhập 

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n=== BAI TAP 1: ESP32 WiFi Station Mode ===");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Dang ket noi WiFi ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n[OK] Ket noi WiFi thanh cong!");
  Serial.print("[OK] IP cua ESP32: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Test ngay lần đầu
  sendHTTPTest();
}

void loop() {
  // Cứ 15 giây gửi 1 lần HTTP GET để chứng minh vẫn online và giao tiếp được
  sendHTTPTest();
  delay(15000);
}

void sendHTTPTest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    // Dùng server test công cộng, luôn trả về thông tin request của bạn
    http.begin("http://httpbin.org/get?from=ESP32_IoT_Class");
    
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("[HTTP] Gui GET thanh cong! Server tra ve:");
      // Chỉ in vài dòng quan trọng để gọn
      Serial.println(payload.substring(0, 500) + "...");
    } else {
      Serial.println("[HTTP] Loi gui GET, ma loi: " + String(httpCode));
    }
    http.end();
  } else {
    Serial.println("[WiFi] Mat ket noi!");
  }
  Serial.println("--------------------------------------------------");
}
