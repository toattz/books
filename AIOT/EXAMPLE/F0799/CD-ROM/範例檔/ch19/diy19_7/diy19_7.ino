// 動態網頁調光器
// 請參閱19-38頁

#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#define PWM_PIN D1

String pwm_val;

const char *ssid = "你的網路名稱";
const char *pwd = "網路密碼";

AsyncWebServer server(80);

void setup(void)
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  SPIFFS.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // 顯示IP位址

  server.serveStatic("/", SPIFFS, "/www/").setDefaultFile("index.html");
  server.serveStatic("/img", SPIFFS, "/www/img/");
  server.serveStatic("/favicon.ico", SPIFFS, "/www/favicon.ico");

  server.on("/sw", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasParam("led"))
    {
      AsyncWebParameter *p = request->getParam("led");
      if (p->value() == "on")
      {
        digitalWrite(LED_BUILTIN, LOW);
      }
      else if (p->value() == "off")
      {
        digitalWrite(LED_BUILTIN, HIGH);
      }
    }

    request->send(200, "text/plain", "OK!");
  });

  server.on("/pwm", HTTP_GET, [](AsyncWebServerRequest *req) {
    if (req->hasParam("val"))
    {
      AsyncWebParameter *p = req->getParam("val");
      pwm_val = p->value();
      analogWrite(PWM_PIN, pwm_val.toInt());
    }

    req->send(200, "text/plain", "OK");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
}
