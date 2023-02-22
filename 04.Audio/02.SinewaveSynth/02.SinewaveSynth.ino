#include <Audio.h>
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=543,352
AudioEffectEnvelope      envelope1;      //xy=726,349
AudioOutputI2S           i2s1;           //xy=967,351
AudioConnection          patchCord1(waveform1, envelope1);
AudioConnection          patchCord2(envelope1, 0, i2s1, 0);
AudioConnection          patchCord3(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=964,445
// GUItool: end automatically generated code

Bounce button1 = Bounce(14, 15);

void setup() {
  pinMode(14, INPUT_PULLUP);
  
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  waveform1.frequency(440);
  waveform1.amplitude(0.9);
  waveform1.begin(WAVEFORM_SINE);
  envelope1.attack(50);
  envelope1.decay(50);
  envelope1.release(250);
}

void loop() {
  button1.update();
  if (button1.fallingEdge()) {
    waveform1.frequency(map(analogRead(A1), 0, 1024, 440, 1760));
    envelope1.noteOn();
  }
  if (button1.risingEdge()) {
    envelope1.noteOff();
  }
}
