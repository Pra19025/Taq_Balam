#include "analogComp.h"

#define Aup 7
#define Bup 5
#define Cup 3
#define Adown 8
#define Bdown 4
#define Cdown 2

#define DELAY 200

// Por ahora se asume que el comparador funciona correctamente
int control_comparador = 0;
int control_secuencia = 0;

void Back_emf() {
  //En este case, se logra ir cambiando de comparador en las interrupciones
  switch (control_comparador) {
    case 0:
      // Se entró a la interrupción por el comparador A0
      control_comparador++;
      analogComparator.setOn(AIN0, A2);
      analogComparator.enableInterrupt(Back_emf, FALLING);
      break;
    case 1:
      control_comparador++;
      analogComparator.setOn(AIN0, A1);
      analogComparator.enableInterrupt(Back_emf, RISING);
      break;
    case 2:
      control_comparador++;
      analogComparator.setOn(AIN0, A0);
      analogComparator.enableInterrupt(Back_emf, FALLING);
      break;
    case 3:
      control_comparador++;
      analogComparator.setOn(AIN0, A2);
      analogComparator.enableInterrupt(Back_emf, RISING);
      break;
    case 4:
      control_comparador++;
      analogComparator.setOn(AIN0, A1);
      analogComparator.enableInterrupt(Back_emf, FALLING);
      break;
    case 5:
      control_comparador = 0;
      analogComparator.setOn(AIN0, A0);
      analogComparator.enableInterrupt(Back_emf, RISING);
      break;

  }
}


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(Aup, OUTPUT);
  pinMode(Bup, OUTPUT);
  pinMode(Cup, OUTPUT);
  pinMode(Adown, OUTPUT);
  pinMode(Bdown, OUTPUT);
  pinMode(Cdown, OUTPUT);

  digitalWrite(Aup, 0);
  digitalWrite(Bup, 0);
  digitalWrite(Cup, 1);
  digitalWrite(Adown, 0);
  digitalWrite(Bdown, 1);
  digitalWrite(Cdown, 0);

  //configuración del comparador
  analogComparator.setOn(AIN0, A0);
  //analogComparator.setOn(AIN0, A1);
  //  analogComparator.setOn(AIN0, A2);

  //se utiliza el AIN0 -> PD6
  // y A0

  analogComparator.enableInterrupt(Back_emf, RISING);

}

void loop() {
  switch (control_comparador) {
    case 0:
      // La corriente entra Por A y sale por B
      digitalWrite(Cup, 0);
      digitalWrite(Aup, 1);
      break;
    case 1:
      //La corriente Entre Por A y sale por C
      digitalWrite(Bdown, 0);
      digitalWrite(Cdown, 1);
      break;

    case 2:
      // La Corriente entra por B y Sale por C
      digitalWrite(Aup, 0);
      digitalWrite(Bup, 1);

      break;

    case 3:
      // La corriente entra por B y sale por A
      digitalWrite(Cdown, 0);
      digitalWrite(Adown, 1);
      break;


    case 4:
      //La corriente entra por C y sale por A
      digitalWrite(Cup, 1);
      digitalWrite(Bup, 0);
      break;

    case 5:
      // la corriente entra por C y sale por B
      digitalWrite(Adown, 0);
      digitalWrite(Bdown, 1);
      break;

  }
  delay(DELAY);
}
