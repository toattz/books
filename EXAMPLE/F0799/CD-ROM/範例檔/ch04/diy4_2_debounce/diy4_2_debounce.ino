// 用程式解決開關訊號的彈跳問題
// 詳細的程式說明，請參閱4-16頁。

const byte LED = 13;
const byte SW = 8;    // 開關在腳8
bool lastState = LOW; // 記錄上次的開關狀態，預設為「低電位」
bool toggle = LOW;    // 輸出給 LED 的訊號，預設為「低電位」

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
}

void loop()
{
  bool b1 = digitalRead(SW);

  if (b1) {
    delay(20);  // 等待20毫秒
    bool b2 = digitalRead(SW); // 再次讀取開關值

    if (b1 == b2) {   // 確認兩次開關值是否一致
      lastState = b1; // 儲存開關的狀態
    }
  }

  if (b1 != lastState)
  {
    toggle = !toggle;
    digitalWrite(LED, toggle);
    lastState = LOW;
  }
}
