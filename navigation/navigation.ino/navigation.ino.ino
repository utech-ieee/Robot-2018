#include <Stepper.h>

const int stepsPerRevolution = 200;
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
    char* value = Serial.read();
    char* result = splitString("Jermaine,im, here", ",");
    Serial.println(result[0]);
    Serial.println(result[1]);
    switch(result[0])
    {
      case 0:
        forward(170);
        break;

      case 1:
        reverse(170);
        break;

      case 2:
        left(170);
        break;

       case 3:
        right(170);
        break;

       case 4:
        stop();
        break;
      
      default:
        break;
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

char* splitString(char* value, char* delimiter)
{
  char** res  = NULL;
  char*  p    = strtok (value, delimiter);
  int n_spaces = 0, i;
    
  while (p) 
  {
    res = realloc (res, sizeof (char*) * ++n_spaces);
  
    if (res == NULL)
      exit (-1); /* memory allocation failed */
  
    res[n_spaces-1] = p;
  
    p = strtok (NULL, " ");
  }
    
  res = realloc (res, sizeof (char*) * (n_spaces+1));
  res[n_spaces] = 0;
    
  return (char *)res; 
}

