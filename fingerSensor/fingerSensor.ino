
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

  // set the data rate for the sensor serial port
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

void loop()                     // run over and over again
{
  getFingerprintID();
  receiveData();
  delay(50);            //don't ned to run this at full speed.
}
unsigned int length(char const* s) {
    unsigned int i = 0;
    while (*s++ != '\0')
        ++i;

    return i;
}
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

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
//      Serial.println("events:finger1:FINGERPRINT_OK");
      break;
    case FINGERPRINT_NOFINGER:
//      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("events:finger1:FINGERPRINT_PACKETRECIEVEERR");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("events:finger1:FINGERPRINT_IMAGEFAIL");
      return p;
    default:
      Serial.println("events:finger1:Unknown_error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("events:finger1:Преобразованное изображение");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("events:finger1:Изображение слишком грязное");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("events:finger1:Ошибка связи");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("events:finger1:Не удалось найти отпечатков пальцев");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("events:finger1:Не удалось найти отпечатков пальцев");
      return p;
    default:
      Serial.println("events:finger1:Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("events:finger1:Нашел совпадение по отпечатку!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("events:finger1:Ошибка связи");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("events:finger1:Не нашел совпадение по отпечатку");
    return p;
  } else {
    Serial.println("events:finger1:Unknown error");
    return p;
  }

  // found a match!
  Serial.print("events:finger1:Нашел совпадение id "); Serial.print(finger.fingerID);
  Serial.print("confidence "); Serial.println(finger.confidence);

  return finger.fingerID;
}
int split (const char *txt, char delim, char ***tokens)
{
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }
    free (tklen);
    return count;
}
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" вероятность "); Serial.println(finger.confidence);
  return finger.fingerID;
}
