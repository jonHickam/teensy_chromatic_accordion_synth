//debug functions
  void Debugln (String msg) {
  if (ByteDebug == 1){
    Serial.println(msg);
   }
 }
 void Debug (String msg) {
  if (ByteDebug == 1){
    Serial.print(msg);
   }
 }
