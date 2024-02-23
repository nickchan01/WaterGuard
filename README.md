# WaterGuard IoT

WaterGuard IoT is a comprehensive flood monitoring system prototype designed to provide real-time information and alerts about the water levels in rivers and other water bodies. The system is equipped with sensors that can detect the changes in water levels and send alerts to the users through their smartphones or other connected devices. WaterGuard IoT is a reliable and accurate system that can help people stay informed about potential flooding risks in their area and take necessary precautions to protect themselves and their property. It is also able to detect dangerous water rise and predict upcoming floods by studying water level patterns with the help of machine learning and Google Technologies.

## Table Of Contents

- [Prototype Overview](#prototype-overview)
- [Getting Started](#getting-started)
- [Features](#features)
- [Technologies](#technologies)
- [Contributors](#contributors)

## Prototype Overview 
WaterGuard IoT is a our physical flood monitoring and alerting model that works in tandem with our WaterGuard application to provide real-time alerts to local communities when floods or dangerous water level rise is detected. WaterGuard IoT also streams data to our Firebase Realtime Database, which uses Google Cloud Platform to predict potential floods using machine learning and update our application accordingly. Built with the NodeMCU ESP32 which can be expanded to the ESP32 SIM800L, WaterGuard IoT is able to connect to the Internet for streaming data either by using Wi-Fi or even celular connection. The model also utilzes Arduino compatible components such as the ultrosonic sensor to detect water levels, alerting buzer and a TP4056 Battery Charger and Solar Panel to ensure our model is continuosly powered. For the housing of our IoT model, we used weatherproof, waterproof and Ingress Protection standard materials which aligns with our use case of being exposed to extreme weather such as high tempreatures, rain and placed in an actively flowing water source. Some materials used for our housing are such as an IP67 Junction Box which houses all of our electronic components including the microcontroller and an PVC Class D pipe which houses the ultronic sensor and acts as a stand in the flowing water source.

Components :
1. 1 - NodeMCU ESP32 / ESP32 SIM800L
2. 1 - SR04P Ultrasonic Ranging Module
3. 1 - I2C 1602 Serial LCD
4. 1 - 16.5x5.5 Breadboard
5. 14 - 10cm Jumper Cables

![flood managment system (1)](https://github.com/nickchan01/WaterGuard/assets/148427518/fc02017b-2fd4-41f7-8260-3e733661ccca)


## Getting Started
#This will only work with similarly built projects!

1. Create the project using components listed
2. Download the source code folder and unzip 
3. Open the source code folder on your preferred IDE (Arduino IDE Recommended)
4. Insert Firebase API key and URL
5. Insert Wi-Fi SSID and password
6. Upload the code to the NodeMCU ESP32 and run 

## Features
- Water Level Monitoring
- Dangerous Water Rise Alerting
- Flood Alerting
- Flood Prediction

## Technologies

Libraries, Packages and Dependencies:
- [EEPROM Library](https://docs.arduino.cc/learn/built-in-libraries/eeprom/)
- [Wire Library](https://www.arduino.cc/reference/en/language/functions/communication/wire/)
- [LiquidCrystal I2C Library](https://www.arduino.cc/reference/en/libraries/liquidcrystal-i2c/)
- [Software Serial Library](https://docs.arduino.cc/learn/built-in-libraries/software-serial/)
- [WiFi Library](https://www.arduino.cc/reference/en/libraries/wifi/)
- [Firebase Arduino Client Library for ESP8266 and ESP32 Library](https://www.arduino.cc/reference/en/libraries/firebase-arduino-client-library-for-esp8266-and-esp32/)


## Contributors 

- [Nicholas Chan Wei Xian](https://github.com/nickchan01)
- [Ivy Chung Ai Shin](https://github.com/ICAS03)
- [Zhe Khee Tang](https://github.com/jackyt0303)

