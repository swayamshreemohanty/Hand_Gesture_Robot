
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include "printf.h"

RF24 radio(9, 10);
const uint64_t addresses[2] = {0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL};

struct data {
  int xAxis;
  int yAxis;
};
data receive_data;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.enableDynamicPayloads();
  printf_begin();
//  radio.setRetries(5, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, addresses[1]);
  radio.startListening();
  radio.printDetails();
}

void loop() {
  while (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    radio.read(&receive_data, len);
    Serial.print("accAngleX : ");
    Serial.print(receive_data.xAxis);
    Serial.print("\taccAngleY : ");
    Serial.println(receive_data.yAxis);
  }
}
