#!/bin/bash

# Set environment variables
export PATH=$PATH:/root/bin
export GREEN='\033[0;32m'
export NOCOLOR='\033[0m'

# Update the package index files on the system
apt-get update

# Change to current user's home directory 
cd ~

# Install JDK 21
apt-get install openjdk-21-jdk -y 
echo -e "{GREEN}Java Version: "
java --version 

# Install Maven 
apt-get install maven -y
echo -e "{GREEN}Maven Version: "
mvn --version 