// 附錄A：典型的輪詢程式
// 程式說明請參閱A-5頁。

const byte swPin = 2;
const byte ledPin = 13;
volatile boolean state = LOW;

void swISR()
{
  state = !state;
  digitalWrite(ledPin, state);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(swPin, INPUT_PULLUP);

  attachInterrupt(0, swISR, CHANGE); // 啟用中斷處理功能
}

void loop()
{
}
