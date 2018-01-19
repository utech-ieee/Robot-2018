#include <Stepper.h>

const int stepsPerRevolution = 200;
String value;
Stepper leftWheel(stepsPerRevolution, 8, 9, 10, 11);
Stepper rightWheel(stepsPerRevolution, 4, 5, 6, 7);


void setup() 
{
  Serial.begin(9600);
}

void loop()
{
 while (Serial.available()) 
 {
   value = Serial.readString();
   if(value == "Move Forward")
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
  setStepperSpeed(speed);
  for (int i = 0; i < stepsPerRevolution; ++i)
  {
    if (isDirectionChanged("Move Forward"))
    {
      break;
    }
    leftWheel.step(1);
    rightWheel.step(-1);
  }
  Serial.println("Direction: Forward");
}

void reverse(uint8_t speed)
{
  setStepperSpeed(speed);
  for (int i = 0; i < stepsPerRevolution; ++i)
  {
    if (isDirectionChanged("Move Back"))
    {
      break;
    }
    leftWheel.step(-1);
    rightWheel.step(-1);
  }
  Serial.println("Direction: Reverse");
}

void left(uint8_t speed)
{
  setStepperSpeed(speed);
  for (int i = 0; i < stepsPerRevolution; ++i)
  {
    if (isDirectionChanged("Move Left"))
    {
      break;
    }
    leftWheel.step(-1);
    rightWheel.step(1);
  }
  Serial.println("Direction: Left");
}

void right(uint8_t speed)
{
  setStepperSpeed(speed);
  for (int i = 0; i < stepsPerRevolution; ++i)
  {
    if (isDirectionChanged("Move Right"))
    {
      break;
    }
    leftWheel.step(-1);
    rightWheel.step(1);
  }
  Serial.println("Direction: Right");
}

void stop()
{
  setStepperSpeed(0);
  leftWheel.step(0);
  rightWheel.step(0);
  Serial.println("Direction: Stop");
}

void setStepperSpeed(uint8_t speed)
{
  leftWheel.setSpeed(speed);
  rightWheel.setSpeed(speed);
}

bool isDirectionChanged(String currentDirection)
{
  if (Serial.available()) 
  {
    value = Serial.readString();
    if (value == currentDirection)
    {
      return false;
    }
    else 
    {
      if (value == "Move forward") 
      {
        return true;
      } 
      else if (value == "Move Back") 
      {
        return true;
      } 
      else if (value == "Move Left") 
      {
        return true;
      } 
      else if (value == "Move Right") 
      {
        return true;
      } 
      else if (value == "Stop") 
      {
        return true;
      }
    }
  }
  return false;
}
