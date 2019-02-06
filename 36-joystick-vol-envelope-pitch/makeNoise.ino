void makeNoise (int midiVal)
 {
     
     if (nextWaveform == 0)
        {
        waveformNum[0] = midiVal; 
        waveform[0].frequency(Frequency[midiVal]);
        envelope[0].noteOn();
        nextWaveform = 1;
        }
      else if (nextWaveform == 1)
        {
        waveformNum[1] = midiVal;
        nextWaveform = 2;
        waveform[1].frequency(Frequency[midiVal]);
        envelope[1].noteOn();
     
        }
      else if (nextWaveform == 2)
        {
        waveformNum[2] = midiVal;
        nextWaveform = 3;
        waveform[2].frequency(Frequency[midiVal]);
        envelope[2].noteOn();
        }
      else if  (nextWaveform == 3)
        {
        waveformNum[3] = midiVal;
        waveform[3].frequency(Frequency[midiVal]);
        envelope[3].noteOn();
        nextWaveform = 0;
        } 
 }
