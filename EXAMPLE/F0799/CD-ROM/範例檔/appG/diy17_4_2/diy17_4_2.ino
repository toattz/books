// 用 Firmata 程式庫改寫「接零件」遊戲
// 詳細的程式說明，請參閱第十七章，17-32頁。

#include <Firmata.h>

void setup() {
  Firmata.setFirmwareVersion(2, 3);
  Firmata.begin(57600);
}

void loop() {
  Firmata.sendAnalog(0, analogRead(0));
  delay(100);
}
