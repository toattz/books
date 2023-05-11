// 動手做6-3：不用 delay() 的延遲方法
// 詳細的程式說明，請參閱6-16頁。

#define SW_PIN 7 
#define LED_PIN 12

void setup() {
  pinMode(SW_PIN, INPUT_PULLUP); // 啟用上拉電阻
  pinMode(LED_BUILTIN, OUTPUT); 
  pinMode(LED_PIN, OUTPUT);
} void loop() {
  bool val = digitalRead(SW_PIN); // 讀取開關狀態 
  digitalWrite(LED_PIN, !val);
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); 
  delay(3000);
}
