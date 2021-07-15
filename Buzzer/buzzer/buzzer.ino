#include "Volume3.h"

int nada[] = {
  0, 523, 587, 659, 698,  783, 880, 987, 1046, 1174,
  1318, 1396, 1567, 1769, 1975, 2093
};

int buzzPin = 9;
int amp = 300;
int led1 = 7;
int led2 = 8;

void setup() {
  pinMode(2, OUTPUT);
}

void bunyi(int nadaKe, int lama)
{

  vol.tone(buzzPin, nada[nadaKe], amp);
  digitalWrite(2, LOW);
  delay(lama / 2);  
  digitalWrite(2, HIGH);
  delay(lama / 2);
}

void tesNada()
{
  for (int x = 0; x < 16; x++) {
    bunyi(x, 500);
  }
  for (int x = 16; x > 0; x--) {
    bunyi(x, x*20);
  }
}

void loop() {
//  tesNada();

  digitalWrite(led1, HIGH);
  vol.tone(buzzPin, nada[1], amp);
  delay(1000);
  digitalWrite(led1, LOW);
  delay(500);
  digitalWrite(led2, HIGH);
  vol.tone(buzzPin, nada[2], amp);
  delay(1000);
  digitalWrite(led2, LOW);
  delay(900);

}
