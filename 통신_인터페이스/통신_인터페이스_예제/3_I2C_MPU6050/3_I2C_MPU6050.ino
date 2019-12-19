#include "MPU6050.h"

MPU6050 mpu6050;

#define SENSOR_READ_INTERVAL 250      // 센서 읽는 간격
unsigned long prevSensoredTime = 0;
unsigned long curSensoredTime = 0;


void setup() {
  Serial.begin(9600);
  mpu6050.begin();
}

void loop() {
  accel_t_gyro_union accel_t_gyro;
  curSensoredTime = millis();
  
  // 250ms 간격으로 센서 읽기
  if(curSensoredTime - prevSensoredTime > SENSOR_READ_INTERVAL) {
    mpu6050.readFromSensor(accel_t_gyro);  // Read from sensor
    prevSensoredTime = curSensoredTime;
  
    // Print raw accel, gyro values
    Serial.print(F("accel x,y,z = "));
    Serial.print(accel_t_gyro.value.x_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_accel, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_accel, DEC);
    Serial.println(F(""));
  
    Serial.print(F("gyro x,y,z = "));
    Serial.print(accel_t_gyro.value.x_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.y_gyro, DEC);
    Serial.print(F(", "));
    Serial.print(accel_t_gyro.value.z_gyro, DEC);
    Serial.println(F(""));
  }
}



