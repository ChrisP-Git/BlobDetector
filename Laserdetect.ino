#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x)  Serial.println(x)
#define DEBUG_PRINT(x)  Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

int lightPin = 0;  //define a pin for Photo resistor
int laserPin = 12;  //define a Pin for Laser LED
int greenPin = 11;
int orangePin = 9;
int redPin = 8;

int minOn = 0;
int minOff = 0;
int maxOn = 0;
int maxOff = 0;
int nbcalibpass = 10 ; // number of pass for light calibration

int threshold = 250;

void calibrateLaser(){
  int upval=0;
  int downval=0;
  int i;
  DEBUG_PRINTLN("Starting Laser calibration"); 
  OrangeOn();
  for (i=0 ; i < nbcalibpass ; i++ ){
    LaserOn();
    delay(250);
    upval = analogRead(lightPin);

    //get min and max value when laser is on
    if (maxOn == 0) {maxOn = upval;}
    else if (maxOn < upval) {maxOn = upval;}
    
    if (minOn == 0) {minOn = upval;}
    else if (minOn > upval) {minOn = upval;}
    DEBUG_PRINT("upval: ");
    DEBUG_PRINTLN(upval); 
    DEBUG_PRINT("minOn: ");
    DEBUG_PRINTLN(minOn); 
    DEBUG_PRINT("maxOn: ");
    DEBUG_PRINTLN(maxOn); 

    LaserOff();
    delay(250);
    downval = analogRead(lightPin);

        //get min and max value when laser is on
    if (maxOff == 0) {maxOff = downval;}
    else if (maxOff < downval) {maxOff = downval;}
    
    if (minOff == 0) {minOff = downval;}
    else if (minOff > downval) {minOff = downval;}
    DEBUG_PRINT("downval: ");
    DEBUG_PRINTLN(downval); 
    DEBUG_PRINT("minOff: ");
    DEBUG_PRINTLN(minOff); 
    DEBUG_PRINT("maxOff: ");
    DEBUG_PRINTLN(maxOff); 

  }

  threshold = (minOff + maxOn) / 2;
  DEBUG_PRINTLN("Laser calibration done"); 
  OrangeOff();
  
}

void LaserOn(){
  digitalWrite(laserPin, HIGH);
  DEBUG_PRINTLN("Switch On Laser"); 
}

void LaserOff(){
  digitalWrite(laserPin, LOW);
  DEBUG_PRINTLN("Switch Off Laser"); 
}

void RedOn(){
  digitalWrite(redPin, HIGH);
  DEBUG_PRINTLN("Switch On Red LED"); 
}

void RedOff(){
  digitalWrite(redPin, LOW);
  DEBUG_PRINTLN("Switch Off Red LED"); 
}

void OrangeOn(){
  digitalWrite(orangePin, HIGH);
  DEBUG_PRINTLN("Switch On Orange LED"); 
}

void OrangeOff(){
  digitalWrite(orangePin, LOW);
  DEBUG_PRINTLN("Switch Off Orange LED"); 
}

void GreenOn(){
  digitalWrite(greenPin, HIGH);
  DEBUG_PRINTLN("Switch On Orange LED"); 
}

void GreenOff(){
  digitalWrite(greenPin, LOW);
  DEBUG_PRINTLN("Switch Off Orange LED"); 
}


void setup(){
    Serial.begin(9600);  //Begin serial communcation
    pinMode(13, OUTPUT);
    pinMode(laserPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(orangePin, OUTPUT);
    pinMode(redPin, OUTPUT);

    calibrateLaser();
}

void loop(){
    DEBUG_PRINTLN(analogRead(lightPin)); 
 
    LaserOn();
    if(analogRead(lightPin) < threshold ){    
        digitalWrite(13, HIGH);
        GreenOn();
        DEBUG_PRINTLN("high"); 
    }else{
        digitalWrite(13, LOW);
        DEBUG_PRINTLN("low"); 
        RedOn();
        GreenOff();
    }

    DEBUG_PRINTLN(analogRead(lightPin)); 
    delay(1000);

    LaserOff();
    delay(250);


}
