// 用麵包板組裝開關電路
// 詳細的程式說明，請參閱第四章，4-8頁。

const byte LED = 13;
const byte SW = 8;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
}
void loop() {
  bool val = digitalRead(SW);
  digitalWrite(LED, val);
}
