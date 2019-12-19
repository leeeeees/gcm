
#include "MPU6050.h"

int MPU6050::begin() {
  int error;
  uint8_t c;

  Wire.begin();

  // default at power-up:
  // Gyro at 250 degrees second
  // Acceleration at 2g
  // Clock source at internal 8MHz
  // The device is in sleep mode.
  //
  error = this->MPU6050_read (MPU6050_WHO_AM_I, &c, 1);
  
  // According to the datasheet, the 'sleep' bit
  // should read a '1'. But I read a '0'.
  // That bit has to be cleared, since the sensor
  // is in sleep mode at power-up. Even if the
  // bit reads '0'.
  error = this->MPU6050_read (MPU6050_PWR_MGMT_2, &c, 1);

  // Clear the 'sleep' bit to start the sensor.
  this->MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
}

/**************************************************
 * MPU-6050 Sensor read/write
 **************************************************/
 
int MPU6050::readFromSensor(accel_t_gyro_union &accel_t_gyro) {
  int error;
  double dT;
  
  error = MPU6050_read (MPU6050_ACCEL_XOUT_H, (uint8_t *) &accel_t_gyro, sizeof(accel_t_gyro));
  if(error != 0) {
    return error;
  }
  
  //-----------------------------------------------------------
  // Swap all high and low bytes.
  // After this, the registers values are swapped,
  // so the structure name like x_accel_l does no
  // longer contain the lower byte.
  uint8_t swap;
  #define SWAP(x,y) swap = x; x = y; y = swap
  SWAP (accel_t_gyro.reg.x_accel_h, accel_t_gyro.reg.x_accel_l);
  SWAP (accel_t_gyro.reg.y_accel_h, accel_t_gyro.reg.y_accel_l);
  SWAP (accel_t_gyro.reg.z_accel_h, accel_t_gyro.reg.z_accel_l);
  SWAP (accel_t_gyro.reg.t_h, accel_t_gyro.reg.t_l);
  SWAP (accel_t_gyro.reg.x_gyro_h, accel_t_gyro.reg.x_gyro_l);
  SWAP (accel_t_gyro.reg.y_gyro_h, accel_t_gyro.reg.y_gyro_l);
  SWAP (accel_t_gyro.reg.z_gyro_h, accel_t_gyro.reg.z_gyro_l);

  return error;
}

int MPU6050::MPU6050_read(int start, uint8_t *buffer, int size)
{
  int i, n, error;
  
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  
  n = Wire.write(start);
  if (n != 1)
    return (-10);
  
  n = Wire.endTransmission(false); // hold the I2C-bus
  if (n != 0)
    return (n);
  
  // Third parameter is true: relase I2C-bus after data is read.
  Wire.requestFrom(MPU6050_I2C_ADDRESS, size, true);
  i = 0;
  while(Wire.available() && i<size)
  {
    buffer[i++]=Wire.read();
  }
  if ( i != size)
    return (-11);
  return (0); // return : no error
}

int MPU6050::MPU6050_write(int start, const uint8_t *pData, int size)
{
  int n, error;
  
  Wire.beginTransmission(MPU6050_I2C_ADDRESS);
  
  n = Wire.write(start); // write the start address
  if (n != 1)
    return (-20);
    
  n = Wire.write(pData, size); // write data bytes
  if (n != size)
    return (-21);
    
  error = Wire.endTransmission(true); // release the I2C-bus
  if (error != 0)
    return (error);
  return (0); // return : no error
}

int MPU6050::MPU6050_write_reg(int reg, uint8_t data)
{
  int error;
  error = this->MPU6050_write(reg, &data, 1);
  return (error);
}


