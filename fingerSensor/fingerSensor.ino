#include <Servo.h>
#include <Adafruit_Fingerprint.h>
#define mySerial Serial1

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
const byte DATA_MAX_SIZE = 32;
char data[DATA_MAX_SIZE]; 
int btn1 = 1;
int btn2 = 1;
int btn3 = 1;
int btn4 = 1;
int btn5 = 1;
int btn6 = 1;
int btn7 = 1;
int btn8 = 1;
int btn9 = 1;
int btn10 = 1;
int btn11 = 1;
int btn12 = 1;
int btn13 = 1;
int btn14 = 1;
int btn15 = 1;
int btn16 = 1;
const int SPEAKER=6;
int notes[] = {
392, 392, 392, 311, 466, 392, 311, 466, 392,
587, 587, 587, 622, 466, 369, 311, 466, 392,
784, 392, 392, 784, 739, 698, 659, 622, 659,
415, 554, 523, 493, 466, 440, 466,
311, 369, 311, 466, 392
};
int times[] = {
350, 350, 350, 250, 100, 350, 250, 100, 700,
350, 350, 350, 250, 100, 350, 250, 100, 700,
350, 250, 100, 350, 250, 100, 100, 100, 450,
150, 350, 250, 100, 100, 100, 450,
150, 350, 250, 100, 750
};
Servo door1;
boolean doorStatus = false;
int sensorValueMq9 = 0;

void setup()
{
    door1.attach(7);//дверь
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


  
   pinMode(23, INPUT);
   pinMode(25, INPUT);
   pinMode(27, INPUT);
   pinMode(29, INPUT);
   pinMode(31, INPUT);
   pinMode(33, INPUT);
   pinMode(35, INPUT);
   pinMode(37, INPUT);
   pinMode(39, INPUT);
   pinMode(41, INPUT);
   pinMode(43, INPUT);
   pinMode(45, INPUT);
   pinMode(47, INPUT);
   pinMode(49, INPUT);
   pinMode(51, INPUT);
   pinMode(53, INPUT);

   pinMode(6, OUTPUT);//пищалка
   pinMode(22, OUTPUT);
   pinMode(24, OUTPUT);
   pinMode(26, OUTPUT);
   pinMode(28, OUTPUT);
   pinMode(30, OUTPUT);
   pinMode(32, OUTPUT);
   pinMode(34, OUTPUT);
   pinMode(36, OUTPUT);
   pinMode(38, OUTPUT);
   pinMode(40, OUTPUT);
   pinMode(42, OUTPUT);
   pinMode(44, OUTPUT);
   pinMode(46, OUTPUT);
   pinMode(48, OUTPUT);
   pinMode(50, OUTPUT);
   pinMode(52, OUTPUT);
   
   digitalWrite(22, btn1);
   digitalWrite(24, btn2);
   digitalWrite(26, btn3);
   digitalWrite(28, btn4);
   digitalWrite(30, btn5);
   digitalWrite(32, btn6);
   digitalWrite(34, btn7);
   digitalWrite(36, btn8);
   digitalWrite(38, btn9);
   digitalWrite(40, btn10);
   digitalWrite(42, btn11);
   digitalWrite(44, btn12);
   digitalWrite(46, btn13);
   digitalWrite(48, btn14);
   digitalWrite(50, btn15);
   digitalWrite(52, btn16);
  


   
  Serial.println("status:ready:1");
}

void loop()
{

   receiveData();
  getFingerprintIDez();
  buttonClick();
 
}
