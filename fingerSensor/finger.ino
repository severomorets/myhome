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
