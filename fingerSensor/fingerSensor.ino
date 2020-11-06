
#include <Adafruit_Fingerprint.h>
#define mySerial Serial1

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
const byte DATA_MAX_SIZE = 32;
char data[DATA_MAX_SIZE]; 

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("status:board1:1");
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("status:finger:1");
  } else {
    Serial.println("status:finger:0");
    while (1) { delay(1); }
  }

  finger.getParameters();
  finger.getTemplateCount();
}

void loop()
{
  getFingerprintID();
  receiveData();
  delay(50); 
}
