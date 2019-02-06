//start waves

void initializeWaveforms() {
  //start the wave forms
      for(int x = 0; x < 4; x++) {
    waveform[x].begin(current_waveform);
    waveform[x].amplitude(initalAmplitude);
    envelope[x].attack(10);
 //   envelope[x].decay(250);
    envelope[x].release(100);
  }
  nextWaveform = 0;
}
