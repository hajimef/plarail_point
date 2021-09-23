#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
#include <ESPmDNS.h>

const char* ssid = "your_ssid";
const char* pass = "your_pass";
const char* mdns_name = "esp32pp";
int c_angle = 110;
int servo1Pin = 5;

#define MODE_NONE 0
#define MODE_STRAIGHT 1
#define MODE_CURVE 2

Servo servo1;
WebServer server(80);

void showHTML(int mode) {
  String html;

  html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta charset=\"utf-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<title>ポイント制御</title>";
  html += "</head>";
  html += "<body>";
  if (mode == MODE_STRAIGHT) {
    html += "<p>直進に切り替えました</p>";
  }
  if (mode == MODE_CURVE) {
    html += "<p>分岐に切り替えました</p>";
  }
  html += "<ul>";
  html += "<li><a href=\"/s\">直進</a></li>";
  html += "<li><a href=\"/c\">分岐</a></li>";
  html += "</ul>";
  html += "</body>";
  html += "</html>";
  // HTMLを出力する
  server.send(200, "text/html", html);  
}

void handleRoot() {
  showHTML(MODE_NONE);
}

void handleStraight() {
  servo1.write(90);
  showHTML(MODE_STRAIGHT);    
}

void handleCurve() {
  servo1.write(c_angle);
  showHTML(MODE_CURVE);    
}

void handleNotFound(void) {
  server.send(404, "text/plain", "Not Found");
}
void setup() {
  // シリアルポートの初期化
  Serial.begin(115200);
  // アクセスポイントに接続
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // ESP32のIPアドレスを出力
  Serial.println("WiFi Connected.");
  Serial.print("IP = ");
  Serial.println(WiFi.localIP());
  // mDNSの設定
  if (!MDNS.begin(mdns_name)) {
    Serial.println("mDNS failed.");
    while(1);
  }
  // サーボモーターの初期化
  servo1.setPeriodHertz(50);
  servo1.attach(servo1Pin, 500, 2500);
  servo1.write(90);
  // 処理するアドレスを定義
  server.on("/", handleRoot);
  server.on("/s", handleStraight);
  server.on("/c", handleCurve);
  server.onNotFound(handleNotFound);
  // Webサーバーを起動
  server.begin();
}

void loop() {
  server.handleClient();
}
