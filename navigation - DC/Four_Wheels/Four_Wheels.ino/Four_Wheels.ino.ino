//#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <PID_v1.h>

const uint8_t FRONT_LEFT_MOTOR_IN1 = 24;
const uint8_t FRONT_LEFT_MOTOR_IN2 = 22;
const uint8_t FRONT_LEFT_MOTOR_PWM = 11;

const uint8_t FRONT_RIGHT_MOTOR_IN1 = 4;
const uint8_t FRONT_RIGHT_MOTOR_IN2 = 3;
const uint8_t FRONT_RIGHT_MOTOR_PWM = 12;

const uint8_t BACK_LEFT_MOTOR_IN1 = 6;
const uint8_t BACK_LEFT_MOTOR_IN2 = 5;
const uint8_t BACK_LEFT_MOTOR_PWM = 10;

const uint8_t BACK_RIGHT_MOTOR_IN1 = 9;
const uint8_t BACK_RIGHT_MOTOR_IN2 = 8;
const uint8_t BACK_RIGHT_MOTOR_PWM = 7;

Encoder frontleftEncoder(14, 15);
Encoder frontrightEncoder(16, 17);
Encoder backleftEncoder(18, 19);
Encoder backrightEncoder(20, 21);

long frontleftEncoderValue;
long frontrightEncoderValue;
long backleftEncoderValue;
long backrighEncoderValue;

double Setpoint, Input, Output;
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

PID frontleftPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
PID frontrightPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
PID backleftPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);
PID backrightPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);

void setup() 
{
  Serial.begin(9600);
  
  Setpoint = 255;

  //1
  Input = frontleftEncoder.read();
  frontleftPID.SetMode(AUTOMATIC);

  //2
  Input = frontrightEncoder.read();
  frontrightPID.SetMode(AUTOMATIC);

  //3
  Input = backleftEncoder.read();
  backleftPID.SetMode(AUTOMATIC);

  //4
  Input = backrightEncoder.read();
  backrightPID.SetMode(AUTOMATIC);
  
  pinMode(FRONT_LEFT_MOTOR_IN1, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_IN2, OUTPUT);
  pinMode(FRONT_LEFT_MOTOR_PWM, OUTPUT);

  pinMode(FRONT_RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(FRONT_RIGHT_MOTOR_IN2, LOW);
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
  forward(170);
//  readEncoders(); 
}

void forward(uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);
  
  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);
  
  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, LOW);
  
  setSpeed(speed);
}

void reverse(uint8_t speed)
{

  digitalWrite(FRONT_LEFT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_LEFT_MOTOR_IN1, LOW);
  digitalWrite(BACK_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(speed);
}

void left(uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, LOW);

  digitalWrite(BACK_LEFT_MOTOR_IN1, LOW);
  digitalWrite(BACK_LEFT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, LOW);

  setSpeed(speed);
}

void right(uint8_t speed)
{
  digitalWrite(FRONT_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(FRONT_LEFT_MOTOR_IN2, LOW);

  digitalWrite(FRONT_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(FRONT_RIGHT_MOTOR_IN2, HIGH);

  digitalWrite(BACK_LEFT_MOTOR_IN1, HIGH);
  digitalWrite(BACK_LEFT_MOTOR_IN2, LOW);

  digitalWrite(BACK_RIGHT_MOTOR_IN1, LOW);
  digitalWrite(BACK_RIGHT_MOTOR_IN2, HIGH);

  setSpeed(speed);
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

  setSpeed(0);
}

//void setSpeed(uint8_t speed)
//{
//  Setpoint = speed;
//
//  Input = frontleftEncoder.read();
//  frontleftPID.Compute();
//  analogWrite(FRONT_LEFT_MOTOR_PWM, Output);
//
//  Input = frontrightEncoder.read();
//  frontrightPID.Compute();
//  analogWrite(FRONT_RIGHT_MOTOR_PWM, Output);
//
//  Input = backleftEncoder.read();
//  backleftPID.Compute();
//  analogWrite(BACK_LEFT_MOTOR_PWM, Output);
//
//  Input = backrightEncoder.read();
//  backrightPID.Compute();
//  analogWrite(BACK_RIGHT_MOTOR_PWM, speed);
//}       

//void setSpeed(uint8_t speed)
//{
//  frontleftEncoderValue = frontleftEncoder.read();
//  frontrightEncoderValue = frontrightEncoder.read();
//  backleftEncoderValue = backleftEncoder.read();
//  backrighEncoderValue = backrightEncoder.read();
//
//}

 void setSpeed(uint8_t speed)
 {
   analogWrite(FRONT_LEFT_MOTOR_PWM, speed);
   analogWrite(FRONT_RIGHT_MOTOR_PWM, speed);
   analogWrite(BACK_LEFT_MOTOR_PWM, speed);
   analogWrite(BACK_RIGHT_MOTOR_PWM, speed);
 }   


void readEncoders()
{
  frontleftEncoderValue = frontleftEncoder.read();
  frontrightEncoderValue = frontrightEncoder.read();
  backleftEncoderValue = backleftEncoder.read();
  backrighEncoderValue = backrightEncoder.read();

  Serial.print("frontleftEncoderValue: ");
  Serial.print(frontleftEncoderValue);
  Serial.println();

  Serial.print("frontrightEncoderValue: ");
  Serial.print(frontrightEncoderValue);
  Serial.println();

  Serial.print("backleftEncoderValue: ");
  Serial.print(backleftEncoderValue);
  Serial.println();

  Serial.print("backrighEncoderValue: ");
  Serial.print(backrighEncoderValue);
  Serial.println();
  Serial.println();

  delay(2000);

}
