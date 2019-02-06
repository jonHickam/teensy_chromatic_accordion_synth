void readJoystick() {
  

    if (JoystickReadMillis >= 50) {
    JoystickReadMillis = 0;
      
    float latestRead = analogRead(JoyXPin);
    if (abs(latestRead - xAxis) > 10){
      frequencyMod = map(latestRead,1,1024,1056,944);
      xAxis = latestRead;
   //   usbMIDI.sendControlChange(xAxisController, xAxisPin, channel);

        if (pitchGlobal == 0) {                             // just bend the last note played

          if (nextWaveform == 1 && waveformNum[0] > 0  )
            {
            waveform[0].frequency(Frequency[waveformNum[0]]* frequencyMod /1000) ;
            }
          else if (nextWaveform == 2 && waveformNum[1] > 0  )
            {
            waveform[1].frequency(Frequency[waveformNum[1]]* frequencyMod /1000) ;
            }
          else if (nextWaveform == 3 && waveformNum[2] > 0  )
            {
            waveform[2].frequency(Frequency[waveformNum[2]]* frequencyMod /1000) ;
            }
          else if (nextWaveform == 0 && waveformNum[3] > 0  )
            {
            waveform[3].frequency(Frequency[waveformNum[3]]* frequencyMod /1000) ;
            }
        }
        else if (pitchGlobal == 1) {                      // bend all of the notes
          for (int x = 0; x< 4; x++){
            waveform[x].frequency(Frequency[waveformNum[x]]* frequencyMod /1000) ;
          }
        }
 
    } //xAxis read
    
    latestRead = analogRead(JoyYPin);
    if (abs(latestRead - yAxis) > 10){
      float yMapped = map(latestRead,1,1024,2.0,0.0);
      amp1.gain(yMapped);
   //   usbMIDI.sendControlChange(yAxisController, yAxisPin, channel);
      yAxis = latestRead;
    }  //yAxis read
    
   } // msec timer   
  
} // readJoystick
