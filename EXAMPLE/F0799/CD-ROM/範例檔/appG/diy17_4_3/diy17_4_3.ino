// 從 ActionScript 3.0 設定 Arduino 接腳的工作模式
// 詳細的程式說明，請參閱第十七章，17-37頁。

#include <Firmata.h>

byte mask;  // 宣告一個儲存遮罩值的變數

void analogWriteCallback(byte pin, int value) {
    if (IS_PIN_PWM(pin)) {
        analogWrite(pin, value);
    }
}

void digitalWriteCallback(byte port, int value) {
  // 依據埠值設定遮罩
  if (port == 0) {
    mask = 252;
  } else if (port == 1) {
    mask = 63;
  }
  // 在指定的數位腳輸出資料（資料值要轉換成byte類型）
  writePort(port, (byte)value, mask);
}

void setPinModeCallback(byte pin, int mode) {
  switch (mode) {
    case OUTPUT:
      if (IS_PIN_DIGITAL(pin)) { // 若此腳是數位腳...
        pinMode(pin, OUTPUT);    // 設定成「輸出」
      }
      break;
    case INPUT:
      if (IS_PIN_DIGITAL(pin)) { // 若此腳是數位腳...
        pinMode(pin, INPUT);     // 設定成「輸入」
      }
      break;
    case PWM:
      if (IS_PIN_PWM(pin)) {    // 若此腳支援 PWM 輸出...
        pinMode(pin, OUTPUT);   // 設定成「輸出」
      }
      break;
  }
}

void setup() {
    Firmata.setFirmwareVersion(2, 3);
    Firmata.attach(DIGITAL_MESSAGE, digitalWriteCallback);
    Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
    Firmata.attach(SET_PIN_MODE, setPinModeCallback);
    Firmata.begin(57600);
    
    // pinMode(pwmPin, OUTPUT);
}

void loop() {
  while(Firmata.available()) {
    Firmata.processInput();
  }
}
