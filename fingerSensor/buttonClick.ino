void buttonClick() {
 
  if (digitalRead(23) == HIGH) {
    if (btn1==1) btn1 = 0;else btn1 = 1;
    digitalWrite(22, btn1); delay(1000);
  }
 if (digitalRead(25) == HIGH) {
    if (btn2==1) btn2 = 0;else btn2 = 1;
    digitalWrite(24, btn2); delay(1000);
  }
  if (digitalRead(27) == HIGH) {
    if (btn3==1) btn3 = 0;else btn3 = 1;
    digitalWrite(26, btn3); delay(1000);
  }
  if (digitalRead(29) == HIGH) {
    if (btn4==1) btn4 = 0;else btn4 = 1;
    digitalWrite(28, btn4); delay(1000);
  }
  if (analogRead(A0)>=60) {
     digitalWrite(6, HIGH);
    for (int i = 0; i < 39; i++){
      
      
      tone(SPEAKER, notes[i], times[i]*2);
      digitalWrite(26, LOW); 
      digitalWrite(24, LOW); 
      digitalWrite(22, LOW); 
      delay((times[i]*2)/2);
      noTone(SPEAKER);
      digitalWrite(26, HIGH);
      digitalWrite(24, HIGH); 
      digitalWrite(22, HIGH);
      delay((times[i]*2)/2);
      }
      digitalWrite(26, HIGH);
      digitalWrite(24, LOW); 
      digitalWrite(22, LOW);
       
  } else {
     digitalWrite(6, LOW);
    }
    
    
}
