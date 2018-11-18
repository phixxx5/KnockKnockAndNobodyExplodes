int Start = 13;
int Eingang = 2;
int Ausgabe = A1;
int Zeit = 300;
int stupid = 60;
boolean started = false;
int n = 1;
#include <Display.h>
#include <Digit.h>
#include <Segment.h>

const byte digit_pins[4] {1, A0, 3, 4}; // From com1 - com4
const byte segment_pins[7] {12, 10, 8, 7, 6, 11, 9}; // From a - g (abc...g)
const byte dp_pin = 5;
char* timeOut = "05.00";

Display d(digit_pins, segment_pins, dp_pin);

void setup() {
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(Start, INPUT_PULLUP);
  pinMode(Ausgabe, OUTPUT);
  pinMode(Eingang, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Eingang), incomeing, RISING);
  //Serial.begin(9800);
}

void loop() {
  if (!started) {
    d.print("0000");
    if (!digitalRead(Start)) {
      started = true;
      digitalWrite(Ausgabe, HIGH);
      digitalWrite(Ausgabe, LOW);
    }
  } else {
    if (Zeit == -1) {
      digitalWrite(Ausgabe, HIGH);
      d.print("88.88");
      started = false;
      Zeit = 300;
    } else {

      if (n == stupid) {
        int m = Zeit / 60;
        int s = Zeit % 60;
        timeOut[0] = m / 10 + 48;
        timeOut[1] = m % 10 + 48;
        timeOut[3] = s / 10 + 48;
        timeOut[4] = s % 10 + 48;
        //Serial.println(timeOut);
        Zeit--;
        n = 1;
      }
      n++;
    }

    d.print(timeOut);
    delay(10);
  }
}

void incomeing()
{
  Zeit = -1;
}
