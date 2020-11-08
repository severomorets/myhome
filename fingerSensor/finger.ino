// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();

  if (p != FINGERPRINT_OK)  return -1;
//   Serial.print("finger:"); Serial.print("error");  Serial.print(":");Serial.println(p);
  p = finger.image2Tz();
//  Serial.print("finger:"); Serial.print("error");  Serial.print(":");Serial.println(p);
  if (p != FINGERPRINT_OK)  return -1;
//  Serial.print("finger:"); Serial.print("error");  Serial.print(":");Serial.println(p);
  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {
     if (p == FINGERPRINT_NOTFOUND) {
      Serial.println("Did not find a match");
      }
//     Serial.print("finger:"); Serial.print("error");  Serial.print(":");Serial.println(finger.confidence);
//    delay(1000);
    return -1;
    }
  Serial.print("finger:"); Serial.print(finger.fingerID);  Serial.print(":");Serial.println(finger.confidence);
//   delay(3000);
//  digitalWrite(52, LOW); 
//  delay(1000);
//  digitalWrite(52, 1); 
if (doorStatus==true){
  door1.write(180);  
  Serial.println("sssssssss1:"); 
  doorStatus = false;
   delay(1000); 
  }else if (doorStatus==false){
  door1.write(0);  
  doorStatus = true;
   delay(1000); 
  }
//delay(500);  
//   door1.write(0);
//   delay(1000);   
//   door1.write(180);
//   delay(1000); 
  return finger.fingerID;
}
int createUser(char* username, int id) {
 Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
   
  }
  p = finger.image2Tz(1);
  if (p != FINGERPRINT_OK)  return -1;
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
  }
  p = finger.image2Tz(2);
  if (p != FINGERPRINT_OK)  return -1;
   Serial.print("Creating model for #");  Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK){
    Serial.println("Prints matched!");
    }

  p = finger.storeModel(id);
if (p == FINGERPRINT_OK) {
    Serial.print("createUser:");Serial.print(username);Serial.print(":");Serial.println(id);
  }
//  Serial.print("READY!!! ");  Serial.println(id);
  delay(3000);


}
