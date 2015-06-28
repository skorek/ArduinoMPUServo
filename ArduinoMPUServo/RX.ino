enum
{
  kAcknowledge,
  kError,
  kSetThrottle,
  kSetXangle,
  kSetYangle,
  kArm,
  kStop,
  kAttitudeAngle,
  kThrottle,
};
void rxInit() {
  cmdMessenger.printLfCr();
  attachCommandCallbacks();
  cmdMessenger.feedinSerialData();
  cmdMessenger.sendCmd(kAcknowledge, "STARTED!");
}

void attachCommandCallbacks()
{
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kSetThrottle, OnSetThrottle);
  cmdMessenger.attach(kSetXangle, OnSetX);
  cmdMessenger.attach(kSetYangle, OnSetY);
  cmdMessenger.attach(kArm, OnArm);
  cmdMessenger.attach(kStop, OnStop);
}

void OnUnknownCommand()
{
  cmdMessenger.sendCmd(kError, "Command without attached callback");
}

void OnSetThrottle()
{
  throttle = (float)cmdMessenger.readInt16Arg ();
  //cmdMessenger.sendCmd(kAcknowledge, "Throttle changed!");
}

void OnSetX()
{
  setX = (float)cmdMessenger.readInt16Arg ();
  //cmdMessenger.sendCmd(kAcknowledge, true);
}

void OnSetY()
{
  setY = (float)cmdMessenger.readInt16Arg ();
  //cmdMessenger.sendCmd(kAcknowledge, true);
}
void OnArm()
{
  armed = true;
  stopped = false;
  motorStop();
  cmdMessenger.sendCmd(kAcknowledge, "ARMED!");
}

void OnStop()
{
  throttle = MOTOR_ZERO_LEVEL;
  stopped = true;
  cmdMessenger.sendCmd(kAcknowledge, "STOP!");
}
void sendThrottle() {
  cmdMessenger.sendCmdStart(kThrottle);
  cmdMessenger.sendCmdBinArg((int)throttle);
  cmdMessenger.sendCmdEnd();
}

void sendAttitude() {
  cmdMessenger.sendCmdStart(kAttitudeAngle);
  cmdMessenger.sendCmdBinArg((int)(gx_aver));
  cmdMessenger.sendCmdBinArg((int)(gy_aver));
  cmdMessenger.sendCmdEnd();
}

bool hasExpired(unsigned long &prevTime, unsigned long interval) {
  if (  millis() - prevTime > interval ) {
    prevTime = millis();
    return true;
  } else
    return false;
}

