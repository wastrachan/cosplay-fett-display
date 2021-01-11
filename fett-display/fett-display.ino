// Cosplay Fett Display (https://github.com/wastrachan/cosplay-fett-display/)
//
// Copyright (c) 2021 Winston Astrachan
// Available under the terms of the MIT license

#include <stdbool.h>
#include <math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "14SegmentFont.h"

#define TFT_CS          9
#define TFT_RST         -1
#define TFT_DC          6
#define TFT_BL          10
#define TFT_WIDTH       320
#define TFT_HEIGHT      240
#define TFT_BRIGHT_PCT  100
#define BLACK           0x0000
#define RED             0xF800

static unsigned int  fsmTextIndex;
static unsigned long fsmNextChange;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define NUMSTRINGS 8
static char *STRINGS[NUMSTRINGS] = {
  "H  5  2  9  1",
  "~  ~  ~  ~  ~",
  " d  *  c o n ",
  "6  6  2  3  4",
  "H  G  2  8  C",
  "~  ~  ~  ~  ~",
  "H  G  2  0  5",
  "d  U  E  P  '",
};


void setup() {
  analogWrite(TFT_BL, (int)round(255 * (TFT_BRIGHT_PCT / (float)100)));   // Brightness as PWM value
  tft.init(TFT_HEIGHT, TFT_WIDTH);                                        // Set up TFT with correct dimensions
  tft.fillScreen(BLACK);                                                  // Black background
  tft.setRotation(3);                                                     // Screen is oriented horizontally
  fsmTextIndex  = 0;                                                      // Init FSM for text rotation
  fsmNextChange = 0;                                                      // Init FSM for text rotation
}


void loop() {
  rotateText();
  sweepDisplay();
}


void rotateText() {
  /**
   * Rotate through display of several predefined strings
   * Change strings randomly between 2 and 8 seconds
   *
   * Uses a rudimentary FSM to determine if enough time has pased
   * to warrant a rotation of the string.
   *
   * Strings defined as STRINGS, an array of size NUMSTRINGS
   */
  int nextChange = random(2000,8000);
  long now = millis();
  if(now > fsmNextChange) {
    if(fsmTextIndex == NUMSTRINGS-1){
      fsmTextIndex = 0;
    } else {
      fsmTextIndex++;
    }
    writeText(STRINGS[fsmTextIndex]);
    fsmNextChange = now + nextChange;
  }
}


void writeText(char *text) {
  /**
   * Write an arbitrary string to an emulated 14 segment display
   *
   * @param text String to display (7 chars max)
   */
  tft.setFont(&Font14Segment_Regular12pt);
  tft.setCursor(19, 160);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.fillRect(0, 100, TFT_WIDTH, 120, BLACK);  // Erase existing Text
  tft.print(text);
}


void sweepDisplay() {
  /**
   * Illuminate an emulated 9 bar LED bargraph in a sweep
   * from left to right to left
   */
  const int numBars = 9;
  const int groupSize = 3;
  const int delayMS = 70;

  // Sweep Left
  for(int i=0; i<numBars+groupSize; i++){
    drawBar(i, true);
    drawBar(i-groupSize, false);
    delay(delayMS);
  }

  // Sweep Right
  for(int i=numBars+groupSize; i>0; i--){
    drawBar(i-groupSize, true);
    drawBar(i, false);
    if(i>1){
      delay(delayMS);
    }
  }
}


void drawBar(int pos, bool state){
  /**
   * Draw a single "bar" of an emulated 9 bar LED bargraph
   * Turn bar on or off by position (0-8) and state (bool)
   *
   * @param pos Position of "LED" (0-8)
   * @param state On/Off state of "LED" (true/false)
   */
  const int barWidth = 30;
  const int barHeight = 80;
  const int padding = 2;
  int x = pos * (barWidth + padding);

  if(state == true) {
    tft.fillRect(x, 0, barWidth, barHeight, RED);
  } else {
    tft.fillRect(x, 0, barWidth, barHeight, BLACK);
  }
}
