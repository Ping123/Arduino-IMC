#include <Adafruit_NeoPixel.h>    // include Adafruit NeoPixel library
#include <avr/power.h>            // include Arduino avr library
#include <SPI.h>                  // include Arduino SPI library
#include <SD.h>                   // include Arduino SD library
#include "TMRpcm.h"               // include TMRpcm library

#define LEDPIN         6          // PIN where LED-Band is
#define NUMPIXELS      15         // How many Pixels are on?
#define SPEAKERPIN     9
#define SDPIN          10

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;

TMRpcm audio;

void setup() {
  pixels.begin();
  audio.speakerPin=SPEAKERPIN;
  PlaySound();
}

void TurnLedON() {
  for(int i=0;i<5;i++){
    pixels.setPixelColor(i, pixels.Color(255,255,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int i=5;i<10;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int i=10;i<15;i++){
    pixels.setPixelColor(i, pixels.Color(0,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void TurnLedOFF() {
  for(int i=0;i<5;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int i=5;i<10;i++){
    pixels.setPixelColor(i, pixels.Color(0,255,255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for(int i=10;i<15;i++){
    pixels.setPixelColor(i, pixels.Color(255,255,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
  }
}

void PlaySound() {
  Serial.begin(9600);
  
  if(!SD.begin(SDPIN)) {
    Serial.println("SD fail");
    return;
  }
  
  audio.setVolume(6);
  audio.play("test.wav");
}

void loop() {
  TurnLedON();
  delay(delayval);
  TurnLedOFF();
  delay(delayval);
}
