#include "Config.h"
#include<I2Cdev.h>
#include<MPU6050.h>

#include "MPULibrary.h"
#include <Wire.h>
#include <PIDCont.h>
#include <avr/pgmspace.h>

#include <CmdMessenger.h>

CmdMessenger cmdMessenger = CmdMessenger(Serial);

bool armed = false;
bool stopped = false;
const unsigned long sampleInterval = 100; // 0.1 second interval, 10 Hz frequency
unsigned long previousSampleMillis = 0;

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

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  while (!Serial);
#endif
#ifdef CMD
  Serial.begin(115200);
  while (!Serial);
#endif
//  MPU.init();
  motorInit();
  leds_init();
  rxInit(); // cmdMessenger = CmdMessenger(Serial);
  motorArm();
  
#ifdef DEBUG
  motoTest();
  tp1 = millis(); //for led blinking, just cheking whether the board is still answering
#endif
  PID_init();
  tp = millis(); //for updateSensorVal
}
int v = 160;
void loop() {
//  updateSensorVal();
  FlightControl();
  
#ifdef DEBUG
  if (millis() - tp1 > 500) w{
    tp1 = millis();
    if (val == 0) {
      motorWrite(v++);
      if (v >= 170)
        v = 160;
      val = 1;
    }
    else {
      motorStop();
      val = 0;
    }
  }
  leds_status(val);
  debugProcess();
#endif
}
