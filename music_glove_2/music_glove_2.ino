// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include <Wire.h>
const int numReadings = 10;
const int MPU_addr = 0x68;                                    // I2C address of the MPU-6050
int32_t AcX[numReadings], AcY[numReadings], AcZ[numReadings]; // Max Ac value = 32767
int32_t AcXtotal, AcYtotal, AcZtotal;
int32_t AcXav, AcYav, AcZav;
int readIndex = 0; // the index of the current reading

void setup()
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

  // Set all reading array values to 0
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  {
    AcX[thisReading] = 0;
    AcY[thisReading] = 0;
    AcZ[thisReading] = 0;
  }
}
void loop()
{
  // Subtract last reading
  AcXtotal = AcXtotal - AcX[readIndex];
  AcYtotal = AcYtotal - AcY[readIndex];
  AcZtotal = AcZtotal - AcZ[readIndex];

  // Read values
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 6, true);             // request a total of 14 registers
  AcX[readIndex] = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY[readIndex] = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ[readIndex] = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  // AcX[readIndex] = AcX[readIndex] + 5000;
  // AcY[readIndex] = AcY[readIndex] + 5000;
  // AcZ[readIndex] = AcZ[readIndex] + 5000;
  // Add reading to total
  AcXtotal = AcXtotal + AcX[readIndex];
  AcYtotal = AcYtotal + AcY[readIndex];
  AcZtotal = AcZtotal + AcZ[readIndex];

  // Increment readIndex
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings)
  {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // Calculate averages
  AcXav = AcXtotal / numReadings;
  AcYav = AcYtotal / numReadings;
  AcZav = AcZtotal / numReadings;

  // AcXav = map(AcXav, 0, 32767, 0, 127);
  // AcYav = map(AcYav, 0, 32767, 0, 127);
  // AcZav = map(AcZav, 0, 32767, 0, 127);
  Serial.print(AcXav);
  Serial.print(" ");
  Serial.print(AcYav);
  Serial.print(" ");
  Serial.println(AcZav);

  delay(1);
}
