#ifndef MPULibrary_h
#define MPULibrary_h
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include<I2Cdev.h>
#include<MPU6050.h>

#include "Arduino.h"
#include "Wire.h"

#define gyro_sensitivity 131
#define accel_sensitivity 16384
class MPULibrary
{
  public:
    MPULibrary();
    void init();
    void getAxlData(int buff[]);
    void getGyroData(float buff[]);
    void getMagData(int buff[]);
    int16_t ACC_X_OFFSET;
    int16_t ACC_Y_OFFSET;
    int16_t ACC_Z_OFFSET;
    //
    int16_t GYRO_X_OFFSET;
    int16_t GYRO_Y_OFFSET;
    int16_t GYRO_Z_OFFSET;
  private:
    void calibrate();
    MPU6050 accelgyro;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

};
#endif
