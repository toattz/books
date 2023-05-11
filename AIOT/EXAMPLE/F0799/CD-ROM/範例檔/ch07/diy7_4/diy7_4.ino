// 動手做7-4：在序列埠監控視窗輸出矩形排列的星號
// 詳細的程式說明，請參閱第7章，7-23頁。

void setup()
{
  Serial.begin(9600);

  for (int y = 0; y < 3; y++)
  {
    for (int x = 0; x < 6; x++)
    {
      Serial.print('*');
    }
    Serial.print('\n');
  }
}

void loop()
{
}
