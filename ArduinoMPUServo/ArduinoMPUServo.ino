#include "Config.h"
#include<I2Cdev.h>
#include<MPU6050.h>

#include "MPULibrary.h"
#include <Wire.h>
#include <PIDCont.h>
#include <avr/pgmspace.h>

PIDCont PIDroll, PIDpitch, PIDyaw, PIDangleX, PIDangleY;
MPULibrary MPU;
unsigned long tp;
unsigned long tp1;
float angles[2] = {
  0.0, 0.0
};
float gx_aver = 0;
float gy_aver = 0;
float gz_aver = 0;


int setX = 0; //Rate Setpoint for PID
int setY = 0; //Rate Setpoint for PID
int setZ = 0; //Rate Setpoint for PID

volatile int rxVal[6] = {1500, 1500, 1500, 0, 0, 1000};

int throttle = MOTOR_ZERO_LEVEL;
byte rateAngleSwitch = 0;
byte val = 0;


int GYRO_XOUT_OFFSET = 0, GYRO_YOUT_OFFSET = 0, GYRO_ZOUT_OFFSET = 0;
long GYRO_XOUT_OFFSET_1000SUM = 0, GYRO_YOUT_OFFSET_1000SUM = 0, GYRO_ZOUT_OFFSET_1000SUM = 0;
int ACCEL_XOUT = 0, ACCEL_YOUT = 0, ACCEL_ZOUT = 0;
float ACCEL_XANGLE = 0.0, ACCEL_YANGLE = 0.0, ACCEL_ZANGLE = 0.0;
int GYRO_XOUT = 0, GYRO_YOUT = 0, GYRO_ZOUT = 0;
float GYRO_XRATE = 0.0, GYRO_YRATE = 0.0, GYRO_ZRATE = 0.0;
float GYRO_XANGLE = 0.0, GYRO_YANGLE = 0.0, GYRO_ZANGLE = 0.0;



void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial);
#endif
  MPU.init();
  //  motorInit();
  leds_init();
  //  rxInit();
  //  motorArm();
  //  PID_init();
  tp = millis(); //for updateSensorVal
  tp1 = millis();

}

void loop() {
  updateSensorVal();
  //  FlightControl();
  if (millis() - tp1 > 1000) {
    tp1 = millis();
    if (val == 0) {
      val = 1;
    }
    else {
      val = 0;
    }
  }
  leds_status(val);

#ifdef DEBUG
  debugProcess();
#endif
}
