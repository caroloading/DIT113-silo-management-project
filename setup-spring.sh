#!/bin/bash

# Set environment variables
export PATH=$PATH:/root/bin

# Update the package index files on the system
apt update

# Change to current user's home directory 
cd ~

# Install JDK 21
apt install openjdk-21-jdk -y 
java --version 

# Install Maven 
apt install maven -y
mvn --version 