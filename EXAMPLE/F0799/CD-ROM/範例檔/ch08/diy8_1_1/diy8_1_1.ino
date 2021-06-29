// I2C 序列連接 LCD 顯示器
// 詳細的程式說明，請參閱第8章，8-11頁。

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();      // 初始化lcd
  lcd.backlight(); // 打開背光
  lcd.clear();
  lcd.print("Stay hungry,"); 
  lcd.setCursor(0, 1);  // 游標移到0行、1列。
  lcd.print("stay foolish.");
}
void loop()
{
}
