
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

//Custom data type
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
  //  radio.printDetails();

  //Set motors I/O
  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
  pinMode(m21, OUTPUT);
  pinMode(m22, OUTPUT);

  //Set motors off when the device plug for the 1st time.
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
  analogWrite(LeftMotorSpeed, pwmOutput);
  analogWrite(RightMotorSpeed, pwmOutput);
}
void turnright(int pwmOutput)
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
void turnleft(int pwmOutput)
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

void drive(data receivedData) {
  if (receivedData.xAxis < -5 && receivedData.xAxis != -90 && receivedData.yAxis != 90)
  {
    forward(speed_control(receivedData.xAxis, -5, -40));
  }
  else if (receivedData.xAxis > 10 && receivedData.xAxis != -90 && receivedData.yAxis != 90)
  {
    backward(speed_control(receivedData.xAxis, 5, 40));
  }
  else if (receivedData.yAxis < -5 && receivedData.xAxis != -90 && receivedData.yAxis != 90)
  {
    turnleft(speed_control(receivedData.yAxis, -5, -40));
  }
  else if (receivedData.yAxis > 5 && receivedData.xAxis != -90 && receivedData.yAxis != 90)
  {
    turnright(speed_control(receivedData.yAxis, 5, 40));
  }
  else if (receivedData.xAxis == -90 && receivedData.yAxis == 90)
  {
    Stop();
  }
  else {
    Stop();
  }
}

void loop() {
  while (radio.available()) {
    uint8_t len = radio.getDynamicPayloadSize();
    //Read the received RF data.
    radio.read(&receive_data, len);
    //print the debug data
    //    Serial.print("accAngleX :     ");
    //    Serial.println(receive_data.xAxis);
    //    Serial.print("\taccAngleY :    ");
    //    Serial.println(receive_data.yAxis);
    //To drive the CAR
    drive(receive_data);
  }
}

//Control the speed according to the angle
int speed_control(int currentAngleValue, int min_angle, int max_angle )
{
  int pwmValue = map(currentAngleValue, min_angle, max_angle, 50, 255);
  if (pwmValue <= 255) {
    return pwmValue;
  } else {
    return 255;
  }
}
