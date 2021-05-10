#include <PS4BT.h>
#include <Wire.h>

USB Usb;
BTD Btd(&Usb);
PS4BT PS4(&Btd, PAIR);

void setup() {
  Serial.begin(115200);

  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  
  Serial.print(F("\r\nPS4 Bluetooth Library Started"));

  Wire.begin();
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    int left_hat_x = PS4.getAnalogHat(LeftHatX);
    int left_hat_y = PS4.getAnalogHat(LeftHatY);

    byte left_hat_x_lsb = left_hat_x & 0xff;
    byte left_hat_x_msb = left_hat_x >> 8;
    byte left_hat_y_lsb = left_hat_y & 0xff;
    byte left_hat_y_msb = left_hat_y >> 8;

    byte left_hat_bytes[] = {
      left_hat_x_lsb,
      left_hat_x_msb,
      left_hat_y_lsb,
      left_hat_y_msb
    };
    
    Wire.beginTransmission(8);                            // transmit to device #8
    Wire.write(left_hat_bytes, sizeof(left_hat_bytes));   // send bytes for left hat
    Wire.endTransmission();                               // stop transmitting

    Wire.beginTransmission(9);                            // transmit to device #8
    Wire.write(left_hat_bytes, sizeof(left_hat_bytes));   // send bytes for left hat
    Wire.endTransmission();                               // stop transmitting
  }
}
