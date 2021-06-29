// 動手做7-1：靜態變數
// 詳細的程式說明，請參閱第7章，7-10頁。

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  static int x;
  x ++;
  Serial.println(x);
  delay(500);
}
