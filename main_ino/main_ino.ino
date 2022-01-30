#include <Wire.h>

//Distance measurement with HC-SR04 and gyroscope MPU 6050
const int TRIGGER_PORT = 4;
const int ECHO_PORT = 5;

const int MPU = 0x68; //I2C address of MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER_PORT, OUTPUT);
  pinMode(ECHO_PORT, INPUT);

  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

  Serial.begin(9600);
  Serial.println("Ultrasonic measurement of distances\n\n");

}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

//  Serial.print("Accelerometer: ");
//  Serial.print("X = "); Serial.print(AcX);
//  Serial.print(" | Y = "); Serial.print(AcY);
//  Serial.print(" | Z = "); Serial.println(AcZ);

//  equation for temperature in degrees C from datasheet
//  Serial.print("Temperature: "); Serial.print(Tmp / 340.00 + 36.53); Serial.println(" C ");
  
  digitalWrite(TRIGGER_PORT, LOW);
  //10 micro-seconds beam on trigger
  digitalWrite(TRIGGER_PORT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PORT, LOW);

  long duration = pulseIn(ECHO_PORT, HIGH);
  long distance = 0.034 * duration / 2;

  //SERIAL PRINTING FORMAT-> X Y Z DISTANCE
  Serial.print(GyX);
  Serial.print(" ");
  Serial.print(GyY);
  Serial.print(" ");
  Serial.print(GyZ);
  Serial.print(" ");

  //case out of range
  if ( duration > 38000 ) {
    Serial.println("Out of range   ");
  }
  else {
    Serial.println(distance);
  }

  delay(1000);

}
