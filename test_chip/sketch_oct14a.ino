#include <Wire.h>
#define PCF8574_I2C_ADDR  0x38
#define P0 0
#define P1 1
#define P2 2
#define P3 3
#define P4 4
#define P5 5
#define P6 6
#define P7 7

void setup() {
  Wire.begin();        // initialize the I2C/TWI interface
}


void loop() {
  // send the data to the LEDs
  turnPinLowOnPCF8574P(PCF8574_I2C_ADDR, P0);
  delay(200);
  turnPinLowOnPCF8574P(PCF8574_I2C_ADDR, P1);
  delay(200);
  turnPinLowOnPCF8574P(PCF8574_I2C_ADDR, P2);
  delay(200);
  turnPinLowOnPCF8574P(PCF8574_I2C_ADDR, P4);
  delay(200);
}

void turnPinLowOnPCF8574P(int chipI2CAddress, int pinNumber) {
  Wire.beginTransmission(chipI2CAddress);
  Wire.write(~(1 << pinNumber));
  Wire.endTransmission();
}
