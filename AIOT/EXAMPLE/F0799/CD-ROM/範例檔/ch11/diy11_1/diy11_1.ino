// 動手做11-1：演奏一段瑪莉歐旋律，使用 #define 巨集指令替換資料。
// 詳細的程式說明，請參閱第11章，11-6頁。

#define E5 659
#define C5 523
#define G5 784
const int INTERVAL = 150;
const byte SP_PIN = 11;

void setup()
{
  pinMode(SP_PIN, OUTPUT);
}

void loop()
{
  tone(SP_PIN, E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, C5, INTERVAL);
  delay(INTERVAL);
  tone(SP_PIN, E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, G5, INTERVAL);
  delay(INTERVAL * 7);
}
