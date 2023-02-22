#include "SparkFun_LIS331.h"
#include <Wire.h>

LIS331 xl;

const float minX=-1, maxX=1;
const float minY=-1, maxY=1;
const float minZ=-1, maxZ=1;

float x, y, z;
int cc1, cc2, cc3;

void setup() {
  setupAccel();
}

void loop() {
  static long loopTimer = 0;
  if (millis() - loopTimer > 10) { // Send data every 10 ms
    int16_t x, y, z;
    loopTimer = millis();
    xl.readAxes(x, y, z);

    cc1 = mapf(xl.convertToG(6, x), minX, maxX, 0, 127);
    cc2 = mapf(xl.convertToG(6, y), minY, maxY, 0, 127);
    cc3 = mapf(xl.convertToG(6, z), minZ, maxZ, 0, 127);
    
    usbMIDI.sendControlChange(20, cc1, 1);
    usbMIDI.sendControlChange(21, cc2, 1);
    usbMIDI.sendControlChange(22, cc3, 1);
  }
}

void setupAccel(){
  pinMode(20, INPUT);       // Interrupt pin input
  Wire.begin();
  xl.setI2CAddr(0x19);    // This MUST be called BEFORE .begin() so 
                          //  .begin() can communicate with the chip
  xl.begin(LIS331::USE_I2C); // Selects the bus to be used and sets
                          //  the power up bit on the accelerometer.
                          //  Also zeroes out all accelerometer
                          //  registers that are user writable.
  // This next section configures an interrupt. It will cause pin
  //  INT1 on the accelerometer to go high when the absolute value
  //  of the reading on the Z-axis exceeds a certain level for a
  //  certain number of samples.
  xl.intSrcConfig(LIS331::INT_SRC, 1); // Select the source of the
                          //  signal which appears on pin INT1. In
                          //  this case, we want the corresponding
                          //  interrupt's status to appear. 
  xl.setIntDuration(50, 1); // Number of samples a value must meet
                          //  the interrupt condition before an
                          //  interrupt signal is issued. At the
                          //  default rate of 50Hz, this is one sec.
  xl.setIntThreshold(2, 1); // Threshold for an interrupt. This is
                          //  not actual counts, but rather, actual
                          //  counts divided by 16.
  xl.enableInterrupt(LIS331::Z_AXIS, LIS331::TRIG_ON_HIGH, 1, true);
                          // Enable the interrupt. Parameters indicate
                          //  which axis to sample, when to trigger
                          //  (in this case, when the absolute mag
                          //  of the signal exceeds the threshold),
                          //  which interrupt source we're configuring,
                          //  and whether to enable (true) or disable
                          //  (false) the interrupt.
}

float mapf(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  float result;
  result = (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
  return result;
} 
