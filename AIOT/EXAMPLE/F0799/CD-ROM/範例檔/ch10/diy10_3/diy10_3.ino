// 透過序列埠調整燈光亮度
// 參閱10-8頁

const int ledPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int val;
  if (Serial.available()) {
    val = Serial.parseInt();
    Serial.println(val); 
    if (val > 255) {
      val = 255;
    } else if (val < 0) {
      val = 0;
    }
    analogWrite(ledPin, val);
  }
}
