// 參閱11-10頁

#include <WiFi.h>
#include "sleepTimer.h" // 引用包含自訂類別的程式庫

const char *ssid = "ZYXEL_1F";
const char *password = "C1470A9A";

SleepTimer st(5); // 建立SleepTimer類別物件st，容許誤差5秒。

void sendData()
{ // 定時器的回呼函式
  Serial.println("送出資料…");
}

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  st.init(28800, 0); // 採”台北”時區初始化即時鐘
  // 啟動計時器，每鐘點的29分0秒執行sendData函式。
  st.start(29, 0, sendData);
}

void loop() {}
