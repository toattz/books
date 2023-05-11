// 附錄A：典型的輪詢程式
// 程式說明請參閱附錄A，A-2頁。

const byte swPin = 2; // 開關接在數位 2 腳
const byte ledPin = 13;
boolean state = LOW; // 儲存開關的狀態值
void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);
}
void loop()
{
  state = digitalRead(swPin);

  if (state == LOW)
  {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(150);
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
  }
}
