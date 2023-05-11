//  自動發送 LINE 訊息的入侵警報系統
// 請參閱19-29頁

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h> // 引用HTTP前端程式庫

#define PIR_PIN D1
#define IFTTT_KEY "你的IFTTT驗證碼"

const char *ssid = "你的網路名稱";
const char *pwd = "網路密碼";

long unsigned int delay_ms = 30000; // 30秒
long unsigned int last_ms = 0;      // 前次PIR觸發時間
bool state = true;                  // PIR是否觸發
bool start_timer = true;            // 是否啟動計時器

HTTPClient http;

void IFTTT(String evt, String val)
{
  String path = "/trigger/" + evt + "/with/key/" +
                IFTTT_KEY + "?value1=" + val;
  http.begin("maker.ifttt.com", 80, path);

  int httpCode = http.GET();
  if (httpCode == 200)
  {
    String payload = http.getString();
    Serial.println(payload);
  }
  else
  {
    Serial.println("HTTP connection ERROR!");
  }
  http.end();
}

void PIRSensor()
{
  if (digitalRead(PIR_PIN) == HIGH)
  {
    if (state)
    {
      state = false;
      IFTTT("PIR", "%E5%AE%A2%E5%BB%B3");
    }
  }

  if (!state)
  {
    if (start_timer)
    {
      Serial.println("Start timer!");
      last_ms = millis();
      start_timer = false;
    }

    long unsigned int diff = millis() - last_ms;
    if (diff > delay_ms)
    {
      state = true;
      start_timer = true;
    }
  }
}

void setup()
{
  pinMode(PIR_PIN, INPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
}

void loop()
{
  PIRSensor();
}
