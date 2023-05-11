// 動手做17-3：Flash 燈光開關和調光器
// 詳細的程式說明，請參閱第十七章，17-21頁。

String str = ""; // 接收到的序列埠字串值，預設為空字串
boolean lineEnd = false; // 是否收到完整訊息，預設為「否」
char type; // 訊息類型字元，'A' 代表類比；'D' 代表數位
int pin;   // 儲存接腳編號
int data;  // 儲存資料值

// 將字串轉換成整數
int strToInt(String s) {
  char buf[s.length() + 1];
  s.toCharArray(buf, sizeof(buf));
  return atoi(buf); // 將 buf 陣列轉換成整數之後傳回
}

void setup() {
  Serial.begin(57600);
}

void loop() {
  // 當序列埠傳入4個以上字元時，執行大括號裡的程式...
  if (Serial.available() > 4) {
    char c = Serial.read(); // 讀取第一個字元
    
    // 確認第一個字元是'A'或'D'
    if (c == 'A' || c =='D') {
      str += c;           // 把讀入的字元連結成字串
      
      while (Serial.available()) {
        c = Serial.read();
        str += c;
        
        if (c ==  '\n') {       // 如果讀取到 '\n' 字元...
          lineEnd = true;       // 代表「讀取完畢」，可以開始解析字串了
        }
      }
    }
  }
 
  // 解析自訂訊息
  if (lineEnd) {
    type = str.charAt(0);
    pin = strToInt(str.substring(1,3));
    
    if (type == 'A') {
      data = strToInt(str.substring(3));
      analogWrite(pin, data);

    } else if (type == 'D') {
      data = str.charAt(3)-48;
      digitalWrite(pin, data);
    }

    lineEnd = false;
 
    str = "";
  } 
}
