// 製作 MIDI 電子鼓，可敲擊六種鼓聲
// 詳細的程式說明，請參閱I-23頁。

const int threshold = 200;
int offTime = 150;

// 打擊樂音色編號，請參閱中文維基百科：
// http://zh.wikipedia.org/wiki/General_MIDI
// 大鼓2, 小鼓1, 閉合開合鈸, 腳踏開合鈸, 中音筒鼓 1, 強音鈸 1
byte notes[6] = {35, 38, 42, 44, 47, 49};
boolean active[6] = {0, 0, 0, 0, 0, 0};
unsigned long startTime[6] = {0, 0, 0, 0, 0, 0};
boolean firstHit[6] = {0, 0, 0, 0, 0, 0};
boolean checked[6] = {0, 0, 0, 0, 0, 0};

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
  for (int pin = 0; pin < 6; pin++)
  {
    int val = analogRead(pin);

    if ((val > threshold))
    {
      if (firstHit[pin] == 1)
      {
        if (checked[pin] == 0)
        {
          startTime[pin] = micros();
          checked[pin] = 1;
        }

        if (micros() - startTime[pin] > 800)
        {
          firstHit[pin] = 0;
          checked[pin] = 0;
        }
      }
      else
      {
        if ((active[pin] == 0))
        {
          val = map(val, threshold, 1023, 50, 127);

          midiMsg(0x99, notes[pin], val);
          active[pin] = 1;
          startTime[pin] = millis();
        }
      }
    }

    if ((active[pin] == 1))
    {
      if (millis() - startTime[pin] > offTime)
      {
        active[pin] = 0;
        midiMsg(0x89, notes[pin], 0);
      }
    }
  }
}
