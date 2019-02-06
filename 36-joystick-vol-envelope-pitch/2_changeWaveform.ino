// waveform and audio connection mapping

int waveformNum[4] = {0, 1, 2, 3};
AudioSynthWaveform       waveform[4];
AudioEffectEnvelope      envelope[4];
AudioOutputAnalog        dacs1; 
AudioMixer4              mixer1;
AudioAmplifier           amp1;    
AudioConnection          patchCord0(waveform[0], 0, envelope[0], 0);  
AudioConnection          patchCord1(waveform[1], 0, envelope[1], 0);
AudioConnection          patchCord2(waveform[2], 0, envelope[2], 0);
AudioConnection          patchCord3(waveform[3], 0, envelope[3], 0);
AudioConnection          patchCord4(envelope[0], 0, mixer1, 0);  
AudioConnection          patchCord5(envelope[1], 0, mixer1, 1);
AudioConnection          patchCord6(envelope[2], 0, mixer1, 2);
AudioConnection          patchCord7(envelope[3], 0, mixer1, 3);
AudioConnection          patchCord8(mixer1, 0, amp1, 0);
AudioConnection          patchCord9(amp1, 0, dacs1, 0);


void changeWaveform() {
        switch (current_waveform) {
      case WAVEFORM_SINE:
        current_waveform = WAVEFORM_SAWTOOTH;
        Debugln("Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH:
        current_waveform = WAVEFORM_SAWTOOTH_REVERSE;
        Debugln("Reverse Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH_REVERSE:
        current_waveform = WAVEFORM_SQUARE;
        Debugln("Square");
        break;
      case WAVEFORM_SQUARE:
        current_waveform = WAVEFORM_TRIANGLE;
        Debugln("Triangle");
        break;
      case WAVEFORM_TRIANGLE:
        current_waveform = WAVEFORM_PULSE;
        Debugln("Pulse");
        break;
      case WAVEFORM_PULSE:
        current_waveform = WAVEFORM_SAMPLE_HOLD;
        Debugln("Sample & Hold");
        break;
      case WAVEFORM_SAMPLE_HOLD:
        current_waveform = WAVEFORM_SINE;
        Debugln("Sine");
        break;
    }//switch
    for(int x = 0; x < 4; x++) {
      waveform[x].begin(current_waveform);
    }
}
