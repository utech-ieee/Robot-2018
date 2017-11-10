#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

const uint8_t LEFT_MOTOR_IN1 = 8;
const uint8_t LEFT_MOTOR_IN2 = 9;
const uint8_t LEFT_MOTOR_PWM = 10;

const uint8_t RIGHT_MOTOR_PWM = 7;
const uint8_t RIGHT_MOTOR_IN1 = 6;
const uint8_t RIGHT_MOTOR_IN2 = 5;

Encoder leftEncoder(18, 19);
Encoder rightEncoder(20, 21);

long leftEncoderPosition;
long rightEncoderPosition;

void setup() 
{
  Serial.begin(9600);
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(LEFT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_PWM, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);
  Serial.println("Encoder Test");
}

void loop()
{
  leftEncoderPosition = leftEncoder.read();
  rightEncoderPosition = rightEncoder.read();

  Serial.print("Left Motor: ");
  Serial.print(leftEncoderPosition);
  Serial.print("  Right Motor: ");
  Serial.print(rightEncoderPosition);
  Serial.println();
  delay(1000);
  forward(70);
}

void forward(uint8_t speed)
{
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);

  analogWrite(LEFT_MOTOR_PWM, speed); 
  analogWrite(RIGHT_MOTOR_PWM, speed);
}

void reverse(uint8_t speed)
{
  digitalWrite(LEFT_MOTOR_IN1, LOW); 
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);

  analogWrite(LEFT_MOTOR_PWM, leftSpeed(speed)); 
  analogWrite(RIGHT_MOTOR_PWM, rightSpeed(speed));
}

void left(uint8_t speed)
{
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);

  digitalWrite(LEFT_MOTOR_PWM, leftSpeed(speed));
  digitalWrite(RIGHT_MOTOR_PWM, rightSpeed(speed));
}

void right(uint8_t speed)
{
  digitalWrite(LEFT_MOTOR_IN1, HIGH); 
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);

  analogWrite(LEFT_MOTOR_PWM, leftSpeed(speed));
  analogWrite(RIGHT_MOTOR_PWM, rightSpeed(speed));
}

void stop()
{
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  analogWrite(LEFT_MOTOR_PWM, 0);
  analogWrite(RIGHT_MOTOR_PWM, 0);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}


uint8_t leftSpeed(uint8_t speed)
{
  if (abs(leftEncoderPosition) > abs(rightEncoderPosition))
    return (leftEncoderPosition * speed / rightEncoderPosition);
    //(return speed - 50);
  return speed;
}

uint8_t rightSpeed(uint8_t speed)
{
  if (abs(rightEncoderPosition) > abs(leftEncoderPosition))
    return (rightEncoderPosition * speed / leftEncoderPosition);
    //return (speed - 50);
  return speed;
}


