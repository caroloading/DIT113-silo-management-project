# <img src="docs/images/faviconG-32x32.png" width="auto" height="auto"/> Grain Guard

## Description
The developed system is meant to help monitor and manage the conditions and levels of grain inside a silo. Relevant information such as humidity, temperature and grain level will be measured and sent back to the application, where data will be processed, stored and later displayed on the website for easy access. The main goal of the system will be to monitor if the environment inside a silo is suitable for grain and check if the grain level is not above the collection threshold. If any of the conditions are not met, the correct person/people are notified.

## Visuals

## Installation

### Required software
* [Arduino IDE](https://www.arduino.cc/en/software)
* [Java JDK 21](https://www.oracle.com/java/technologies/downloads/#java21)
* [Maven](https://maven.apache.org/install.html)

### Required hardware and sensors
* Microcontroller: [Wio Seeed Terminal](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
* Battery Chassis: [Wio Terminal Battery Chassis](https://wiki.seeedstudio.com/Wio-Terminal-Battery-Chassis/)
* 3x Cables : [Grove - Cable](https://www.seeedstudio.com/Grove-Universal-4-Pin-20cm-Unbuckled-Cable-5-PCs-Pack-p-749.html)
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

To avoid having potential problems with library dependencies, it is advised to install all libraries directly from the GitHub links provided above.

## Setup
* Before downloading the git repository, ensure that all required software and libraries are installed.
* Connect the Battery Chassis to the Wio Terminal by inserting all the pins on the battery into the back of the terminal.
* If the battery is charged, the terminal should work without having to be connected to the power source with a cable. <br/>
If the battery is not charged, plugged the battery into a computer using the central USB-C port on the battery.
* Connect each sensor to a cable and insert them in the following sockets: 
<div>
    <img style="margin-left: 50px" src="docs/images/WioConnections.png" width="400px" height="auto"/>
    <img style="margin-left: 50px" src="docs/images/BatteryConnections.png" width="400px" height="auto"/>
</div>

* Download the GrainGuard repository from GitLab.
* Extract the `.zip` file to a directory of choice.
* Create a `secrets.h` file in the wio directory according to the `secrets.example.h` file, and replace the example text with the correct SSID and password for your Wi-Fi network.
* In the Arduino IDE, open the file called `wio.ino` which is located in the `silo-management-project/wio/` directory:

<div>
    <img style="margin-left: 50px" src="docs/images/OpenFile.png" width="auto" height="auto"/>
    <img style="margin-left: 50px" src="docs/images/OpenWio.png" width="auto" height="auto"/>
</div>

* After opening the `wio.ino` file, ensure that the terminal is connected via the USB-C port to the computer where the Arduino IDE is opened.
* Now, with the terminal ON, upload the code to the terminal through the Arduino IDE by pressing the arrow button as highlighted below. <br/>
(Note that the following step will not work if the computer is connected to the battery or not at all.)
<div>
    <img style="margin-left: 50px" src="docs/images/UploadWio.png" width=500px height=200px/>
</div>

* On your computer, open the terminal and navigate to the following directory `/silo-management-project/silo-webapp/`
* Run the command: ```mvn clean install```
* If the build fails, it might be the case that you have multiple versions of Java installed. Run the following command in the command prompt to see the currently installed Java version ```java -version``` <br/>
If the output version is not JDK 21, you may need to change your system path. You can read more about it [here.](https://www.java.com/en/download/help/path.html) Update the path and repeat this step.
* Now,  run the command: `mvn compile` and after, `mvn exec:java -Dexec.mainClass=group1.silowebapp.SiloWebAppApplication`
* Lastly, open your web browser and navigate to `http://localhost:8080/`

* If you wish to stop the program, you can either terminate the processes by pressing `CTRL + C` in the terminal or simply closing the command prompt.


## Contributors:
* Charles Jarju - created a foundation for the Spring Boot Web application by adding appropriate models, controllers, and views that kicked off the development process; added a business logic to the Wio terminal for capturing reading timestamps; created a CI Pipeline for the web application using Maven for the build process (Spring Boot build); created a professionally-looking style for the Wio Terminal display
* Viktor Kolak - created MQTT logic on the Wio terminal level; added Wi-Fi connectivity to the Wio terminal; Set up a third-party database running PostgreSQL engine; worked on the web application charts; positively contributed to the web application styling; created a wonderful logo for the "company"/website
* Samuel Partain - added business logic for the temperature and humidity sensor; worked on the web application charts; added dynamic updates to the web application charts based on the incoming data 
* Szymon Witt - made significant contributions to the refactor front (both on the sensor level and on the web application level); worked on the web application styling; added web sockets to the web application; created a silo details page with an integrated map view
* Caroline Grand-Clement - worked on the MQTT client on the web application side; added business logic for Wio terminal buttons; worked on the web application web socket connection; added dynamic pop-ups and banners to the web application; was the strongest PM of the group, coordinating responsibilities, keeping project progress information updated, and keeping team meetings on the highest level


## Acknowledgements
* Thank you to our TAs Teo Portase and Adrian Hassa.

## License
The project is licensed under the MIT License. Refer to [license](https://git.chalmers.se/courses/dit113/2024/group-1/silo-management-project/-/blob/main/LICENSE?ref_type=heads) for more information.

## Project status
Completed.
