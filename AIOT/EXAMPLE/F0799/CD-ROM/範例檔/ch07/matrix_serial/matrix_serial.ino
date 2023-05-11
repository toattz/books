#include <SPI.h>  // 引用 SPI 程式庫

/*
 * 
 *測試資料：
 * 1111111111111111111111111111111111111111111111111111111111111111
 * 0001110000011100000111000001110000011100000111000001110000011100
 * 0001100000111100011111100011110000011000000000000000000000011000
 */

// 定義 MAX7219 暫存器
const byte NOOP = 0x0;        // 不運作
const byte DECODEMODE = 0x9;  // 解碼模式
const byte INTENSITY = 0xA;   // 顯示強度
const byte SCANLIMIT = 0xB;   // 掃描限制
const byte SHUTDOWN = 0xC;    // 停機
const byte DISPLAYTEST = 0xF; // 顯示器檢測

//byte symbol[8];
byte display_screen[64];
int array_index=0;

// 設定 MAX7219 暫存器資料的自訂函數
void max7219(byte reg, byte data) {
  digitalWrite (SS, LOW);
  SPI.transfer (reg);
  SPI.transfer (data);
  digitalWrite (SS, HIGH);
}

void writeDisplayOnMatrix() { 
  char val;
  
  while (Serial.available()>0) {
    val = Serial.read();
    if (val !='\n') {
       display_screen[array_index]= val - 48;
       array_index++;
    } else {
      array_index = 0;
      Serial.print("array: ");
      for (byte i = 0; i<8; i++) {
        byte temp = 0;
        for (byte j=0; j<8;j++) {
          temp = temp | (display_screen[j+i*8] << j);
          Serial.print(display_screen[j+i*8]);
        }
       //symbol[i] = temp;
       max7219 (i + 1, temp);  // 顯示自訂圖像
      }
      Serial.println();
    }
  }
}

void setup () {
  pinMode(SS, OUTPUT);     // 將預設的 SS 腳（數位 10）設成「輸出」
  digitalWrite(SS, HIGH);  // 先在 SS 腳輸出高電位
  //（代表「尚不選取周邊」）
  Serial.begin(9600);
  SPI.begin ();     // 啟動 SPI 連線
  
  max7219 (SCANLIMIT, 7);  // 設定掃描 8 行
  max7219 (DECODEMODE, 0); // 不使用 BCD 解碼
  max7219 (INTENSITY, 8);  // 設定成中等亮度
  max7219 (DISPLAYTEST, 0);// 關閉顯示器測試
  max7219 (SHUTDOWN, 1);   // 關閉停機模式（亦即，「開機」）

  // 清除顯示畫面（LED 矩陣中的八行都設定成 0）
  for (byte i=0; i < 8; i++) {
    max7219 (i + 1, 0);
  }
}

void loop () {
  writeDisplayOnMatrix();
}

