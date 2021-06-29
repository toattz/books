// 動手做9-2：使用光敏電阻製作小夜燈
// 詳細的程式說明，請參閱第9章，9-9頁。

const byte LED = 13;
const byte CdS = A0;

void setup()
{
  pinMode(LED, OUTPUT);
}
void loop()
{
  int val;
  val = analogRead(A0);
  if (val >= 700)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}
