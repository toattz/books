// 透過Arduino演奏MIDI音樂
// 詳細的程式說明，請參閱I_7頁。

#include <SoftwareSerial.h>

byte note;
SoftwareSerial MIDI(2, 3);

void midiMsg(byte cmd, byte pitch, byte velocity)
{
  MIDI.write(cmd);
  MIDI.write(pitch);
  MIDI.write(velocity);
}

void setup()
{
  MIDI.begin(31250);
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
