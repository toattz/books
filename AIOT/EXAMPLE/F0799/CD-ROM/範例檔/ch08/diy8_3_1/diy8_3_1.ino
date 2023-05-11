// 在 LCD 上顯示自訂字元符號
// 詳細的程式說明，請參閱第8章，8-21頁。

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte sp0[8] = {0x04, 0x0E, 0x1F, 0x15, 
               0x1F, 0x0E, 0x0A, 0x11};

void setup(){
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, sp0); 
  lcd.home();
  lcd.write(0); 
}

void loop(){
}
