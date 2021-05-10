#include <Wire.h>

void setup()
{
  Wire.begin(9);                // join i2c bus with address #9
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);         // start serial for output
}

void loop()
{
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{ 
  byte left_hat_x_lsb = Wire.read();
  byte left_hat_x_msb = Wire.read();
  byte left_hat_y_lsb = Wire.read();
  byte left_hat_y_msb = Wire.read();

  int left_hat_x = (left_hat_x_msb << 8) | left_hat_x_lsb;
  int left_hat_y = (left_hat_y_msb << 8) | left_hat_y_lsb;

  Serial.print(F("\r\nLeftHatX: "));
  Serial.print(left_hat_x);
  Serial.print(F("\tLeftHatY: "));
  Serial.print(left_hat_y);
}
