#include <iostream>
#include "Ranger.h"
#include "LedBar.h"
#include "ModeButton.h"
#include "TFT_eSPI.h"  

TFT_eSPI tft;
LedBar ledBar(1, 0, GREEN_FIRST);
Ranger ranger(2);
ModeButton pauseButton(BUTTON_1);

void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.setCursor(50,100);
  tft.setTextColor(TFT_BLACK);          //sets the text colour to black
  tft.setTextSize(2);
  tft.fillScreen(TFT_RED);

  Serial.begin(115200);
}

void loop() {
  if (!pauseButton.IsEnabled()){
    long distance = ranger.MeasureRange();
    ledBar.UpdateDisplay(14);
    Serial.println(distance);
  } else {
    Serial.println("Paused for maintenance.");
  }
  
  pauseButton.ChangeIfPressed();

  delay(1000);
}
