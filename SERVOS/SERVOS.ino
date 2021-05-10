#include <Wire.h>
#include <Servo.h>

Servo panServo;   // create servo object to control a servo
Servo tiltServo;  // create servo object to control a servo
Servo fireServo;  // create servo object to control a servo

static volatile int right_hat_x;
static volatile int right_hat_y;
static volatile int r2_button;

void setup()
{
  panServo.attach(2);  
  tiltServo.attach(3);
  Wire.begin(9);                // join i2c bus with address #9
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);         // start serial for output
}

void loop()
{
  int my_right_hat_x, my_right_hat_y;
  
  noInterrupts();
    my_right_hat_x = right_hat_x;
    my_right_hat_y = right_hat_y;
  interrupts();
  
  panServo.write(my_right_hat_x);    
  tiltServo.write(my_right_hat_y);

  if(r2_button) {
    fireServo.attach(4);
  } else {
    fireServo.detach();
  }

  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{ 
  byte right_hat_x_lsb = Wire.read();
  byte right_hat_x_msb = Wire.read();
  byte right_hat_y_lsb = Wire.read();
  byte right_hat_y_msb = Wire.read();
  r2_button = Wire.read();

  right_hat_x = (right_hat_x_msb << 8) | right_hat_x_lsb;
  right_hat_y = (right_hat_y_msb << 8) | right_hat_y_lsb;
}
