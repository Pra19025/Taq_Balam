
#define Aup 7
#define Bup 5
#define Cup 3
#define Adown 6
#define Bdown 4
#define Cdown 2
#define DELAY 50


int HA;
int HB;
int HC;

volatile int control;

ISR (PCINT0_vect) {
  HC = digitalRead(9);
  HB = digitalRead(10);
  HA = digitalRead(11);

  Serial.print("HC ");
  Serial.print(HC);

  Serial.print(" HB ");
  Serial.print(HB);

  Serial.print(" HA ");
  Serial.println(HA);
  //Serial.println(PINB & B00001110 , BIN);

  switch (PINB & B00001110) {
    case B00000110:
      control = 1;
      break;

    case B00000100:
      control = 2;
      break;

    case B00001100:
      control = 3;
      break;

    case B00001000:
      control = 4;
      break;

    case B00001010:
      control = 5;
      break;


    case B00000010:
      control = 6;
      break;

  }




}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);

  PCICR |= B00000001;
  PCMSK0 |= B00001110;


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

}

void loop() {

  //EL orden es ABC
  //Con los sensores el orden es inverso, va del 11, 10, 9

  switch (control) {
    case 1:
      // La corriente entra Por A y sale por B
      digitalWrite(Cup, 0);
      digitalWrite(Aup, 1);
      break;

    case 2:
      //La corriente Entre Por A y sale por C
      digitalWrite(Bdown, 0);
      digitalWrite(Cdown, 1);
      break;

    case 3:
      // La Corriente entra por B y Sale por C
      digitalWrite(Aup, 0);
      digitalWrite(Bup, 1);

      break;

    case 4:
      // La corriente entra por B y sale por A
      digitalWrite(Cdown, 0);
      digitalWrite(Adown, 1);
      break;


    case 5:
      //La corriente entra por C y sale por A
      digitalWrite(Cup, 1);
      digitalWrite(Bup, 0);
      break;

    case 6:
      // la corriente entra por C y sale por B
      digitalWrite(Adown, 0);
      digitalWrite(Bdown, 1);
      break;
  }
  //delay(DELAY);
}
