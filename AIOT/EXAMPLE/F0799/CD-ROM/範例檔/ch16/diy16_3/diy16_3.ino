#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    A0     // Reset腳
#define SS_PIN     10     // 晶片選擇腳

int balance = 0;  // 帳戶餘額
int credit = 500; // 每次充值的金額

MFRC522 mfrc522(SS_PIN, RST_PIN);    // 建立MFRC522物件

MFRC522::MIFARE_Key key;  // 儲存金鑰

byte sector = 15;   // 指定讀寫的「區段」，可能值:0~15
byte block = 1;     // 指定讀寫的「區塊」，可能值:0~3
byte blockData[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 暫存讀取區塊內容的陣列，MIFARE_Read()方法要求至少要18位元組空間，來存放16位元組。
byte buffer[18];
byte buffersize = sizeof(buffer);

MFRC522::StatusCode status;

void checkBalance(int debit) {   // 扣款
  balance = ((int)buffer[1]) << 8 | buffer[0];
  debit = 50;
  // 若餘額小於0，存入500元
  if (balance - debit <= 0) {
    balance += credit;
  }

  balance -= debit;   // 扣除50元
  blockData[0] = balance & 0xFF;
  blockData[1] = balance >> 8;
}

void writeBlock(byte _sector, byte _block, byte _blockData[]) {
  if (_sector < 0 || _sector > 15 || _block < 0 || _block > 3) {
    // 顯示「區段或區塊碼錯誤」，然後結束函式。
    Serial.println(F("Wrong sector or block number."));
    return;
  }

  if (_sector == 0 && _block == 0) {
    // 顯示「第一個區塊只能讀取」，然後結束函式。
    Serial.println(F("First block is read-only."));
    return;
  }

  byte blockNum = _sector * 4 + _block;  // 計算區塊的實際編號（0~63）
  byte trailerBlock = _sector * 4 + 3;   // 控制區塊編號

  // 驗證金鑰
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  // 若未通過驗證…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // 在指定區塊寫入16位元組資料
  status = mfrc522.MIFARE_Write(blockNum, _blockData, 16);
  // 若寫入不成功…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // 顯示「寫入成功！」
  Serial.println(F("Checking data..."));

  status = mfrc522.MIFARE_Read(blockNum, buffer, &buffersize);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  }

  byte count = 0;
  for (byte i = 0; i < 16; i++) {
    if (buffer[i] == blockData[i])
      count++;
  }

  if (count == 16) {
    Serial.println(F("Success :-)"));
  } else {
    Serial.println(F("Failure, no match :-("));
    Serial.println(F("  perhaps the write didn't work properly..."));
  }
  Serial.println();
}

void readBlock(byte _sector, byte _block, byte _blockData[])  {
  if (_sector < 0 || _sector > 15 || _block < 0 || _block > 3) {
    // 顯示「區段或區塊碼錯誤」，然後結束函式。
    Serial.println(F("Wrong sector or block number."));
    return;
  }

  byte blockNum = _sector * 4 + _block;  // 計算區塊的實際編號（0~63）
  byte trailerBlock = _sector * 4 + 3;   // 控制區塊編號

  // 驗證金鑰
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  // 若未通過驗證…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(blockNum, _blockData, &buffersize);

  // 若讀取不成功…
  if (status != MFRC522::STATUS_OK) {
    // 顯示錯誤訊息
    Serial.print(F("MIFARE_read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // 顯示「讀取成功！」
  Serial.println(F("\nData was read."));
}

void setup() {
  Serial.begin(9600);
  SPI.begin();               // 初始化SPI介面
  mfrc522.PCD_Init();        // 初始化MFRC522卡片

  Serial.println(F("Please scan MIFARE Classic card..."));

  // 準備金鑰（用於key A和key B），出廠預設為6組 0xFF。
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  // 如果感應到卡片…
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // 讀取卡片
    readBlock(sector, block, buffer);      // 區段編號、區塊編號、存放讀取資料的陣列
    checkBalance(50);  // 扣50
    // 寫入卡片
    writeBlock(sector, block, blockData);  // 區段編號、區塊編號、包含寫入資料的陣列

    Serial.println(String("Balance: ") + balance);
    // 令卡片進入停止狀態
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }
}
