#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

// --- Cấu hình STA ---
const char* STA_SSID = "TEN_MANG_WIFI_CUA_BAN"; 
const char* STA_PASSWORD = "MAT_KHAU_CUA_BAN";

// --- Cấu hình TCP Client ---
const char* tcp_server_host = "192.168.1.100"; // Thay bằng IP của PC/Server
const uint16_t tcp_server_port = 8080;
WiFiClient tcpClient;

// --- Cấu hình UDP ---
WiFiUDP Udp;
unsigned int localUdpPort = 4210; // Cổng lắng nghe UDP của ESP32
char incomingPacket[255]; // Buffer cho gói tin UDP đến

const int LED_PIN = 2; // Thường là LED tích hợp trên ESP32

// Hàm kết nối TCP và gửi dữ liệu
void send_tcp_data() {
  if (WiFi.status() != WL_CONNECTED) return;

  Serial.println("--- Kiem tra TCP (Ket noi on dinh) ---");
  
  if (!tcpClient.connect(tcp_server_host, tcp_server_port)) {
    Serial.println(" TCP: Ket noi Server that bai!");
    return;
  }
  
  Serial.println(" TCP: Da ket noi. Gui chuoi...");
  tcpClient.println("Hello World via TCP!"); // Gửi chuỗi
  
  // Đọc phản hồi
  while (tcpClient.connected() && !tcpClient.available()) {
    delay(1);
  }
  if (tcpClient.available()) {
      Serial.print("Server phan hoi: ");
      Serial.println(tcpClient.readStringUntil('\n'));
  }
  
  tcpClient.stop(); 
}

// Hàm lắng nghe và xử lý UDP
void listen_udp_data() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // Nhận gói tin UDP
    int len = Udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = 0; // Kết thúc chuỗi
    }
    String message = String(incomingPacket);

    Serial.println("--- Kiem tra UDP (Nhanh, nhe) ---");
    Serial.print("Nhan du lieu UDP tu ");
    Serial.print(Udp.remoteIP());
    Serial.print(":");
    Serial.println(Udp.remotePort());
    Serial.print("Noi dung: ");
    Serial.println(message);

    // Ví dụ: bật/tắt LED qua TCP socket (UDP trong trường hợp này)
    if (message.indexOf("ON") != -1) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println(" LED ON");
    } else if (message.indexOf("OFF") != -1) {
      digitalWrite(LED_PIN, LOW);
      Serial.println(" LED OFF");
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Tắt LED lúc khởi động
  delay(1000);
  Serial.println("\n--- 4. Giao tiep du lieu (TCP/UDP) ---");

  // Kết nối Wi-Fi (Cần có kết nối để gửi/nhận)
  WiFi.mode(WIFI_STA);
  WiFi.begin(STA_SSID, STA_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n Wi-Fi Connected!");
  
  // Bắt đầu lắng nghe UDP
  Udp.begin(localUdpPort);
  Serial.print("UDP Listening on port: ");
  Serial.println(localUdpPort);
}

void loop() {
  // Gửi TCP mỗi 10 giây (cần Server đang chạy trên PC)
  static unsigned long lastTcpTime = 0;
  if (millis() - lastTcpTime > 10000) {
    send_tcp_data();
    lastTcpTime = millis();
  }
  
  // Lắng nghe UDP liên tục
  listen_udp_data();
  delay(10);
}
