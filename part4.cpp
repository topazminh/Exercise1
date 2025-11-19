#include <WiFi.h>
#include <WiFiServer.h>   // Thêm cái này
#include <WiFiUdp.h>

// --- Cấu hình Wi-Fi STA ---
const char* ssid = "TE_MANG_WIFI_CUA_BAN";          //Sửa dòng này
const char* password = "MAT_KHAU_WIFI_CUA_BAN";     //Sửa dòng này

// --- TCP Server (ESP32 làm Server) ---
WiFiServer server(80);                    // Cổng 80 hoặc 8080 tuỳ bạn
const int LED_PIN = 2;

// --- UDP ---
WiFiUDP Udp;
unsigned int localUdpPort = 4210;
char incomingPacket[255];

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // Kết nối Wi-Fi
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP ESP32 (TCP Server): ");
  Serial.println(WiFi.localIP());

  // Khởi động TCP Server
  server.begin();
  Serial.println("TCP Server started on port 80");

  // Khởi động UDP
  Udp.begin(localUdpPort);
  Serial.printf("UDP listening on port %d\n", localUdpPort);
}

void loop() {
  // ==================== TCP SERVER (để client kết nối vào bật/tắt LED) ====================
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client TCP kết nối!");
    String req = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') break;
        req += c;
      }
    }

    Serial.print("Yêu cầu từ client: ");
    Serial.println(req);

    // Phản hồi đơn giản
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html; charset=utf-8");
    client.println("Content-Type: text/html");
    client.println();

    if (req.indexOf("GET /on") != -1) {
      digitalWrite(LED_PIN, HIGH);
      client.println("LED ĐÃ BẬT");
      Serial.println("LED ON qua TCP");
    } else if (req.indexOf("GET /off") != -1) {
      digitalWrite(LED_PIN, LOW);
      client.println("LED ĐÃ TẮT");
      Serial.println("LED OFF qua TCP");
    } else {
      client.println("<h1>ESP32 TCP Control</h1><a href=\"/on\">BẬT LED</a><br><a href=\"/off\">TẮT LED</a>");
    }
    client.stop();
  }

  // ==================== UDP (nhận lệnh nhanh) ====================
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;

    String msg = String(incomingPacket);
    Serial.print("UDP nhận: ");
    Serial.println(msg);

    if (msg.indexOf("ON") != -1) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON qua UDP");
    } else if (msg.indexOf("OFF") != -1) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF qua UDP");
    }

    // Gửi lại phản hồi UDP (tuỳ chọn)
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.print("ESP32 nhan: ");
    Udp.print(msg);
    Udp.endPacket();
  }

  delay(10);
}
