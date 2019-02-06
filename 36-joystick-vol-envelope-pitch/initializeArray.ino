void initializeArray() {

    
  rSize = sizeof(rPins)/sizeof(int);
  Debug(rSize);
  Debug(" initializing rows ");
    for(int x = 0; x < rSize; x ++) {
   
    pinMode(rPins[x], OUTPUT);
    digitalWrite(rPins[x], LOW);
    Debug(rPins[x]);
    Debug(" ");
  
    for(int y=0; y < cSize; y ++) {
      buttonState[x][y] = 0;
    }
  
  }
  Debugln(" ");
  cSize = sizeof(cPins)/sizeof(int);
  Debug(cSize);
  Debug(" initializing columns ");
  for(int x = 0; x < cSize; x ++) {
 
    pinMode(cPins[x], INPUT_PULLDOWN);
    Debug(cPins[x]);
    Debug(" ");
  }
  Debugln(" ");

}
