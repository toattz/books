//  從 D1 板（ESP8266） 連結網站伺服器
// 請參閱19-26頁

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "你的網路名稱";
const char *pwd = "網路密碼";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  HTTPClient http;

  //http.begin("http://swf.com.tw/openData/test.html");
  http.begin("swf.com.tw", 80, "/openData/test.html");
  int httpCode = http.GET();
  Serial.println(String("\nHTTP code: ") + httpCode);

  if (httpCode > 0)
  {
    String payload = http.getString();
    Serial.println(payload);
  }

  http.end();
}

void loop()
{
}
