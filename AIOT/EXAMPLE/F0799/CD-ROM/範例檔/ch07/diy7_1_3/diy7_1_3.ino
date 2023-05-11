// 動手做7-1：全域變數
// 詳細的程式說明，請參閱第7章，7-10頁。

int x;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  x++;
  Serial.println(x);
  delay(500);
}
