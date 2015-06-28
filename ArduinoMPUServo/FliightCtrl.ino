void FlightControl(){
cmdMessenger.feedinSerialData();



//  if (rateAngleSwitch == 0){
//    setX=(int)PIDangleX.Compute((float)setX+angles[0],gy_aver,(float)setX/RX_ANGLE_DAMPNING);
//    setY=(int)PIDangleY.Compute((float)setY-angles[1],gx_aver,(float)setY/RX_ANGLE_DAMPNING);
//  }
//  int PIDroll_val= (int)PIDroll.Compute((float)setX-gy_aver);
//  int PIDpitch_val= (int)PIDpitch.Compute((float)setY-gx_aver);
//  int PIDyaw_val= (int)PIDyaw.Compute((float)setZ-gz_aver);
//
//  int m0_val=throttle+PIDroll_val+PIDpitch_val+PIDyaw_val;
//  int m1_val=throttle-PIDroll_val+PIDpitch_val-PIDyaw_val;
//  int m2_val=throttle+PIDroll_val-PIDpitch_val-PIDyaw_val;
//  int m3_val=throttle-PIDroll_val-PIDpitch_val+PIDyaw_val;
//
//  analogWrite(MOTOR0,m0_val);
//  analogWrite(MOTOR1,m1_val);
//  analogWrite(MOTOR2,m2_val);
//  analogWrite(MOTOR3,m3_val);
  if (hasExpired(previousSampleMillis, sampleInterval))
  {
    
    sendThrottle();
    sendAttitude();
  }

  
}

