
  void FunDebug (String msg) {
  if (ByteDebug == 1){
    Serial.println(msg);
   }
 }
 void FD (String msg) {
  if (ByteDebug == 1){
    Serial.print(msg);
   }
 }
