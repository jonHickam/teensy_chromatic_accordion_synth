void initializeArray() {

    for(int x = 0; x < 4; x++) {
    waveform[x].begin(current_waveform);
    waveform[x].amplitude(initalAmplitude);
    envelope[x].attack(10);
 //   envelope[x].decay(250);
    envelope[x].release(100);
  }
  nextWaveform = 0;
      
  rSize = sizeof(rPins)/sizeof(int);
  FD(rSize);
  FD(" initializing rows ");
    for(int x = 0; x < rSize; x ++) {
   
    pinMode(rPins[x], OUTPUT);
    digitalWrite(rPins[x], LOW);
    FD(rPins[x]);
    FD(" ");
  
    for(int y=0; y < cSize; y ++) {
      buttonState[x][y] = 0;
    }
  
  }
  FunDebug(" ");
  cSize = sizeof(cPins)/sizeof(int);
  FD(cSize);
  FD(" initializing columns ");
  for(int x = 0; x < cSize; x ++) {
 
    pinMode(cPins[x], INPUT_PULLDOWN);
    FD(cPins[x]);
    FD(" ");
  }
  FunDebug(" ");

}
