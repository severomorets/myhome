void receiveData() {
  static char endMarker = '\n';
  char receivedChar;
  int ndx = 0;
  while(Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar == endMarker) {
      data[ndx] = '\0';
      return;
    }
    data[ndx] = receivedChar;
    ndx++;
    if (ndx >= DATA_MAX_SIZE) {
      break;
    }
  }
if (length(data)>1){
  char **tokens;
  int count, i;
  count = split (data, ':', &tokens);

  if (strcmp (tokens[0], "getSensorTemplateLength")==0){
     Serial.print(F("request:getSensorTemplateLength:"));Serial.println(finger.templateCount);
    }
  if (strcmp (tokens[0], "initPin")==0){
   
//      if (strcmp (tokens[2], "INPUT")==0){
//         pinMode(atoi(tokens[1]), INPUT);
//          Serial.print(F("initPin:"));Serial.print(tokens[1]);Serial.print(F(":"));Serial.print(tokens[2]);Serial.println("");
//        }
//        if (strcmp (tokens[2], "OUTPUT")==0){
//         pinMode(atoi(tokens[1]), OUTPUT);
//         digitalWrite(atoi(tokens[1]), 1);
//          Serial.print(F("initPin:"));Serial.print(tokens[1]);Serial.print(F(":"));Serial.print(tokens[2]);Serial.println("");
//        }
         
    }
    if (strcmp (tokens[0], "setPin")==0){
     
         digitalWrite(atoi(tokens[1]), atoi(tokens[2]));

         Serial.print("setPin:");Serial.print(tokens[1]);Serial.print(F(":"));Serial.print(tokens[2]);Serial.println("");
    }
    if (strcmp (tokens[0], "createUser")==0){
     createUser(tokens[1],atoi(tokens[2]));
         
    }
  memset(data, 0, sizeof(data));
  }

}
