#include <Stepper.h>

const int stepsPerRevolution = 200;
char value;
Stepper frontLeft(stepsPerRevolution, 8, 9, 10, 11);
Stepper frontRight(stepsPerRevolution, 8, 9, 10, 11);
Stepper backLeft(stepsPerRevolution, 8, 9, 10, 11);
Stepper backRight(stepsPerRevolution, 8, 9, 10, 11);


void setup() 
{
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available()) 
  {
    value = Serial.readString();
    if(value == "Move forward")
    {
      forward(170);
    }
    else if (value == "Move Back")
    {
      reverse(170);
    }
    else if (value == "Move Left")
    {
      left(170);
    }
    else if (value == "Move Right")
    {
      right(170);
    }
    else if(value == "Stop")
    {
      stop();
    }
  }
}

void forward(uint8_t speed)
{
  Serial.println("Direction: Forward");
  
  frontLeft.step(stepsPerRevolution);
  frontRight.step(stepsPerRevolution);
  backLeft.step(stepsPerRevolution);
  backRight.step(stepsPerRevolution);
  
  setStepperSpeed(speed);
}

void reverse(uint8_t speed)
{
  Serial.println("Direction: Reverse");

  frontLeft.step(-stepsPerRevolution);
  frontRight.step(-stepsPerRevolution);
  backLeft.step(-stepsPerRevolution);
  backRight.step(-stepsPerRevolution);
  
  setStepperSpeed(speed);
}

void left(uint8_t speed)
{
  Serial.println("Direction: Left");
    
  frontLeft.step(-stepsPerRevolution);
  frontRight.step(stepsPerRevolution);
  backLeft.step(-stepsPerRevolution);
  backRight.step(stepsPerRevolution);
  
  setStepperSpeed(speed);
}

void right(uint8_t speed)
{
  Serial.println("Direction: Right");
  
  frontLeft.step(stepsPerRevolution);
  frontRight.step(-stepsPerRevolution);
  backLeft.step(stepsPerRevolution);
  backRight.step(-stepsPerRevolution);

  setStepperSpeed(speed);
}

void stop()
{
  Serial.println("Direction: Right");
  
  frontLeft.step(stepsPerRevolution);
  frontRight.step(stepsPerRevolution);
  backLeft.step(stepsPerRevolution);
  backRight.step(stepsPerRevolution);

  setStepperSpeed(0);
}

void setStepperSpeed(uint8_t speed)
{
  frontLeft.setSpeed(speed);
  frontRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  backRight.setSpeed(speed);
}

