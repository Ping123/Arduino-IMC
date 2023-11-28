#include <avr/power.h>            // include Arduino avr library
#include <SPI.h>                  // include Arduino SPI library
#include <SD.h>                   // include Arduino SD library
#include "TMRpcm.h"               // include TMRpcm library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define Pins & max. LED's --------------------------------------------------------------------------------------------
#define SPEAKER        46         // Speaker Pin
#define SDPIN          53         // SD-Card-Slot Pin

// initial Setup -------------------------------------------------------------------------------------------------------

TMRpcm audio;
File root;

void setup() {
  
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  if (!SD.begin(SDPIN)) {
    Serial.println("failed!");
    while(true);  // stay here.
  }
  Serial.println("OK!");

  audio.speakerPin = SPEAKER;
  audio.setVolume(3);
  audio.quality(0);

  delay(1000);
  Serial.println("init done");
}

// MAIN LOOP FUNCTION --------------------------------------------------------------------------------------------------
void loop() {
  Serial.println("loop start");
  audio.play("imc_2.wav");
  delay(119000);
  Serial.println("loop end");
}
