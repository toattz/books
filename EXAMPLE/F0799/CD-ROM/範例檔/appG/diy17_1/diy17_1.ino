// 動手做17-1：測試 Arduino 與 Flash 連線
// 詳細的程式說明，請參閱第十七章，17-6頁。

void setup() {
  Serial.begin(57600);
}
void loop() {
  int val = analogRead(A0) ;

  Serial.print(val);
  Serial.print( '\0');
  delay(1000);
}
