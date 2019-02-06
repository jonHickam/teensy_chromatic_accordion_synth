//read what buttons are being pressed and either start or stop the note
void readArray() {
  for(int rInt = 0; rInt < rSize; rInt ++) {
   
    digitalWrite(rPins[rInt], HIGH);
    delay(5);
    for(int cInt = 0; cInt < cSize; cInt ++) {
      int val = digitalRead(cPins[cInt]);

      buttonChecker(val,rInt, cInt);
      
    } // c loop
    
  
    digitalWrite(rPins[rInt],LOW);
    
  } // r loop
} //readArray

void buttonChecker(int val, int rInt, int cInt){
  if( val == 1 && buttonState[rInt][cInt] == 0) { // this is a button press

      int note = midiNumber(rInt,cInt);
      usbMIDI.sendNoteOn(note, 99, midiChannel);
      makeNoise(note);
      buttonState[rInt][cInt] = val;
      
  }
  else if ( val == 0 && buttonState[rInt][cInt] == 1) { // this is a button release
      int note = midiNumber(rInt,cInt);
      usbMIDI.sendNoteOff(note, 0, midiChannel);
      if ( waveformNum[0] == note)
        {
           envelope[0].noteOff();
           nextWaveform = 0;
           waveformNum[0] = 0;
        }
      else if ( waveformNum[1] == note)
        {
           envelope[1].noteOff();
           nextWaveform = 1;
           waveformNum[1] = 0;
        }
      else if ( waveformNum[2] == note)
        {
           envelope[2].noteOff();
           nextWaveform = 2;
           waveformNum[2] = 0;
        }
     else if ( waveformNum[3] == note)
        {
           envelope[3].noteOff();
           nextWaveform = 3;
           waveformNum[3] = 0;
        }           

      buttonState[rInt][cInt] = val;

  }
}
