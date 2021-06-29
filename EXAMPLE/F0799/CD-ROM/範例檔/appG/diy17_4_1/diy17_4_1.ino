// 動手做17-4：Flash 燈光開關和調光器，使用Firmata
// 詳細的程式說明，請參閱第十七章，17-28頁。

#include <Firmata.h>

byte pwmPin = 11;

void analogWriteCallback(byte pin, int value) {
    if (IS_PIN_PWM(pin)) {
        analogWrite(pin, value);
    }
}

void setup() {
  Firmata.setFirmwareVersion(2, 3);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.begin(57600);

  pinMode(pwmPin, OUTPUT);
}

void loop() {
  while(Firmata.available()) {
    Firmata.processInput();
  }
}
