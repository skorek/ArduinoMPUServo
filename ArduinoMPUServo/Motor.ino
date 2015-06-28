
void motorInit() {
  pinMode(MOTOR0, OUTPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  analogWrite(MOTOR0, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR1, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR2, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR3, MOTOR_ZERO_LEVEL);
}

void motorArm() {
  analogWrite(MOTOR0, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR1, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR2, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR3, MOTOR_ZERO_LEVEL);
#ifdef SAFE
  while (rxVal[5] < 1100) {
  };
  PIDroll.resetI();
  PIDpitch.resetI();
  PIDyaw.resetI();
  PIDangleX.resetI();
  PIDangleY.resetI();
#endif
}

void motoTest() {
  delay(5000);
  analogWrite(MOTOR0, MOTOR_ARM_START);
  analogWrite(MOTOR1, MOTOR_ARM_START);
  analogWrite(MOTOR2, MOTOR_ARM_START);
  analogWrite(MOTOR3, MOTOR_ARM_START);
  delay(5000);
  motorWrite(160);
  delay(5000);
  motorStop();
}

void motorWrite(int v) {
  analogWrite(MOTOR0, v);
  analogWrite(MOTOR1, v);
  analogWrite(MOTOR2, v);
  analogWrite(MOTOR3, v);
}

void motorStop() {
  analogWrite(MOTOR0, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR1, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR2, MOTOR_ZERO_LEVEL);
  analogWrite(MOTOR3, MOTOR_ZERO_LEVEL);
}

