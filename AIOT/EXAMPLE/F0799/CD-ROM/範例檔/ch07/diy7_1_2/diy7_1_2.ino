// 動手做7-1：建立自訂函式，函式原型
// 詳細的程式說明，請參閱第7章，7-7頁。

float cirArea(int);

void setup()
{
  Serial.begin(9600);
  float ans = cirArea(10);
  Serial.println(ans);
}
void loop()
{
}

float cirArea(int r)
{
  float area = 3.14 * r * r;
  return area;
}
