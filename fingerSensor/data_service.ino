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
//Serial.println(strcmp (tokens[0], "getSensorTemplateLength"));
  if (strcmp (tokens[0], "getSensorTemplateLength")==0){
     Serial.print(F("request:getSensorTemplateLength:"));Serial.println(finger.templateCount);
    }
  
  memset(data, 0, sizeof(data));
  }

}
