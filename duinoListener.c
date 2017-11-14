/*
  Arduinio Listener for Raspberry Pi
*/
char val;

#define BLUE 11
#define RED 12
#define GREEN 13

void setup() {
  // initialize serial:
  Serial.begin(9600);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    val = Serial.read();
    switch(val){
      case 'r':
          allOff();
         digitalWrite(RED, HIGH);
         break;

      case 'g':
          allOff();
         digitalWrite(GREEN, HIGH);
         break;

      case 'b':
          allOff();
         digitalWrite(BLUE, HIGH);
         break;

      case 'w':
          allOff();
         allOn();
         break;

      case 't':
          messItUp();
          break;


        case 'f':
          unsigned int rgbColour[3];

          // Start off with red.
          rgbColour[0] = 255;
          rgbColour[1] = 0;
          rgbColour[2] = 0;  

          // Choose the colours to increment and decrement.
          for (int decColour = 0; decColour < 3; decColour += 1) {
            int incColour = decColour == 2 ? 0 : decColour + 1;

            // cross-fade the two colours.
            for(int i = 0; i < 255; i += 1) {
              rgbColour[decColour] -= 1;
              rgbColour[incColour] += 1;
              
              setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
              delay(5);
            }
          }
          break;

      default:
         break;
    }
  }
}


void allOff(){
  digitalWrite(BLUE,LOW);
  digitalWrite(RED,LOW);
  digitalWrite(GREEN,LOW);
}


void allOn(){
  digitalWrite(BLUE,HIGH);
  digitalWrite(RED,HIGH);
  digitalWrite(GREEN,HIGH);
}

void messItUp(){
    for (int i = 0; i < 1000; ++i)
    {
          digitalWrite(BLUE,HIGH);
          delay(100);
          allOff();
          delay(100);
          digitalWrite(RED,HIGH);
          delay(100);
          allOff();
          delay(100);
          digitalWrite(GREEN,HIGH);
          delay(100);
          allOff();
          delay(100);
    }

  
}


void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(RED, red);
  analogWrite(GREEN, green);
  analogWrite(BLUE, blue);
 }