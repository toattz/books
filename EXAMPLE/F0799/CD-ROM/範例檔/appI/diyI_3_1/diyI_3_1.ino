// 製作 MIDI 電子鼓，使用delay()函數
// 詳細的程式說明，請參閱I_17頁。

const int threshold = 200;   // 敲擊蜂鳴片的臨界值
unsigned long startTime = 0; // 記錄開始「擊鼓」的時間
boolean active = 0;          // 代表是否在「作用期間」
int maxTime = 100;           // 從打擊到結束的時間

void midiMsg(byte cmd, byte pitch, byte velocity)
{
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int val = analogRead(A0); // 讀取類比值

  if (val >= threshold)
  {                       // 如果超過臨界值…
    delay(1);             // 暫停1毫秒
    val = analogRead(A0); // 再次讀取類比值
    if (active == 0)
    { // 若電子鼓不在作用期間…
      val = map(val, threshold, 1023, 30, 127);
      midiMsg(0x99, 49, val);
      startTime = millis(); // 記錄發聲的時間點
      active = 1;           // 將電子鼓設定為「作用中」
    }
  }
  if (active == 1)
  { // 若電子鼓在「作用中」
    if (millis() - startTime > maxTime)
    {
      active = 0;
      midiMsg(0x89, 49, val);
    }
  }
}
