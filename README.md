# Hand_Gesture_Robot
Hand Gesture Robot

1.  Definition of hand Gesture: -
Instead of using a remote control with buttons or a joystick, the motion of the hand is used to control the robot.
The project is based on wireless communication, where the data from the hand gestures is transmitted to the robot over the RF link (RF Transmitter – Receiver pair).
2. How the robot will work: - 
(i). The first part of the project is the calibration of the MPU 6050 sensor then the wireless communication establishment between the RF Transmitter and Receiver.
(ii). The second part is getting data from the MPU6050 Accelerometer Sensor by the Arduino Nano (Microcontroller). The Arduino continuously reads data from the MPU6050 and based on the predefined datatype, then it sends the data through the RF Transmitter module to the RF Receiver module.
(iii). Finally, the third part of the project is decoding the Data received by the RF Receiver and sending appropriate signals to the Motor Driver IC after the data processing by the Arduino, which will drive the Motors of the Robot.
_______________________________________________
-Components used for Transmitter Section
1.	Arduino Nano
2.	MPU6050 (Accelerometer/Gyroscope Sensor) 
3.	RF Module
--------------------------------------
-Components used for Receiver Section
1. L293D Motor
2. Arduino Nano
3. RF Module
4. Four Geared Motors with wheels
5. Robot Chassis
_______________________________________
3. Working of Hand Gesture Controlled Robot: -
In this project, a robot is controlled by the gestures made by the hand. 
As mentioned earlier, the gesture-controlled robot is a wireless-operated robot and has two parts: Transmitter and Receiver. When the robot is powered on, the transmitter part, which consists of Arduino, MPU6050, and RF Transmitter, will continuously monitor the MPU6050 sensor. This data is captured by the Arduino, which then transmits corresponding data, based on the orientation of the MPU6050 Sensor. Then the microcontroller transmits the sensor orientation data by the RF Transmitter.
At the receiver section, the RF Receiver receives the data and sends them to the Arduino for processing. Based on the data, the microcontroller drives the motor by sending the signal to the motor driver module.
