
#include <Audio.h>
#include <Wire.h>


//#include <SD.h>

AudioSynthWaveform       waveform[4];

AudioEffectEnvelope   envelope[4];
\
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

const int midiChannel = 1;


int rPins[] = {7, 8, 9, 10, 11, 23, 22, 21, 20, 19};
int cPins[] = {0, 1, 2, 3, 4, 5, 6};
int insideLed = 24;
int outsideLed = 27;
int octaveUpPin = 28;
int octaveDownPin = 29;
int buttonAPin = 30;
int buttonBPin = 31;
int buttonCPin = 32;
int buttonDPin = 33;
int controlButtonPin = 36;  
int JoyXPin = A15;
int JoyYPin = A16;
int rSize;
int cSize;
byte buttonState[10][7];
int waveformNum[4] = {0, 1, 2, 3};
int octive = 4;
int LastOctiveUpVal = 0;
int LastOctiveDownVal = 0;
int LastButtonA = 0;
int LastButtonB = 0;
int xAxisStart;
int yAxisStart;
int xAxis;
int yAxis; 
float frequencyMod =1;
float initalAmplitude = .5;
int nextWaveform;
int pitchGlobal = 0;

elapsedMillis JoystickReadMillis = 0;
//extern const int16_t myWaveform[256];  // defined in myWaveform.ino
//waveform1.arbitraryWaveform(myWaveform, 172.0);


int waveState[3];


void setup() {
  // put your setup code here, to run once:
  // get up control buttons

  pinMode(insideLed, OUTPUT);
  pinMode(outsideLed, OUTPUT);
  pinMode(octaveUpPin, INPUT_PULLDOWN);
  pinMode(octaveDownPin, INPUT_PULLDOWN);
  pinMode(buttonAPin, INPUT_PULLDOWN);
  pinMode(buttonBPin, INPUT_PULLDOWN);
  pinMode(buttonCPin, INPUT_PULLDOWN);
  pinMode(buttonDPin, INPUT_PULLDOWN);
  pinMode(controlButtonPin, OUTPUT);
  digitalWrite(controlButtonPin, LOW);


  xAxisStart = analogRead(JoyXPin);
  yAxisStart = analogRead(JoyYPin);

  xAxis = xAxisStart;
  yAxis = yAxisStart;
  
    //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Starting x");
  Serial.println(xAxisStart);
  AudioMemory(20);

  for(int x = 0; x < 4; x++) {
    waveform[x].begin(current_waveform);
    waveform[x].amplitude(initalAmplitude);
    envelope[x].attack(10);
 //   envelope[x].decay(250);
    envelope[x].release(100);
  }
  nextWaveform = 0;
      
  rSize = sizeof(rPins)/sizeof(int);
  Serial.print(rSize);
  Serial.print(" initializing rows ");
    for(int x = 0; x < rSize; x ++) {
   
    pinMode(rPins[x], OUTPUT);
    digitalWrite(rPins[x], LOW);
    Serial.print(rPins[x]);
    Serial.print(" ");
  
    for(int y=0; y < cSize; y ++) {
      buttonState[x][y] = 0;
    }
  
  }
  Serial.println(" ");
  cSize = sizeof(cPins)/sizeof(int);
  Serial.print(cSize);
  Serial.print(" initializing columns ");
  for(int x = 0; x < cSize; x ++) {
 
    pinMode(cPins[x], INPUT_PULLDOWN);
    Serial.print(cPins[x]);
    Serial.print(" ");
  }
  Serial.println(" ");
}




void loop() {
  // put your main code here, to run repeatedly:

  // read the control buttons.  First send them current
  digitalWrite(controlButtonPin,HIGH);
  delay(5);
  // then read the values
  int OctiveUpVal = digitalRead(octaveUpPin);
  int OctiveDownVal = digitalRead(octaveDownPin);
  int ButtonA = digitalRead(buttonAPin);
  int ButtonB = digitalRead(buttonBPin);

  // then do what is needed based on what was read

  // change octaves 
  if (OctiveUpVal == 1 && LastOctiveUpVal== 0 && octive < 6) {
    octive++;
    Serial.println("Octive Up");
  }
  if (OctiveDownVal == 1  && LastOctiveDownVal == 0 && octive > 0) {
    octive--;
    Serial.println("Octive Down");
  }

  // change wave types
  if (ButtonA == 1  && LastButtonA == 0 ) {
    Serial.println("Button A");
        switch (current_waveform) {
      case WAVEFORM_SINE:
        current_waveform = WAVEFORM_SAWTOOTH;
        Serial.println("Sawtooth");
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
    }
    for(int x = 0; x < 4; x++) {
      waveform[x].begin(current_waveform);
    }
  }

  // change pitch bend from single note to global
  if (ButtonB == 1  && LastButtonB == 0  ) {
    if ( pitchGlobal == 1) {
      pitchGlobal = 0;
    }
    else if ( pitchGlobal == 0) {
      pitchGlobal = 1;
    }
    
  } // ButtonB pressed

  
  digitalWrite(controlButtonPin,LOW);  // turn off power to control pins
  LastOctiveUpVal = OctiveUpVal;
  LastOctiveDownVal = OctiveDownVal; 
  LastButtonA = ButtonA;
  LastButtonB = ButtonB;
  // read the joysticks
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
  
  
  // read the array
  for(int rInt = 0; rInt < rSize; rInt ++) {
   
    digitalWrite(rPins[rInt], HIGH);
    delay(5);
    for(int cInt = 0; cInt < cSize; cInt ++) {
      int val = digitalRead(cPins[cInt]);

      checker(val,rInt, cInt);
      
    } // c loop
    
  
    digitalWrite(rPins[rInt],LOW);
    
  } // r loop
}

void checker(int val, int rInt, int cInt){
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

void makeNoise (int midiVal)
 {
 //    Serial.print("next: waveform");
 //    Serial.println(nextWaveform);
      // find a waveform that is available and reserve it.
  //   AudioNoInterrupts();
     
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
