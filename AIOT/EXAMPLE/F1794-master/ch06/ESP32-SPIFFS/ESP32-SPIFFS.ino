// 參閱6-17頁

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

const char *ssid = "ZYXEL_1F";
const char *password = "C1470A9A";

AsyncWebServer server(80);

void setup()
{
  Serial.begin(115200);

  if (!SPIFFS.begin(true))
  {
    Serial.println("掛載SPIFFS分區出錯啦～");
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nIP位址：");
  Serial.println(WiFi.localIP());

  server.serveStatic("/", SPIFFS, "/www/").setDefaultFile("index.html");
  server.serveStatic("/img", SPIFFS, "/www/img/");
  server.serveStatic("/favicon.ico", SPIFFS, "/www/favicon.ico");

  server.begin();
  Serial.println("HTTP伺服器開工了～");
}

void loop() {}
