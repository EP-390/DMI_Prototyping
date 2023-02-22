#include <Audio.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=217,198
AudioEffectEnvelope      envelope1;      //xy=381,196
AudioMixer4              mixer1;         //xy=581,207
AudioEffectDelay         delay1;         //xy=588,381
AudioOutputI2S           i2s1;           //xy=795,341
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, delay1);
AudioConnection          patchCord4(delay1, 0, mixer1, 3);
AudioConnection          patchCord5(delay1, 0, i2s1, 0);
AudioConnection          patchCord6(delay1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=778,424
// GUItool: end automatically generated code

Bounce button1 = Bounce(14, 15);

void setup() {
  pinMode(14, INPUT_PULLUP);
  
  // allocate enough memory for the delay
  AudioMemory(120);

  // enable the audio shield
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  waveform1.begin(0.9, 440, WAVEFORM_SINE);
  delay1.delay(0, 110);
  mixer1.gain(0, 1);
  mixer1.gain(3, 0.7); 
}

void loop() {
  button1.update();
  if (button1.fallingEdge()) {
    envelope1.noteOn();
  }
  if (button1.risingEdge()) {
    envelope1.noteOff();
  }

  // Use the pot to control the overall volume
  int knob = analogRead(A1);
  float vol = (float) knob / 1050.0;
  mixer1.gain(3, vol);
}
