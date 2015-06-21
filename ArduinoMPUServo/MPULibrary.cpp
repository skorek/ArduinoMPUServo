#include "MPULibrary.h"

MPULibrary::MPULibrary() {

}

void MPULibrary::init() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  // verify connection
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  calibrate();
}

void MPULibrary::calibrate() {
  long a[6] = {0, 0, 0, 0, 0, 0};
  int size = 100;
  for (int i = 0; i < size; ++i) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    a[0] += ax;
    a[1] += ay;
    a[2] += az;
    a[3] += gx;
    a[4] += gy;
    a[5] += gz;
    delay(1);
  }
  ACC_X_OFFSET = a[0] / size;
  ACC_Y_OFFSET = a[1] / size;
  ACC_Z_OFFSET = a[2] / size;
  //
  GYRO_X_OFFSET = a[3] / size/gyro_sensitivity;
  GYRO_Y_OFFSET = a[4] / size/gyro_sensitivity;
  GYRO_Z_OFFSET = a[5] / size/gyro_sensitivity;
#ifdef DEBUG
  Serial.print("Acceloffsets: ")
  Serial.print(ACC_X_OFFSET); Serial.print('\t');
  Serial.print(ACC_Y_OFFSET); Serial.print('\t');
  Serial.print(ACC_Z_OFFSET); Serial.print('\t');
  Serial.print("Gyro  offsets: ")
  Serial.print(GYRO_X_OFFSET); Serial.print('\t');
  Serial.print(GYRO_Y_OFFSET); Serial.print('\t');
  Serial.print(GYRO_Z_OFFSET); Serial.print('\t');

#endif
}
void MPULibrary::getAxlData(int buff[]) {
  accelgyro.getAcceleration(&ax, &ay, &az);
  buff[0] = ax;
  buff[1] = ay;
  buff[2] = az;
}

void MPULibrary::getGyroData(float buff[]) {
  accelgyro.getRotation(&gx, &gy, &gz);
  buff[0] = gx/ gyro_sensitivity;
  buff[1] = gy/ gyro_sensitivity;
  buff[2] = gz/ gyro_sensitivity;
}

void MPULibrary::getMagData(int buff[]) {

}

