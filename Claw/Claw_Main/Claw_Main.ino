#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Convert Angle to pulse
int angleBase(int angle) {
  int pulse = map(angle, 0, 180, 100, 600);
  return pulse;
}
int angleNeck(int angle) {
  int pulse = map(angle, 0, 180, 120, 600);
  return pulse;
}
int angleShoulder(int angle) {
  int pulse = map(angle, 0, 180, 150, 600);
  return pulse;
}
int angleElbow(int angle) {
  int pulse = map(angle, 0, 180, 150, 650);
  return pulse;
}
int angleWrist(int angle) {
  int pulse = map(angle, 0, 180, 130, 600);
  return pulse;
}
int angleClaw(int angle) {
  int pulse = map(angle, 0, 180, 220, 400);
  return pulse;
}
// End Conversions

String serialInput;
int basePos;
int neckPos;
int shoulderPos;
int elbowPos;
int wristPos;
int clawPos;
int servoNumber, destAngle;
int servoPos;


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  
  yield();


  // Set default servo position
  Serial.println("Initializing Servos...");
  pwm.setPWM(0, 0, angleBase(90)); delay(500); basePos = 90;
  pwm.setPWM(3, 0, angleElbow(0)); delay(500); elbowPos = 0;
  pwm.setPWM(1, 0, angleNeck(90)); delay(500); neckPos = 90;
  pwm.setPWM(2, 0, angleShoulder(0)); delay(500); shoulderPos = 0;
  pwm.setPWM(4, 0, angleWrist(180)); delay(500); wristPos = 180;
  pwm.setPWM(5, 0, angleClaw(90)); delay(500); clawPos = 90;
  delay (2000);


}

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= 60;   // 60 Hz
  pulselength /= 4096;  // 12 bits of resolution
  pulse *= 1000;
  pulse /= pulselength;
  Serial.println(pulse);
  pwm.setPWM(n, 0, pulse);
}


void loop()
{
// To be controlled via Serial Monitor
  if (Serial.available())  {
    serialInput = Serial.readString();
    char data1 = serialInput.charAt(0);
    switch (data1) {
      // Pack up function
      case 'p':
        // Move down
        moveElbow(180);
        moveNeck(180);
        moveClaw(0);
        delay (2000);
        // Grab
        moveShoulder(25);
        moveElbow(145);
        delay (2000);
        moveClaw(150);
        delay (5000);
        moveElbow(180);
        moveShoulder(0);
        delay (2000);
        // Move up
        moveNeck(90);
        moveElbow(20);
        moveShoulder(90);
        moveBase(0);
        // Drop
        moveShoulder(70);
        moveClaw(0);
        delay(2000);
        ResetServos();
        break;
      // Home function
      case 'h':
        ResetServos();
        Serial.println("Resetting servos...");
        delay (5000);
        break;
      // General case (to control individual servo angles) q[servoPin][angle] eg. q1150-pin 1, 150 degrees
      case 'q':
        String data2 = serialInput.substring(2);
        int servoval = data2.toInt();
        int servoPin = serialInput.charAt(1);
        int servoPinNumber = serialInput.toInt();
        int servoDest = servoval;
        switch (servoPin) {
          case '0':
            moveBase(servoDest);
            break;
          case '1':
            moveNeck(servoDest);
            break;
          case '2':
            moveShoulder(servoDest);
            break;
          case '3':
            moveElbow(servoDest);
            break;
          case '4':
            moveWrist(servoDest);
            break;
          case '5':
            moveClaw(servoDest);
            break;
        }
        // End General case

    }
  }
}//end Loop.


// Create move functions for all servos --> move[servoName](destinationAngle);
void moveBase(int destAngle){
  for (int servoPos = basePos; destAngle < basePos; servoPos--) {
    pwm.setPWM(0, 0, angleBase(servoPos));
    delay(8);
    basePos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = basePos; destAngle > basePos; servoPos++) {
    pwm.setPWM(0, 0, angleBase(servoPos));
    delay(8);
    basePos = servoPos;
    Serial.println(servoPos);
  }
}
void moveNeck(int destAngle){
  for (int servoPos = neckPos; destAngle < neckPos; servoPos--) {
    pwm.setPWM(1, 0, angleNeck(servoPos));
    delay(8);
    neckPos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = neckPos; destAngle > neckPos; servoPos++) {
    pwm.setPWM(1, 0, angleNeck(servoPos));
    delay(8);
    neckPos = servoPos;
    Serial.println(servoPos);
  }
}
void moveShoulder(int destAngle){
  for (int servoPos = shoulderPos; destAngle < shoulderPos; servoPos--) {
    pwm.setPWM(2, 0, angleShoulder(servoPos));
    delay(8);
    shoulderPos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = shoulderPos; destAngle > shoulderPos; servoPos++) {
    pwm.setPWM(2, 0, angleShoulder(servoPos));
    delay(8);
    shoulderPos = servoPos;
    Serial.println(servoPos);
  }
}
void moveElbow(int destAngle){
  for (int servoPos = elbowPos; destAngle < elbowPos; servoPos--) {
    pwm.setPWM(3, 0, angleElbow(servoPos));
    delay(8);
    elbowPos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = elbowPos; destAngle > elbowPos; servoPos++) {
    pwm.setPWM(3, 0, angleElbow(servoPos));
    delay(8);
    elbowPos = servoPos;
    Serial.println(servoPos);
  }
}
void moveWrist(int destAngle){
  for (int servoPos = wristPos; destAngle < wristPos; servoPos--) {
    pwm.setPWM(4, 0, angleWrist(servoPos));
    delay(8);
    wristPos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = wristPos; destAngle > wristPos; servoPos++) {
    pwm.setPWM(4, 0, angleWrist(servoPos));
    delay(8);
    wristPos = servoPos;
    Serial.println(servoPos);
  }
}
void moveClaw(int destAngle){
   for (int servoPos = clawPos; destAngle < clawPos; servoPos--) {
    pwm.setPWM(5, 0, angleClaw(servoPos));
    delay(8);
    clawPos = servoPos;
    Serial.println(servoPos);
  }
  for (int servoPos = clawPos; destAngle > clawPos; servoPos++) {
    pwm.setPWM(5, 0, angleClaw(servoPos));
    delay(8);
    clawPos = servoPos;
    Serial.println(servoPos);
  }
}

//ResetServos
void ResetServos()
{
  moveBase(90);
  moveElbow(0);
  moveNeck(90);
  moveShoulder(0);
  moveWrist(180);
  moveClaw(90);
} //End ResetServos.
