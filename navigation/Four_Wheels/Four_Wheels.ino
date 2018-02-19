#include <Stepper.h>

// ================================================================
// ===               COMPASS SETUP                              ===
// ================================================================
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high
#define OUTPUT_READABLE_YAWPITCHROLL
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
float yaw;
float pitch;
float roll;
// ================================================================
// ===                                                          ===
// ================================================================

//INTERRUPT DETECTION ROUTINE
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() 
{
    mpuInterrupt = true;
}

const int stepsPerRevolution = 200;
int numOfSteps;
String direction;
String value;

Stepper frontLeft(stepsPerRevolution, 8, 9, 10, 11);
Stepper frontRight(stepsPerRevolution, 32, 34, 36, 38);
Stepper backLeft(stepsPerRevolution, 4, 5, 6, 8);
Stepper backRight(stepsPerRevolution, 22, 24, 26, 28);

void setup() 
{
  // ================================================================
  // ===                     COMPASS                              ===
  // ================================================================
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  Serial.begin(115200);
  while (!Serial); 
  mpu.initialize();
  devStatus = mpu.dmpInitialize();
  mpu.setXGyroOffset(62);
  mpu.setYGyroOffset(890);
  mpu.setZGyroOffset(-3);
  mpu.setZAccelOffset(1498); 

  if (devStatus == 0) 
  {
      mpu.setDMPEnabled(true);
      attachInterrupt(0, dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();
      dmpReady = true;
      packetSize = mpu.dmpGetFIFOPacketSize();
  } 
  else 
  {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      // Serial.print(F("DMP Initialization failed (code "));
      // Serial.print(devStatus);
      // Serial.println(F(")"));
  }
  // ================================================================
  // ===                     COMPASS                              ===
  // ================================================================
  setStepperSpeed(170);
  Serial.print("End\n");
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
  Serial.print("End\n");
 }
}

void forward(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    frontLeft.step(1);
    frontRight.step(-1);
    backLeft.step(1);
    backRight.step(-1);
  }
//  Serial.print("Direction: Forward | Number of Steps: ");
//  Serial.print(steps);
//  Serial.println();
}

void reverse(int steps)
{
  for (int i = 0; i < steps; ++i)
  {
    frontLeft.step(-1);
    frontRight.step(1);
    backLeft.step(-1);
    backRight.step(1);
  }
//  Serial.println("Direction: Reverse | Number of Steps: ");
//  Serial.print(steps);
//  Serial.println();
}

void left(int steps)
{
  getYawPitchRoll();
  for (int i = 0; i < (yaw + 90); ++i)
  {
    frontLeft.step(1);
    frontRight.step(1);
    backLeft.step(-1);
    backRight.step(-1);
  }
//  Serial.println("Direction: Left | Number of Steps: ");
//  Serial.print(steps);
//  Serial.println();
}

void right(int steps)
{
  getYawPitchRoll();
  for (int i = 0; i < (yaw + 90); ++i)
  {
    frontLeft.step(-1);
    frontRight.step(-1);
    backLeft.step(1);
    backRight.step(1);
  }
//  Serial.println("Direction: Right | Number of Steps: ");
//  Serial.print(steps);
//  Serial.println();
}

void stop()
{
  frontLeft.step(0);
  frontRight.step(0);
  backLeft.step(1);
  backRight.step(1);
//  Serial.println("Direction: Stop");
}

void setStepperSpeed(uint8_t speed)
{
  frontLeft.setSpeed(speed);
  frontRight.setSpeed(speed);
  backLeft.setSpeed(speed);
  backRight.setSpeed(speed);
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

void getYawPitchRoll() 
{
     // if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize);

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
    {
        // reset so we can continue cleanly
        mpu.resetFIFO();
    } 
    else if (mpuIntStatus & 0x02)
    {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

      // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      // Serial.print("ypr\t");
      // Serial.print(ypr[0] * 180/M_PI);
      // Serial.print("\t");
      // Serial.print(ypr[1] * 180/M_PI);
      // Serial.print("\t");
      // Serial.println(ypr[2] * 180/M_PI);
      
       yaw = ypr[0] * 180/M_PI;
       pitch = ypr[1] * 180/M_PI;
       roll = ypr[2] * 180/M_PI;
    }
}

