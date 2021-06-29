// 動手做8-2：透過I2C介面串連兩個Arduino板（發射端）
// 詳細的程式說明，請參閱第8章，8-24頁。

#include <Wire.h>

void setup()
{
  Wire.begin(); // 啟動I2C連線
}

void loop()
{
  Wire.beginTransmission(3);
  Wire.write("hello\n");
  Wire.endTransmission();

  delay(1000);
}
