# Silo Management Project

## Name
Grain Guard.

## Description
The developed system is meant to help monitor and manage the conditions and levels of grain inside a silo. Relevant information such as humidity, temperature and grain level will be measured and sent back to the application, where data will be processed, stored and later displayed on the website for easy access. The main goal of the system will be to monitor if the environment inside a silo is suitable for grain and check if the grain level is not above the collection threshold. If any of the conditions are not met, the correct person/people is notified.

## Visuals

## Installation

### Required software
* [Arduino](https://www.arduino.cc/en/software)

### Required hardware and sensors
* Microcontroller: [Wio Seeed Terminal](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
* [Grove - Ultrasonic Ranger](https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/)
* [Grove - LED Bar](https://wiki.seeedstudio.com/Grove-LED_Bar/) 
* [Grove - Temperature&Humidity Sensor (DHT11)](https://wiki.seeedstudio.com/Grove-TemperatureAndHumidity_Sensor/)

### Required Arduino libraries
* [Grove Temperature and Humidity Sensor](https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor)
* [Grove LED Bar](https://github.com/Seeed-Studio/Grove_LED_Bar/tree/master)
* [Grove Ultrasonic Ranger](https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger)
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [Seeed Arduino RTC](https://github.com/Seeed-Studio/Seeed_Arduino_RTC/tree/master)
* [Seeed Arduino rpcWiFi](https://github.com/Seeed-Studio/Seeed_Arduino_rpcWiFi)
* [Seeed Arduino rpcUnified](https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified)
* [Seeed Arduino FS](https://github.com/Seeed-Studio/Seeed_Arduino_FS)
* [Seeed Arduino mbedtls](https://github.com/Seeed-Studio/Seeed_Arduino_mbedtls)
* [PubSubClient](https://github.com/knolleary/pubsubclient/tree/master)
* [NTPClient](https://github.com/arduino-libraries/NTPClient)

To avoid having potential problems with library dependencies. It is advised to install all libraries directly from GitHub links provided above.

## Usage
* Download the repository.
* Create a secrets.h file in the /wio folder, according secrets.example.h file, replacing with the correct SSID and password for your wifi network.
* Upload the Arduino sketch to your Wio Terminal.
* Run the web application. 
* Open your web browser to http://localhost:8080/.

## Contributors:
* Charles Jarju
* Viktor Kolak 
* Samuel Partain
* Szymon Witt
* Caroline Grand-Clement

## Acknowledgements
* Thank you to our TAs Teo Portase and Adrian Hassa.

## License
The project is licensed under the MIT License. Refer to [license](https://git.chalmers.se/courses/dit113/2024/group-1/silo-management-project/-/blob/main/LICENSE?ref_type=heads) for more information.

## Project status
Completed.
