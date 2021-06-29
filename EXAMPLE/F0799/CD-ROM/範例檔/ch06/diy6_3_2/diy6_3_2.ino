// 動手做6-3：不用 delay() 的延遲方法
// 詳細的程式說明，請參閱6-16頁。

#define SW_PIN 7
#define LED_PIN 12

unsigned long lastTime = 0;
const long interval = 3000;

void setup() {
  pinMode(SW_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();
  bool val = digitalRead(SW_PIN);

  digitalWrite(LED_PIN, !val);

  if (now - lastTime >= interval) {
    lastTime = now;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}
