#!/bin/bash

apt-get update
cd ~

# Install arduino-cli
apt-get install curl -y
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
export PATH=$PATH:/root/bin
arduino-cli version

# Install Seeed Wio Terminal core
printf "board_manager:\n  additional_urls:\n    - https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json\n" > .arduino-cli.yaml
arduino-cli core update-index --config-file .arduino-cli.yaml
arduino-cli core install Seeeduino:samd --config-file .arduino-cli.yaml

# Install 'native' packages (libraries that do not come with the core)
arduino-cli lib install "Seeed Arduino rpcWiFi@1.0.7"
arduino-cli lib install "PubSubClient@2.8"
arduino-cli lib install "NTPClient@3.2.1"
arduino-cli lib install "ArduinoJson@7.0.4"

cd ~

# Install 'third-party' packages / libraries: find proper location and 'git clone'
apt-get install git -y
cd `arduino-cli config dump | grep user | sed 's/.*\ //'`/libraries
git clone https://github.com/Seeed-Studio/Grove_LED_Bar.git
git clone https://github.com/Seeed-Studio/Grove_Temperature_And_Humidity_Sensor.git
git clone https://github.com/Seeed-Studio/Seeed_Arduino_RTC.git
#git clone https://github.com/Seeed-Studio/Seeed_Arduino_mbedtls.git
git clone https://github.com/Seeed-Studio/Seeed_Arduino_UltrasonicRanger.git
#git clone https://github.com/Seeed-Studio/Seeed_Arduino_rpcUnified.git
#git clone https://github.com/Seeed-Studio/Seeed_Arduino_FS.git