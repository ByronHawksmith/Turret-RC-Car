#include <Wire.h>

//L293D
//Motor A
const int motorPin1 = 12;  // Pin 10 of L293D
const int motorPin2 = 13;  // Pin 15 of L293D

//Motor B
const int motorPin3 = 8;   // Pin 2 of L293D
const int motorPin4 = 11;  // Pin 7 of L293D

//Motor C
const int motorPin5 = 4;  // Pin 10 of L293D
const int motorPin6 = 7; // Pin 15 of L293D

//Motor D
const int motorPin7 = 2;  // Pin 2 of L293D
const int motorPin8 = 3;  // Pin 7 of L293D

int motors[8] = {motorPin1, motorPin2, motorPin3, motorPin4, motorPin5, motorPin6, motorPin7, motorPin8};

//This will run only one time.
void setup(){
//    Serial.begin(115200);         // start serial for output
    //Set motor pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(motorPin5, OUTPUT);
    pinMode(motorPin6, OUTPUT);
    pinMode(motorPin7, OUTPUT);
    pinMode(motorPin8, OUTPUT);

    Wire.begin(8);                // join i2c bus with address #9
    Wire.onReceive(receiveEvent); // register event
}


void loop(){
  
}

void forward(){
  stopMotors();
//  Serial.println("Forward!");
  // Motor A clockwise.
  digitalWrite(motorPin2, HIGH);
  // Motor B counter-clockwise.
  digitalWrite(motorPin3, HIGH);
  // Motor C clockwise.
  digitalWrite(motorPin6, HIGH);
  // Motor D counter-clockwise.
  digitalWrite(motorPin7, HIGH);
//  delay(500);
}

void backward(){
  stopMotors();
//  Serial.println("Backward!");
  // Motor A counter-clockwise.
  digitalWrite(motorPin1, HIGH);
  // Motor B clockwise.
  digitalWrite(motorPin4, HIGH);
  // Motor C counter-clockwise.
  digitalWrite(motorPin5, HIGH);
  // Motor D clockwise.
  digitalWrite(motorPin8, HIGH);
//  delay(500);
}

void left(){
  stopMotors();
//  Serial.println("Left!");
  // Motor A clockwise.
  digitalWrite(motorPin2, HIGH);
  // Motor B clockwise.
  digitalWrite(motorPin4, HIGH);
  // Motor C clockwise.
  digitalWrite(motorPin6, HIGH);
  // Motor D clockwise.
  digitalWrite(motorPin8, HIGH);
//  delay(500);
}

void right(){
  stopMotors();
//  Serial.println("Right!");
  // Motor A counter-clockwise.
  digitalWrite(motorPin1, HIGH);
  // Motor B counter-clockwise.
  digitalWrite(motorPin3, HIGH);
  // Motor C counter-clockwise.
  digitalWrite(motorPin5, HIGH);
  // Motor D counter-clockwise.
  digitalWrite(motorPin7, HIGH);
//  delay(500);
}

void stopMotors() {
  for (int i = 0; i < sizeof(motors) / sizeof(int); ++i){
    // Stop all Motors.
    digitalWrite(motors[i], LOW);
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  byte left_hat_x_lsb = Wire.read();
  byte left_hat_x_msb = Wire.read();
  byte left_hat_y_lsb = Wire.read();
  byte left_hat_y_msb = Wire.read();

  int x_pos = (left_hat_x_msb << 8) | left_hat_x_lsb;
  int y_pos = (left_hat_y_msb << 8) | left_hat_y_lsb;

  if(y_pos < 115) {
    forward();
  } else if (y_pos > 140) {
    backward();
  } else if (x_pos < 115) {
    left();
  } else if (x_pos > 140) {
    right();
  } else {
    stopMotors();
  }
}
