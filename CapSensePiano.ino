#include <CapacitiveSensor.h>

/*
  Capacitive-Touch Arduino Keyboard Piano
  
  Plays piano tones through a buzzer when the user taps touch-sensitive piano "keys"
  
  Created  18 May 2013
  Modified 23 May 2013
  by Tyler Crumpton and Nicholas Jones
  
  This code is released to the public domain. For information about the circuit,
  visit the Instructable tutorial at http://www.instructables.com/id/Capacitive-Touch-Arduino-Keyboard-Piano/
*/

#include <CapacitiveSensor.h>
#include "pitches.h"

#define COMMON_PIN      2    // The common 'send' pin for all keys
#define BUZZER_PIN      A4   // The output pin for the piezo buzzer
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   50  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     12    // Number of keys that are on the keyboard

// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:
#define CS(Y) CapacitiveSensor(2, Y)

// Each key corresponds to a note, which are defined here. Uncomment the scale that you want to use:
int notes[]={NOTE_C4,NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4}; // C-Major scale
//int notes[]={NOTE_A4,NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5}; // A-Minor scale
//int notes[]={NOTE_C4,NOTE_DS4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_AS4,NOTE_C5,NOTE_DS5}; // C Blues scale
const int motorpin = 24;
// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3), CS(4), CS(5), CS(6), CS(7), CS(8), CS(9), CS(10), CS(11), CS(12), CS(13), CS(22)};

void setup() { 
  // Turn off autocalibrate on all channels:
  for(int i=1; i<12; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }
  // Set the buzzer as an output:
  pinMode(BUZZER_PIN, OUTPUT); 
  // set motor as output:
  pinMode(motorpin, OUTPUT);
}

void loop() {    
  // Loop through each key:
unsigned int keysPlaying = 0;
// Loop through each key:
  for (int i = 0; i < NUM_OF_KEYS; ++i) {
// If the capacitance reading is greater than the threshold, play a note and turn on motor:
  int c = keys[i].capacitiveSensor(NUM_OF_SAMPLES);
  if(c > CAP_THRESHOLD) {
  tone(BUZZER_PIN, notes[i]); // Plays the note corresponding to the key pressed
    keysPlaying++;
   digitalWrite(motorpin, HIGH);
}
}
// If the capacitance reading is less than the threshold, do not play sound and turn off motor:
if (keysPlaying == 0) {
noTone(BUZZER_PIN);
digitalWrite(motorpin, LOW);
}
}
