// 動手做11-1：演奏一段瑪莉歐旋律，使用 .h 標頭檔分割程式碼。
// 詳細的程式說明，請參閱第11章，11-7頁。
#include "pitches.h"

const int INTERVAL = 150;
const byte SP_PIN = 11;

void setup()
{
  pinMode(SP_PIN, OUTPUT);
}

void loop()
{
  tone(SP_PIN, NOTE_E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, NOTE_E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, NOTE_E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, NOTE_C5, INTERVAL);
  delay(INTERVAL);
  tone(SP_PIN, NOTE_E5, INTERVAL);
  delay(INTERVAL * 3);
  tone(SP_PIN, NOTE_G5, INTERVAL);
  delay(INTERVAL * 7);
}
