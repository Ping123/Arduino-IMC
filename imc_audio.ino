#include <avr/power.h>            // include Arduino avr library
#include <SPI.h>                  // include Arduino SPI library
#include <SD.h>                   // include Arduino SD library
#include "TMRpcm.h"               // include TMRpcm library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Wire.h>                 // Communication between Arduinos

// define Pins & max. LED's --------------------------------------------------------------------------------------------
#define SPEAKER           46         // Speaker Pin
#define SDPIN             53         // SD-Card-Slot Pin
volatile bool data_flag   = false;


// initial Setup -------------------------------------------------------------------------------------------------------
TMRpcm audio;
File root;

void setup() {
  
  Wire.begin(8);                  // join i2c bus with address #8
  Wire.onReceive(receiveEvent);   // register event

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
  Serial.println("init done");
}

// function that executes whenever data is received from master --------------------------------------------------------
void receiveEvent(int bytes) {
  data_flag = true;
}

/*
void receiveEvent(int howMany) {
  while(1 < Wire.available()) {
    char c = Wire.read();         // receive byte as a character
    Serial.print(c);              // print the character
  }
  int x = Wire.read();            // receive byte as an integer
  Serial.println(x);              // print the integer
}
*/

// MAIN LOOP FUNCTION --------------------------------------------------------------------------------------------------
void loop() {

  if (data_flag == true) {
    int go = Wire.read();
    Serial.println(go);
    
    if (go == 1) {
        audio.play("imc_2.wav");
        data_flag = false;
      } else {
        data_flag = false;
    }
  }

  delay(500);

  /*
  Serial.println("loop start");
  audio.play("imc_2.wav");
  delay(119000);
  Serial.println("loop end");
  */
}
