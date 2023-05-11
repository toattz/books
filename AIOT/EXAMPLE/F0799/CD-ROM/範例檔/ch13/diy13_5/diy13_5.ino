// 使用IMU感測器控制伺服馬達
// 參閱13-34頁

#include <MPU6050_tockn.h>
#include <Servo.h>
#include <Wire.h>

MPU6050 imu(Wire);
Servo servoX, servoY;  // 宣告兩個伺服馬達物件
servoX.attach(8);      // 設定伺服馬達的接腳
servoY.attach(9);

int valX, posX;
int valZ, posZ;  // 暫存IMU模組的Z軸值

void setup() {
  Serial.begin(9600);
  Wire.begin();
  imu.begin();
  imu.calcGyroOffsets(true);  // 顯示校正訊息
}

void loop() {
  imu.update();
  valX = imu.getAngleX();
  valZ = imu.getAngleZ();   // 讀取Z軸的融合角度值
  Serial.print(valX);
  Serial.print(",");
  Serial.println(valZ);

  posX = map(valX, -150, 150, 0, 180);
  posZ = map(valZ, -150, 150, 0, 180);
  servoX.write(posX);
  servoY.write(posZ);   // 用Z軸值設定伺服馬達的角度
  delay(15);
}
