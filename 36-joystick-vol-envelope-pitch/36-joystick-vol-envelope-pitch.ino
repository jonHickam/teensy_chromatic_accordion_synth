
#include <Audio.h>
#include <Wire.h>

AudioSynthWaveform       waveform[4];
AudioEffectEnvelope   envelope[4];
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


const int midiChannel = 1;

int current_waveform = WAVEFORM_TRIANGLE;


int rPins[] = {7, 8, 9, 10, 11, 23, 22, 21, 20, 19};
int cPins[] = {0, 1, 2, 3, 4, 5, 6};
int LEDPin = 14;
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
int octave = 4;
int LastOctaveUpVal = 0;
int LastOctaveDownVal = 0;
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
int ByteDebug = 0;
//elapsedMillis JoystickReadMillis = 0;
//extern const int16_t myWaveform[256];  // defined in myWaveform.ino
//waveform1.arbitraryWaveform(myWaveform, 172.0);


//int waveState[3];


void setup() {
  // put your setup code here, to run once:
  // get up control buttons

  pinMode(LEDPin, OUTPUT);
  pinMode(octaveUpPin, INPUT_PULLDOWN);
  pinMode(octaveDownPin, INPUT_PULLDOWN);
  pinMode(buttonAPin, INPUT_PULLDOWN);
  pinMode(buttonBPin, INPUT_PULLDOWN);
  pinMode(buttonCPin, INPUT_PULLDOWN);
  pinMode(buttonDPin, INPUT_PULLDOWN);
  pinMode(controlButtonPin, OUTPUT);
  digitalWrite(controlButtonPin, LOW);
  digitalWrite(LEDPin, HIGH);


  xAxisStart = analogRead(JoyXPin);
  yAxisStart = analogRead(JoyYPin);

  xAxis = xAxisStart;
  yAxis = yAxisStart;
  
    //Initialize serial and wait for port to open:
  if (ByteDebug == 1){
  Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
   
  }
 
  FD("Starting x:");
  FunDebug(xAxisStart);
  AudioMemory(20);


  initializeArray();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //start the wave forms
      for(int x = 0; x < 4; x++) {
    waveform[x].begin(current_waveform);
    waveform[x].amplitude(initalAmplitude);
    envelope[x].attack(10);
 //   envelope[x].decay(250);
    envelope[x].release(100);
  }
  nextWaveform = 0;
  

  // read the control buttons.  
  readButtons();
  
  // read the joysticks
  readJoystick() ;

  // read the array
  readArray();
}

     
