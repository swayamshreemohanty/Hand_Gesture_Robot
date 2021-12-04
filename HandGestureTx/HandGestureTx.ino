
#include <MPU6050_tockn.h>
#include <Wire.h>
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include "printf.h"


MPU6050 mpu6050(Wire);
RF24 radio(9, 10);
const uint64_t addresses[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

struct data {
  float xAxis;
  float yAxis;
};
data send_data;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  printf_begin();
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(addresses[0]);
  radio.stopListening();
  radio.printDetails();
}

void loop() {
  mpu6050.update();
  Serial.print("accAngleX : "); Serial.print(mpu6050.getAccAngleX());
  Serial.print("\taccAngleY : "); Serial.println(mpu6050.getAccAngleY());
  send_data.xAxis = mpu6050.getAccAngleX();
  send_data.yAxis = mpu6050.getAccAngleY();
  delay(100);
  radio.write(&send_data, sizeof(data));
}
