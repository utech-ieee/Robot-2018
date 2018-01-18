#include <Stepper.h>

const int stepsPerRevolution = 200;
String value;
Stepper leftWheel(stepsPerRevolution, 8, 9, 10, 11);
Stepper rightWheel(stepsPerRevolution, 8, 9, 10, 11);


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
  
  leftWheel.step(stepsPerRevolution);
  rightWheel.step(stepsPerRevolution);

  setStepperSpeed(speed);
}

void reverse(uint8_t speed)
{
  Serial.println("Direction: Reverse");

  leftWheel.step(-stepsPerRevolution);
  rightWheel.step(-stepsPerRevolution);
  
  setStepperSpeed(speed);
}

void left(uint8_t speed)
{
  Serial.println("Direction: Left");
    
  leftWheel.step(-stepsPerRevolution);
  rightWheel.step(stepsPerRevolution);
 
  setStepperSpeed(speed);
}

void right(uint8_t speed)
{
  Serial.println("Direction: Right");
  
  leftWheel.step(stepsPerRevolution);
  rightWheel.step(-stepsPerRevolution);

  setStepperSpeed(speed);
}

void stop()
{
  Serial.println("Direction: Right");
  
  leftWheel.step(stepsPerRevolution);
  rightWheel.step(stepsPerRevolution);
 
  setStepperSpeed(0);
}

void setStepperSpeed(uint8_t speed)
{
  leftWheel.setSpeed(speed);
  rightWheel.setSpeed(speed);
}

