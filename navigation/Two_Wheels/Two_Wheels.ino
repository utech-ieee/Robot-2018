#include <Stepper.h>

const int stepsPerRevolution = 200;
int numOfSteps;
String direction;
String value;

Stepper leftWheel(stepsPerRevolution, 8, 9, 10, 11);
Stepper rightWheel(stepsPerRevolution, 4, 5, 6, 7);

void setup() 
{
  Serial.begin(9600);
  setStepperSpeed(170);
}

void loop()
{
 while (Serial.available()) 
 {
   split(Serial.readString());
   if(direction == "Move Forward")
   {
     forward(numOfSteps);
   }
   else if (direction == "Move Back")
   {
     reverse(numOfSteps);
   }
   else if (direction == "Move Left")
   {
     left(numOfSteps);
   }
   else if (direction == "Move Right")
   {
     right(numOfSteps);
   }
   else if(direction == "Stop")
   {
     stop();
   }
 }
}

void forward(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    leftWheel.step(1);
    rightWheel.step(-1);
  }
  Serial.print("Direction: Forward | Number of Steps: ");
  Serial.print(steps);
  Serial.println();
  Serial.println("Finished");
}

void reverse(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    leftWheel.step(-1);
    rightWheel.step(-1);
  }
  Serial.println("Direction: Reverse | Number of Steps: ");
  Serial.print(steps);
  Serial.println();
  Serial.println("Finished");
}

void left(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    leftWheel.step(-1);
    rightWheel.step(1);
  }
  Serial.println("Direction: Left | Number of Steps: ");
  Serial.print(steps);
  Serial.println();
  Serial.println("Finished");
}

void right(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    leftWheel.step(-1);
    rightWheel.step(1);
  }
  Serial.println("Direction: Right | Number of Steps: ");
  Serial.print(steps);
  Serial.println();
  Serial.println("Finished");
}

void stop()
{
  leftWheel.step(0);
  rightWheel.step(0);
  Serial.println("Direction: Stop");
  Serial.println("Finished");
}

void setStepperSpeed(uint8_t speed)
{
  leftWheel.setSpeed(speed);
  rightWheel.setSpeed(speed);
}

void split(String string)
{
  for (int i = 0; i < string.length(); i++) 
  {
    if (string.substring(i, i+1) == ",") 
    {
      direction = string.substring(0, i);
      numOfSteps = string.substring(i+1).toInt();
      break;
    }
  }
}

