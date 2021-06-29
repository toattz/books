// LED 切換開關
// 詳細的程式說明，請參閱4-15頁。

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

  if (b1)
  {
    lastState = b1;
  }

  if (b1 != lastState)
  {
    toggle = !toggle;
    digitalWrite(LED, toggle);
    lastState = LOW;
  }
}