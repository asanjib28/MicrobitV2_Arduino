/*
  The sketch detects loud sounds such as the sound of clap and displays a level on
  the built-in LED matrix display.
  This sketch is tested with a Micro:bit V2.21 board, and will only work with V2 boards

  Author: Sanjib Acharya
  Date: 01-FEB-2024
  Version: 1.0

*/
#include <Adafruit_Microbit.h>
#include "sound_levels.h"

Adafruit_Microbit_Matrix microbit;


int unsigned sensorValue = 0;       // variable to store the value coming from the sensor
int unsigned maxSensorValue = 0;    // variable that stores the maximum sensor value recored
int signed quietPeriodCounter = 0;  // Counts the number of sensor data captured 
int unsigned soundDetected = 0;     // Flag which goes HIGH is sound is detected
const int RUN_MIC = 28;             // RUN_MIC pin; shall be driven HIGH to enable the microphone
const int MIC_IN = A6;              // Analog input A6 pin; microphone signal is connected to it
const int displayDelay = 0;         // A variable to add a delay between each dislay, set to zero for now


// Function to display sound level
void displaySoundLevel(int sensVal) {

  switch (sensVal) {
    case 0 ... 26:
      microbit.clear();
      break;
    case 27 ... 35:
      microbit.show(sound_level1);
      delay(displayDelay);
      break;
    case 36 ... 60:
      microbit.show(sound_level2);
      delay(displayDelay);
      break;
    case 61 ... 85:
      microbit.show(sound_level3);
      delay(displayDelay);
      break;
    case 86 ... 110:
      microbit.show(sound_level4);
      delay(displayDelay);
      break;
    case 111 ... 135:
      microbit.show(sound_level5);
      delay(displayDelay);
      break;      
    case 136 ... 160:
      microbit.show(sound_level6);
      delay(displayDelay);
      break;
    case 161 ... 185:
      microbit.show(sound_level7);
      delay(displayDelay);
      break;
    case 186 ... 200:
      microbit.show(sound_level8);
      delay(displayDelay);
      break;
    case 201 ... 220:
      microbit.show(sound_level9);
      delay(displayDelay);
      break;
    case 221 ... 255:
      microbit.show(sound_level10);
      delay(displayDelay);
      break;
    default:
      microbit.clear();
      break;
         
  }
}

void setup() {
  // declare the RUN_MIC as an OUTPUT:
  pinMode(RUN_MIC, OUTPUT);
  // Enable the microphone by driving RUN_MIC signal high
  digitalWrite(RUN_MIC, HIGH);
  // Initialize the serial port
  Serial.begin(115200);
  // Initiate the display instance created above for the LED Matrix
  microbit.begin();
  
}

void loop() {
  
  sensorValue = analogRead(MIC_IN);

  if (sensorValue >= 27) {
    soundDetected = 1;
    if (sensorValue > maxSensorValue) {
      maxSensorValue = sensorValue;
      // Print the Microphone input signal on the serial port
      Serial.println(maxSensorValue);
      //Serial.print("\t");
      //Serial.println(sensorDataCounter);
      displaySoundLevel(maxSensorValue);
    }
  }
  else {
    if (soundDetected == 1) {
      quietPeriodCounter = 1000;
      soundDetected = 0;
      // Print the Microphone input signal on the serial port
      //Serial.println(maxSensorValue);
      //displaySoundLevel(maxSensorValue);
    }
    else {
      if (quietPeriodCounter > 0){
        quietPeriodCounter--;
      }
      else{
        maxSensorValue = 0;
      } 
    } 
  }
}
