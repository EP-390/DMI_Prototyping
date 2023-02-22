#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=103,234
AudioOutputI2S           i2s1;           //xy=329,231
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=327,314
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Bounce button1 = Bounce(14, 15);

void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(14, INPUT_PULLUP);
}

void loop() {
  button1.update();
  if(button1.fallingEdge() && !playSdWav1.isPlaying()){
    playSdWav1.play("SDTEST1.WAV");
  }

  if(button1.risingEdge() && playSdWav1.isPlaying()){
    playSdWav1.stop();
  }

  // Use the pot to control the overall volume
  int knob = analogRead(A1);
  float vol = (float) knob / 1280.0;
  sgtl5000_1.volume(vol);
}
