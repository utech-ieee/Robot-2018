//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Servo.h>

/***************************************
 *    COMMUNICATION DECLARATIONS       *
 ***************************************/
int numOfTurns;
String direction;
/***************************************
 ***************************************/

/***************************************
 *         SERVO DECLARATIONS          *
 ***************************************/
Servo spinWheel;
unsigned long previousMillis = 0;
int wheelPin = 12;
/***************************************
 ***************************************/

/***************************************
 *         MOTOR DECLARATIONS          *
 ***************************************/
const uint8_t FRONT_LEFT_MOTOR_IN1 = 24;
const uint8_t FRONT_LEFT_MOTOR_IN2 = 22;
const uint8_t FRONT_LEFT_MOTOR_PWM = 12;

const uint8_t FRONT_RIGHT_MOTOR_IN1 = 5;
const uint8_t FRONT_RIGHT_MOTOR_IN2 = 4;
const uint8_t FRONT_RIGHT_MOTOR_PWM = 13;

const uint8_t BACK_LEFT_MOTOR_IN1 = 7;
const uint8_t BACK_LEFT_MOTOR_IN2 = 6;
const uint8_t BACK_LEFT_MOTOR_PWM = 11;

const uint8_t BACK_RIGHT_MOTOR_IN1 = 10;
const uint8_t BACK_RIGHT_MOTOR_IN2 = 9;
const uint8_t BACK_RIGHT_MOTOR_PWM = 8;

uint8_t motorSpeed = 170; 
/***************************************
 ***************************************/


/***************************************
 *       ENCODER DECLARATIONS          *
 ***************************************/
Encoder frontleftEncoder(14, 15);
Encoder frontrightEncoder(16, 17);
Encoder backleftEncoder(18, 19);
Encoder backrightEncoder(20, 21);

long positionFrontLeft  = -999;
long positionFrontRight = -999;
long positionBackLeft  = -999;
long positionBackRight = -999;
/***************************************
 ***************************************/
 
void setup() 
{
  Serial.begin(9600);

  /***************************************
   *               MOTOR                 *
   ***************************************/
  pinMode(FRONT_LEFT_MOTOR_IN1, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_IN2, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_PWM, OUTPUT);

  pinMode(FRONT_RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_PWM, OUTPUT);

  pinMode(BACK_LEFT_MOTOR_IN1, OUTPUT);
  pinMode(BACK_LEFT_MOTOR_IN2, OUTPUT);
  pinMode(BACK_LEFT_MOTOR_PWM, OUTPUT);

  pinMode(BACK_RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_IN2, OUTPUT);
  pinMode(BACK_RIGHT_MOTOR_PWM, OUTPUT);
}

void loop()
{
//  split(Serial.readString());
//  if(direction == "FORWARD")
//  {
//    forward(numOfTurns, motorSpeed);
//  }
//  else if (direction == "BACK")
//  {
//    reverse(numOfTurns, motorSpeed);
//  }
//  else if (direction == "LEFT")
//  {
//    left(numOfTurns, motorSpeed);
//  }
//  else if (direction == "RIGHT")
//  {
//    right(numOfTurns, motorSpeed);
//  }
//  else if (direction == "REVERSELEFT")
//  {
//    reverseLeft(numOfTurns, motorSpeed);
//  }
//  else if (direction == "REVERSERIGHT")
//  {
//    reverseRight(numOfTurns, motorSpeed);
//  }
//  else if(direction == "STOP")
//  {
//    stop();
//  }
//  else if(direction == "TURNFLAG")
//  {
//    raiseFlag(numOfTurns);
//  }
//  Serial.write("1");
   forward(0, 170);
   readEncoders();
}

void forward(int distance, uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);
  
  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);
  
  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, LOW);
  
  setSpeed(distance, speed);
}

void reverse(int distance, uint8_t speed)
{

  digitalWrite(FRONT_LEFT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_LEFT_MOTOR_IN1, LOW);
  digitalWrite(BACK_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(distance, speed);
}

void left(int distance, uint8_t speed)
{
//  digitalWrite(FRONT_LEFT_MOTOR_IN1, LOW);
//  digitalWrite(FRONT_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);

//  digitalWrite(BACK_LEFT_MOTOR_IN1, LOW);
//  digitalWrite(BACK_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, LOW);

  setSpeed(distance, speed);
}

void right(int distance, uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, LOW);

  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(distance, speed);
}

void reverseLeft(int distance, uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, HIGH);
  
  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);
  
  digitalWrite(BACK_LEFT_MOTOR_IN1, LOW);
  digitalWrite(BACK_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, LOW);

  setSpeed(distance, speed);
}

void reverseRight(int distance, uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);
  
  digitalWrite(FRONT_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, LOW);
  
  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(distance, speed);
}

void stop()
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(0, 0);
}       

//void setSpeed(int distance, uint8_t speed)
//{
// analogWrite(FRONT_LEFT_MOTOR_PWM, speed);
// analogWrite(FRONT_RIGHT_MOTOR_PWM, speed);
// analogWrite(BACK_LEFT_MOTOR_PWM, speed);
// analogWrite(BACK_RIGHT_MOTOR_PWM, speed);
//}   

void setSpeed(int tenthsOfIn, int masterPower)
{
  int tickGoal = (42 * tenthsOfIn) / 10;
 
  //This will count up the total encoder ticks despite the fact that the encoders are constantly reset.
  int totalTicks = 0;
 
  //Initialise slavePower as masterPower - 5 so we don't get huge error for the first few iterations. The
  //-5 value is based off a rough guess of how much the motors are different, which prevents the robot from
  //veering off course at the start of the function.
  int slavePower1 = masterPower - 5; 
  int slavePower2 = masterPower - 5;
  int slavePower3 = masterPower - 5;

  int error1 = 0;
  int error2 = 0;
  int error3 = 0;

  int kp1 = 5;
  int kp2 = 5;
  int kp3 = 5;
  
  //Master
  frontleftEncoder.write(0);

  //Slaves
  frontrightEncoder.write(0);
  backleftEncoder.write(0);
  backrightEncoder.write(0);
 
  //Monitor 'totalTicks', instead of the values of the encoders which are constantly reset.
  while(abs(totalTicks) < tickGoal)
  {
    //Proportional algorithm to keep the robot going straight.
    analogWrite(FRONT_LEFT_MOTOR_PWM, masterPower);
    analogWrite(FRONT_RIGHT_MOTOR_PWM, slavePower1);
    analogWrite(BACK_LEFT_MOTOR_PWM, slavePower2);
    analogWrite(BACK_RIGHT_MOTOR_PWM, slavePower3);

  
    positionFrontLeft = frontleftEncoder.read();
    positionFrontRight = frontrightEncoder.read();
    positionBackLeft = backleftEncoder.read();
    positionBackRight = backrightEncoder.read();

    error1 = positionFrontLeft - positionFrontRight;
    error2 = positionFrontLeft - positionBackLeft;
    error3 = positionFrontLeft - positionBackRight;

    slavePower1 += error1 / kp1;
    slavePower2 += error2 / kp2;
    slavePower3 += error3 / kp3;
    
    //Master
    frontleftEncoder.write(0);

    //Slaves
    frontrightEncoder.write(0);
    backleftEncoder.write(0);
    backrightEncoder.write(0);

    delay(100);
 
    //Add this iteration's encoder values to totalTicks.
    totalTicks+= SensorValue[leftEncoder];
  }
  // Stop the loop once the encoders have counted up the correct number of encoder ticks.
  analogWrite(FRONT_LEFT_MOTOR_PWM, 0);
  analogWrite(FRONT_RIGHT_MOTOR_PWM, 0);
  analogWrite(BACK_LEFT_MOTOR_PWM, 0);
  analogWrite(BACK_RIGHT_MOTOR_PWM, 0);
}

void raiseFlag(int turns) 
{
  spinWheel.attach(wheelPin);
  long interval = long(1170*turns);  
  unsigned long currentMillis = millis();  
  while (true)
  {
    previousMillis = currentMillis;
    spinWheel.write(180);
    if (currentMillis - previousMillis >= interval) 
    {
      spinWheel.detach();
      break;
    }
  }
}

void readEncoders()
{
  long newFrontLeft;
  long newFrontRight;
  long newBackLeft;
  long newBackRight;

  newFrontLeft = frontleftEncoder.read(); 
  newFrontRight = frontrightEncoder.read();
  newBackLeft = backleftEncoder.read();
  newBackRight = backrightEncoder.read();


  if (newFrontLeft != positionFrontLeft || newFrontRight != positionFrontRight || newBackLeft != positionBackLeft || newBackRight != positionBackRight) 
  {
    Serial.print("Front Left = ");
    Serial.print(newFrontLeft);

    Serial.print(", Front Right = ");
    Serial.print(newFrontRight);

    Serial.print(", Back Left = ");
    Serial.print(newBackLeft);

    Serial.print(", Back Right = ");
    Serial.print(newBackRight);

    Serial.println();

    positionFrontLeft = newFrontLeft;
    positionFrontRight = newFrontRight;
    positionBackLeft = newBackLeft;
    positionBackRight = newBackRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) 
  {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    frontleftEncoder.write(0); 
    frontrightEncoder.write(0);
    backleftEncoder.write(0);
    backrightEncoder.write(0);
  }
}

void split(String string)
{
  for (int i = 0; i < string.length(); i++) 
  {
    if (string.substring(i, i+1) == ",") 
    {
      direction = string.substring(0, i);
      numOfTurns = string.substring(i+1).toInt();
      break;
    }
  }
}

