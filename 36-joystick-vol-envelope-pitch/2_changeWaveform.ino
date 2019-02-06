
int current_waveform = WAVEFORM_TRIANGLE;


const float Frequency[128]=
  {8.18,8.66,9.18,9.72,10.3,10.91,11.56,12.25,12.98,13.75,14.57,15.43,16.35,
  17.32,18.35,19.45,20.6,21.83,23.12,24.5,25.96,27.5,29.14,30.87,32.7,34.65,
  36.71,38.89,41.2,43.65,46.25,49,51.91,55,58.27,61.74,65.41,69.3,73.42,77.78,
  82.41,87.31,92.5,98,103.83,110,116.54,123.47,130.81,138.59,146.83,155.56,
  164.81,174.61,185,196,207.65,220,233.08,246.94,261.63,277.18,293.66,311.13,
  329.63,349.23,369.99,392,415.3,440,466.16,493.88,523.25,554.37,587.33,622.25,
  659.26,698.46,739.99,783.99,830.61,880,932.33,987.77,1046.5,1108.73,1174.66,
  1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760,1864.66,1975.53,2093,2217.46,
  2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520,3729.31,3951.07,4186.01,
  4434.92,4698.64,4978.03,5274.04,5587.65,5919.91,6271.93,6644.88,7040,7458.62,
  7902.13,8372.02,8869.84,9397.27,9956.06,10548.08,11175.3,11839.82,12543.85
  };

void changeWaveform() {
        switch (current_waveform) {
      case WAVEFORM_SINE:
        current_waveform = WAVEFORM_SAWTOOTH;
        FunDebug("Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH:
        current_waveform = WAVEFORM_SAWTOOTH_REVERSE;
        Serial.println("Reverse Sawtooth");
        break;
      case WAVEFORM_SAWTOOTH_REVERSE:
        current_waveform = WAVEFORM_SQUARE;
        Serial.println("Square");
        break;
      case WAVEFORM_SQUARE:
        current_waveform = WAVEFORM_TRIANGLE;
        Serial.println("Triangle");
        break;
      case WAVEFORM_TRIANGLE:
        current_waveform = WAVEFORM_PULSE;
        Serial.println("Pulse");
        break;
      case WAVEFORM_PULSE:
        current_waveform = WAVEFORM_SAMPLE_HOLD;
        Serial.println("Sample & Hold");
        break;
      case WAVEFORM_SAMPLE_HOLD:
        current_waveform = WAVEFORM_SINE;
        Serial.println("Sine");
        break;
    }//switch
    for(int x = 0; x < 4; x++) {
      waveform[x].begin(current_waveform);
    }
}
