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

uint8_t motorSpeed = 255; 
/***************************************
 ***************************************/


/***************************************
 *       ENCODER DECLARATIONS          *
 ***************************************/
Encoder frontleftEncoder(18, 32);
Encoder frontrightEncoder(19, 34);
Encoder backleftEncoder(20, 36);
Encoder backrightEncoder(21, 38);

long positionFrontLeft;
long positionFrontRight;
long positionBackLeft;
long positionBackRight;
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
//  Serial.write("1");z
   forward(10, 255);
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

 int temp1;
 int temp2;
 int temp3;

 int kp1 = 0.5; //FRONT_LEFT
 int kp2 = 0.2; //BACK_LEFT
 int kp3 = 0.5; //BACK_RIGHT
 
 //Master
 frontrightEncoder.write(0);

 //Slaves
 frontleftEncoder.write(0);
 backleftEncoder.write(0);
 backrightEncoder.write(0);

 //Monitor 'totalTicks', instead of the values of the encoders which are constantly reset.
 while(abs(totalTicks) < tickGoal)
 {
	//Master
	positionFrontRight = frontrightEncoder.read();
	//Slave
	positionFrontLeft = frontleftEncoder.read();
	positionBackLeft = backleftEncoder.read();
	positionBackRight = backrightEncoder.read();

	Serial.print("FRONT_RIGHT Encoder: ");
	Serial.print(positionFrontRight);
	Serial.println();

	Serial.print("FRONT_LEFT Encoder: ");
	Serial.print(positionFrontLeft);
	Serial.println();

	Serial.print("BACK_LEFT Encoder: ");
	Serial.print(positionBackLeft);
	Serial.println();

	Serial.print("BACK_RIGHT Encoder: ");
	Serial.print(positionBackRight);
	Serial.println();
	Serial.println();

	error1 = positionFrontRight - positionFrontLeft;
	error2 = positionFrontRight - positionBackLeft;
	error3 = positionFrontRight - positionBackRight;

	Serial.print("ERROR1/FRONT_LEFT: ");
	Serial.print(error1);
	Serial.println();

	Serial.print("ERROR2/BACK_LEFT: ");
	Serial.print(error2);
	Serial.println();

	Serial.print("ERROR3/BACK_RIGHT: ");
	Serial.print(error3);
	Serial.println();
	Serial.println();

	temp1 = (error1 / kp1);
	temp2 = (error2 / kp2);
	temp3 = (error3 / kp3);

	Serial.print("Temp1/FRONT_LEFT: ");
	Serial.print(temp1);
	Serial.println();

	Serial.print("Temp2/BACK_LEFT: ");
	Serial.print(temp2);
	Serial.println();

	Serial.print("Temp3/BACK_RIGHT: ");
	Serial.print(temp3);
	Serial.println();
	Serial.println();

	slavePower1 += temp1;
	slavePower2 += temp2;
	slavePower3 += temp3;

	Serial.print("FRONT_RIGHT_MOTOR_PWM: ");
	Serial.print(masterPower);
	Serial.println();

	Serial.print("FRONT_LEFT_MOTOR_PWM: ");
	Serial.print(slavePower1);
	Serial.println();

	Serial.print("BACK_LEFT_MOTOR_PWM: ");
	Serial.print(slavePower2);
	Serial.println();

	Serial.print("BACK_RIGHT_MOTOR_PWM: ");
	Serial.print(slavePower3);
	Serial.println();
	Serial.println();

	//Proportional algorithm to keep the robot going straight.
	//Master
	analogWrite(FRONT_RIGHT_MOTOR_PWM, masterPower);
	//Slave
	analogWrite(FRONT_LEFT_MOTOR_PWM, slavePower1);
	analogWrite(BACK_LEFT_MOTOR_PWM, slavePower2);
	analogWrite(BACK_RIGHT_MOTOR_PWM, slavePower3);

	//Master
	frontrightEncoder.write(0);

	//Slaves
	frontleftEncoder.write(0);
	backleftEncoder.write(0);
	backrightEncoder.write(0);

	// delay(10);

	//Add this iteration's encoder values to totalTicks.
	totalTicks+= positionFrontLeft;
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
