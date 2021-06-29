//  掃描 I2 C 匯流排連接的週邊位址
// 參閱8-17頁

#include <Wire.h>

void scanI2C()
{
  byte total, code; // 暫存I2C裝置總數和錯誤代碼

  Wire.begin();            // 初始化I2C通訊介面
  Wire.setClock(100000UL); // 設定時脈速率，此行可省略。
  Serial.begin(9600);
  Serial.println("\nI2C Scanning...");

  for (byte addr = 1; addr < 127; addr++)
  {
    Wire.beginTransmission(addr);
    code = Wire.endTransmission();

    if (code == 0)
    { // 有裝置回應，顯示位址。
      Serial.println(String("Found one at: ") + addr);
      total++; // 總數加1
    }
    else if (code == 4)
    { // 發生不知名錯誤
      Serial.println(String("Unknow error at: ") + addr);
    }
  }

  if (total == 0)
    Serial.println("No I2C devices found."); // 沒發現I2C裝置
}

void setup()
{
  scanI2C();
}

void loop() {}
