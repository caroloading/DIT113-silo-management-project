#!/bin/bash

# Set environment variables
export PATH=$PATH:/root/bin
export GREEN='\033[0;32m'
export NOCOLOR='\033[0m'

# Update the package index files on the system
apt-get update

# Install JDK 21
apt-get install openjdk-21-jdk -y 
printf "${GREEN}Java Version:${NOCOLOR} \n"
java --version 

# Install Maven 
apt-get install maven -y
printf "${GREEN}Maven Version:${NOCOLOR} \n"
mvn --version 
 