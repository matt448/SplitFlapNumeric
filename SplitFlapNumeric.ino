
#include <Stepper.h>

int sensorPin = 8;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorState = 0;  // variable to store the value coming from the sensor
bool foundZero = false;

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  // set the speed at 60 rpm:
  myStepper.setSpeed(15);
  // initialize the serial port:
  Serial.begin(115200);
  Serial.println("Starting program");
  findZero();
  delay(1000);
}

void loop() {

moveSteps(103,10);
delay(2000);
/*
  if(foundZero){
    delay(5000);
    myStepper.step(-stepsPerRevolution);
  }else{
    myStepper.step(-1);
    readSensor();
  }
  
  
  */
}


void disableMotor(){
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW); 
}

void moveSteps(int steps, float delayVal){
  for(int i = 0; i < steps; ++i){
    myStepper.step(-1);
    delay(delayVal); 
  }
}

void findZero(){
  foundZero = false;
  while(foundZero == false){
    myStepper.step(-1);
    delay(2);
    readSensor();
  }
  moveSteps(30,25);
  Serial.println("> found zero");
}

void readSensor(){
  // read the value from the sensor:
  sensorState = digitalRead(sensorPin);
  if (sensorState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    foundZero = true;
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    foundZero = false;
  }
  //Serial.print("Value: ");
  //Serial.println(sensorState);
}

