// 動手做17-2：「接電子零件」互動遊戲
// 詳細的程式說明，請參閱第十七章，17-15頁。

void setup() {
  Serial.begin(57600);
}
void loop() {
  int val = analogRead(A0) ;

  Serial.print(val);
  Serial.print( '\0');
  delay(100);
}
