// 動手做7-1：建立自訂函式
// 詳細的程式說明，請參閱第7章，7-6頁。

float ans; // 接收運算結果的變數

float cirArea(int r)
{
  float area = 3.14 * r * r;
  return area;
}

void setup()
{
  Serial.begin(9600);
  ans = cirArea(10);   // 計算半徑 10 的圓面積
  Serial.println(ans); // 顯示結果
  ans = cirArea(20);   // 計算半徑 20 的圓面積
  Serial.println(ans); // 顯示結果
}
void loop()
{
}
