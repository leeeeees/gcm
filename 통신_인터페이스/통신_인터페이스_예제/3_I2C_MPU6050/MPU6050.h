#ifndef _CPP_MPU6050
#define _CPP_MPU6050

#include <math.h>
#include <Wire.h>

#define MPU6050_ACCEL_XOUT_H 0x3B // R
#define MPU6050_PWR_MGMT_1 0x6B // R/W
#define MPU6050_PWR_MGMT_2 0x6C // R/W
#define MPU6050_WHO_AM_I 0x75 // R
#define MPU6050_I2C_ADDRESS 0x68    // I2C address of MPU-6050 module

typedef union accel_t_gyro_union {
  struct {
    uint8_t x_accel_h;
    uint8_t x_accel_l;
    uint8_t y_accel_h;
    uint8_t y_accel_l;
    uint8_t z_accel_h;
    uint8_t z_accel_l;
    uint8_t t_h;
    uint8_t t_l;
    uint8_t x_gyro_h;
    uint8_t x_gyro_l;
    uint8_t y_gyro_h;
    uint8_t y_gyro_l;
    uint8_t z_gyro_h;
    uint8_t z_gyro_l;
  } reg;

  struct {
    int x_accel;
    int y_accel;
    int z_accel;
    int temperature;
    int x_gyro;
    int y_gyro;
    int z_gyro;
  } value;
};

class MPU6050 
{
  public:
    int begin();
    int readFromSensor(accel_t_gyro_union &accel_t_gyro);
    int MPU6050_read(int start, uint8_t *buffer, int size);
    int MPU6050_write(int start, const uint8_t *pData, int size);
    int MPU6050_write_reg(int reg, uint8_t data);
};

#endif  /* _CPP_MPU6050 */
