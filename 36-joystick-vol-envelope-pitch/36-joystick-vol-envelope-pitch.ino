
#include <Audio.h>
#include <Wire.h>


const int midiChannel = 1;
int current_waveform = WAVEFORM_TRIANGLE;
int nextWaveform;

int ByteDebug = 0;


//int waveState[3];


void setup() {
  // put your setup code here, to run once:
  //Initialize serial and wait for port to open:
  if (ByteDebug == 1){
  Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  }
  
  AudioMemory(20);

  initializeArray();
  initializeWaveforms();
  initializeControls();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  

  // read the control buttons.  
  readButtons();
  
  // read the joysticks
  readJoystick() ;

  // read the array
  readArray();
}

     
