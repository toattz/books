// 讀取IMU數據
// 參閱13-29頁

#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 imu(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  imu.begin();
  imu.calcGyroOffsets(true);  // 計算偏移量並顯示偏移值
}

void loop() {
  imu.update();
  Serial.print("getGyroAngleX: ");
  Serial.print(imu.getGyroAngleX());
  Serial.print("\tgetAccAngleX: ");
  Serial.print(imu.getAccAngleX());
  Serial.print("\tgetAngleX: ");
  Serial.println(imu.getAngleX());
}
