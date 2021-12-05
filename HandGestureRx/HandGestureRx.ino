
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include "printf.h"

RF24 radio(9, 10);
const uint64_t addresses[2] = {0xF0F0F0F0A1LL};

#define m11 2 //Left Motor front
#define m12 4 //Left Motor back
#define m21 6 //Right Motor front
#define m22 7 //Right Motor front

#define LeftMotorSpeed 3  // Left motor PWM Speed Control
#define RightMotorSpeed 5  // Right motor PWM Speed Control


struct data {
  int xAxis;
  int yAxis;
};
data receive_data;
void setup() {
  Serial.begin(9600);
  radio.begin();
  printf_begin();
  radio.enableDynamicPayloads();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  radio.printDetails();

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);

}

void forward(int pwmOutput)
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  Serial.println(pwmOutput);
  analogWrite(LeftMotorSpeed, pwmOutput);
  analogWrite(RightMotorSpeed, pwmOutput);
}
void right(int pwmOutput)
{
  digitalWrite(m11, HIGH);
  digitalWrite(m12, LOW);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  analogWrite(LeftMotorSpeed, pwmOutput);
  analogWrite(RightMotorSpeed, pwmOutput);
}
void backward(int pwmOutput)
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, HIGH);
  digitalWrite(m22, LOW);
  analogWrite(LeftMotorSpeed, pwmOutput);
  analogWrite(RightMotorSpeed, pwmOutput);
}
void left(int pwmOutput)
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, HIGH);
  digitalWrite(m21, LOW);
  digitalWrite(m22, HIGH);
  analogWrite(LeftMotorSpeed, pwmOutput);
  analogWrite(RightMotorSpeed, pwmOutput);
}
void Stop()
{
  digitalWrite(m11, LOW);
  digitalWrite(m12, LOW);
  digitalWrite(m21, LOW);
  digitalWrite(m22, LOW);
}

void loop() {
  while (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    radio.read(&receive_data, len);
    Serial.println("accAngleX :     ");
    Serial.println(receive_data.xAxis);
    //    Serial.print("\taccAngleY :    ");
    //    Serial.println(receive_data.yAxis);


    if (receive_data.xAxis < -10 && receive_data.xAxis != -90 && receive_data.yAxis != 90)
    {
      forward(speed_control(receive_data.xAxis, -5, -40));

    }
    else if (receive_data.xAxis > 10 && receive_data.xAxis != -90 && receive_data.yAxis != 90)
    {
      backward(speed_control(receive_data.xAxis, 5, 40));
    }
    else if (receive_data.yAxis < -10 && receive_data.xAxis != -90 && receive_data.yAxis != 90)
    {
      left(speed_control(receive_data.yAxis, -5, -40));
    }
    else if (receive_data.yAxis > 10 && receive_data.xAxis != -90 && receive_data.yAxis != 90)
    {
      right(speed_control(receive_data.yAxis, 5, 40));
    }
    else if (receive_data.xAxis == -90 && receive_data.yAxis == 90)
    {
      Stop();
    }
    else {
      Stop();
    }
  }
}


int speed_control(int currentAngleValue, int min_angle, int max_angle )
{
    int pwmValue= map(currentAngleValue, min_angle, max_angle, 50, 255);
  if (pwmValue <=255) {
    Serial.println("IN IF");
    return pwmValue;
  } else {
    Serial.println("ELSE");
    return 255;
  }
}
