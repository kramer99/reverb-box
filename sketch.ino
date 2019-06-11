#include <ADC.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

ADC *adc = new ADC();   // ...this has to be before Audio Library stuff

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=151,148
AudioEffectFreeverb      freeverb1;      //xy=314,266
AudioMixer4              mixer1;         //xy=479,165
AudioOutputAnalogStereo  dacs1;          //xy=658,172
AudioConnection          patchCord1(adc1, freeverb1);
AudioConnection          patchCord2(adc1, 0, mixer1, 0);
AudioConnection          patchCord3(freeverb1, 0, mixer1, 1);
AudioConnection          patchCord4(mixer1, 0, dacs1, 0);
// GUItool: end automatically generated code

void setup() {
    AudioMemory(20);

    // NOTE: commented out /Users/craig/Arduino.app/Contents/Java/hardware/teensy/avr/libraries/Audio/input_adc.cpp:51
    adc->setReference(ADC_REFERENCE::REF_1V2, ADC_0);
    adc->setReference(ADC_REFERENCE::REF_3V3, ADC_1);
      
    // Audio library has overriden this, so need to reset the reference voltages...
    //adc->setReference(ADC_REFERENCE::REF_1V2, ADC_1); // NOTE: ADC CODE CHECKS FOR SETTING SAME VALUE, SO SET IT TO SOMETHING ELSE FIRST
    //adc->setReference(ADC_REFERENCE::REF_3V3, ADC_1);
  
    freeverb1.roomsize(0.8);
    freeverb1.damping(.5);
    mixer1.gain(0, .5);
    mixer1.gain(1, .5);
}

void loop() {
    int a16 = adc->analogRead(A16, ADC_1);
    int a17 = adc->analogRead(A17, ADC_1);
    int a18 = adc->analogRead(A18, ADC_1);
    int a18 = adc->analogRead(A18, ADC_1);
    float room = (float)a16 / 65535;
    float damp = (float)a17 / 65535;
    float mix = (float)a18 / 65535;
    freeverb1.roomsize(room);
    freeverb1.damping(damp);
    mixer1.gain(0, mix);
    mixer1.gain(1, 1 - mix);
    
    Serial.printf("%d\t%d\t%d\n", a16, a17, a18);
    adc->printError();

    delay(200);
}
