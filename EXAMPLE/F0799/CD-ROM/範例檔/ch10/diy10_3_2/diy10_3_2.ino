// 取絕對值以及限定數值範圍
// 參閱10-11頁

#define LED_PIN 11

void setup() {
  Serial.begin(9600);
  Serial.println("LED is ready!");
}

void loop() {
  String txt;   // 儲存序列字串資料
  int pwm = 0;  // 儲存轉換後的整數值

  if (Serial.available()) {
    txt = Serial.readStringUntil('\n');
    pwm = txt.toInt();

    int val = constrain(pwm, 0, 255);
    Serial.println(String("PWM: ") + pwm);
    Serial.println(String("VAL: ") + val);
    analogWrite(LED_PIN, val);
  }
}
