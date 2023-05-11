// 透過「虛擬 MIDI」介面演奏音樂
// 詳細的程式說明，請參閱I-12頁。

byte note;

// 發送 MIDI 訊息的自訂程式
void midiMsg(byte cmd, byte pitch, byte velocity)
{
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void setup()
{
  Serial.begin(115200); // 序列連線速度是 115200
  Serial.write(0xC0);   // 改變音色
  Serial.write(0x0A);   // 選用 Music Box 音色
}

void loop()
{
  for (note = 48; note < 84; note++)
  {
    midiMsg(0x90, note, 0x40);
    delay(100);
    midiMsg(0x80, note, 0x00);
    delay(100);
  }
}
