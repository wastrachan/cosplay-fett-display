// Cosplay Fett Display (https://github.com/wastrachan/cosplay-fett-display/)
//
// Copyright (c) 2021 Winston Astrachan
// Available under the terms of the MIT license

#include <stdbool.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "14SegmentFont.h"

#define TFT_CS      9
#define TFT_RST     -1
#define TFT_DC      6
#define TFT_WIDTH   320
#define TFT_HEIGHT  240
#define BLACK       0x0000
#define RED         0xF800

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

static unsigned int  fsmTextIndex;
static unsigned long fsmNextChange;


void setup() {
  tft.init(TFT_HEIGHT, TFT_WIDTH);  // Set up TFT with correct dimensions
  tft.fillScreen(BLACK);            // Black background
  tft.setRotation(3);               // Screen is oriented horizontally
  fsmTextIndex  = 1;                // Init FSM for text rotation
  fsmNextChange = 0;                // Init FSM for text rotation
}


void loop() {
  rotateText();
  sweepDisplay();
}


void rotateText() {
  int nextChange = random(2000,8000);
  const int numStrings = 8;
  const char *strings[numStrings];

  strings[0] = "8  8  8  8  8";
  strings[1] = "6  6  2  3  4";
  strings[2] = "H  G  2  8  C";
  strings[3] = "~  ~  ~  ~  ~";
  strings[4] = "H  G  2  0  5";
  strings[5] = "d  U  E  P  '";
  strings[6] = "H  5  2  9  1";
  strings[7] = " d  *  c o n";

  long now = millis();
  if(now > fsmNextChange) {
    if(fsmTextIndex == numStrings-1){
      fsmTextIndex = 0;
    } else {
      fsmTextIndex++;
    }
    writeText(strings[fsmTextIndex]);
    fsmNextChange = now + nextChange;
  }
}


void writeText(char *text) {
  tft.setFont(&Font14Segment_Regular12pt);
  tft.setCursor(20, 160);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.fillRect(0, 100, TFT_WIDTH, 120, BLACK);  // Erase existing Text
  tft.print(text);
}


void sweepDisplay() {
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
