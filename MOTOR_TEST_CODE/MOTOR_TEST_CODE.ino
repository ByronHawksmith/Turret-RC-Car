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

// joystick pins
const int X_AX = A3; // analog pin 0 connected to X output of JoyStick
const int Y_AX = A2; // analog pin 1 connected to Y output of JoyStick
int x_pos;
int y_pos;

int rows = 0;

int motion = 0;

int motors[8] = {motorPin1, motorPin2, motorPin3, motorPin4, motorPin5, motorPin6, motorPin7, motorPin8};

//This will run only one time.
void setup(){
    Serial.begin(115200);
    //Set motor pins as outputs
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    pinMode(motorPin5, OUTPUT);
    pinMode(motorPin6, OUTPUT);
    pinMode(motorPin7, OUTPUT);
    pinMode(motorPin8, OUTPUT);
    
    pinMode(X_AX, INPUT);                     
    pinMode(Y_AX, INPUT);  
    showHeading();

}


void loop(){
x_pos = analogRead(X_AX);
y_pos = analogRead(Y_AX);

  Serial.print(x_pos);
  Serial.print("          ");
  Serial.println(y_pos);
  delay(100);
    if(y_pos == 0) {
      forward();
    }
    else if(y_pos == 255) {
      backward();
    }
    else if(x_pos == 0) {
      left();
    }
    else if(x_pos == 255) {
      right();
    }else {
      for (int i = 0; i < sizeof(motors) / sizeof(int); ++i){
        // Stop all Motors.
        digitalWrite(motors[i], LOW);
      }
    }
}

void forward()
{
  Serial.println("Forward!");
  for (int i = 0; i < sizeof(motors) / sizeof(int); ++i)
  {
    // Stop all Motors.
    digitalWrite(motors[i], LOW);
  }
  // Motor A clockwise.
  digitalWrite(motorPin2, HIGH);
  // Motor B counter-clockwise.
  digitalWrite(motorPin3, HIGH);
  // Motor C clockwise.
  digitalWrite(motorPin6, HIGH);
  // Motor D counter-clockwise.
  digitalWrite(motorPin7, HIGH);
}

void backward(){
  Serial.println("Backward!");
  for (int i = 0; i < sizeof(motors) / sizeof(int); ++i)
  {
    // Stop all Motors.
    digitalWrite(motors[i], LOW);
  }
  // Motor A counter-clockwise.
  digitalWrite(motorPin1, HIGH);
  // Motor B clockwise.
  digitalWrite(motorPin4, HIGH);
  // Motor C counter-clockwise.
  digitalWrite(motorPin5, HIGH);
  // Motor D clockwise.
  digitalWrite(motorPin8, HIGH);
}

void left(){
  Serial.println("Left!");
  for (int i = 0; i < sizeof(motors) / sizeof(int); ++i)
  {
    // Stop all Motors.
    digitalWrite(motors[i], LOW);
  }
  // Motor A clockwise.
  digitalWrite(motorPin2, HIGH);
  // Motor B clockwise.
  digitalWrite(motorPin4, HIGH);
  // Motor C clockwise.
  digitalWrite(motorPin6, HIGH);
  // Motor D clockwise.
  digitalWrite(motorPin8, HIGH);
}

void right(){
  for (int i = 0; i < sizeof(motors) / sizeof(int); ++i)
  {
    // Stop all Motors.
    digitalWrite(motors[i], LOW);
  }
  Serial.println("Right!");
  // Motor A counter-clockwise.
  digitalWrite(motorPin1, HIGH);
  // Motor B counter-clockwise.
  digitalWrite(motorPin3, HIGH);
  // Motor C counter-clockwise.
  digitalWrite(motorPin5, HIGH);
  // Motor D counter-clockwise.
  digitalWrite(motorPin7, HIGH);
}

void showHeading() {
  Serial.println("X axis      Y axis");
}
