// set up all control buttons and indicator(s)

int LastOctaveUpVal = 0;
int LastOctaveDownVal = 0;
int LastButtonA = 0;
int LastButtonB = 0;
int xAxisStart;
int yAxisStart;
int xAxis;
int yAxis; 
int pitchGlobal = 0;
int octave = 4;
float frequencyMod =1;
float initalAmplitude = .5;


void initializeControls() {
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
  
   
  Debug("Starting x:");
  Debugln(xAxisStart);
  Debug("Starting y:");
  Debugln(yAxisStart);

}
