#include<avr/io.h>
const byte LED13 = 13;
volatile boolean bandera = false;

#define Aup 9 //PB1
#define Bup 5 //PD5
#define Cup 3 //PD3
#define Adown 8 //PB0
#define Bdown 4 //PD4
#define Cdown 2 //PD2

#define DELAY 3

int i = 0;
int volatile control_comparador = 0;
int volatile control_secuencia = 0;


void setup() {

  Serial.begin(115200);
  pinMode(LED13, OUTPUT);
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

  Serial.println("Inicio");
  //Ejecución en bucle abierto
  digitalWrite(LED13, 1);


  ACSR |= B00010000;      // Clear flag comparator interrupt (ACI bit to 1)
  ACSR &= B11011111;      // Set ACBG, to be equal to "0"
  ADCSRA = B00000000;     // Disable the ADC module
  ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
  ADMUX = 0;              // Select A0 as comparator negative input

  while (i < 300) {

    // La corriente entra Por A y sale por B
    //    digitalWrite(Cup, 0);
    //    digitalWrite(Aup, 1);
    PORTD = B00010000;
    PORTB = B00000010;
    delay(DELAY);
    //La corriente Entre Por A y sale por C
    //    digitalWrite(Bdown, 0);
    //    digitalWrite(Cdown, 1);
    PORTD = B00000100;
    PORTB = B00000010;
    delay(DELAY);
    // La Corriente entra por B y Sale por C
    //    digitalWrite(Aup, 0);
    //    digitalWrite(Bup, 1);
    PORTD = B00100100;
    PORTB = B00000000;
    delay(DELAY);
    // La corriente entra por B y sale por A
    //    digitalWrite(Cdown, 0);
    //    digitalWrite(Adown, 1);
    PORTD = B00100000;
    PORTB = B00000001;


    delay(DELAY);
    //La corriente entra por C y sale por A
    //    digitalWrite(Cup, 1);
    //    digitalWrite(Bup, 0);
    PORTD = B00001000;
    PORTB = B00000001;

    delay(DELAY);
    // la corriente entra por C y sale por B
    //    digitalWrite(Adown, 0);
    //    digitalWrite(Bdown, 1);
    PORTD = B00011000;
    PORTB = B00000000;
    delay(DELAY);
    i++;
  }
  ACSR |= B00001011;      // Set interrupt on rising edge*/


  //control_comparador = control_secuencia;
}


void loop() {


  control_secuencia = control_comparador;

  switch (control_comparador) {
    case 0:

      // La corriente entra Por A y sale por B
      //      digitalWrite(Aup, 1);
      //      digitalWrite(Bdown, 1);
      //
      //      digitalWrite(Cup, 0);
      //      digitalWrite(Adown, 0);
      //      digitalWrite(Bup, 0);
      //      digitalWrite(Cdown, 0);

      PORTD = B00010000;
      PORTB = B00000010;


      break;
    case 1:
      //La corriente Entre Por A y sale por C
      //      digitalWrite(Aup, 1);
      //      digitalWrite(Cdown, 1);
      //
      //      digitalWrite(Bdown, 0);
      //      digitalWrite(Adown, 0);
      //      digitalWrite(Bup, 0);
      //      digitalWrite(Cup, 0);

      PORTD = B00000100;
      PORTB = B00000010;


      break;

    case 2:
      // La Corriente entra por B y Sale por C
      //      digitalWrite(Bup, 1);
      //      digitalWrite(Cdown, 1);
      //
      //      digitalWrite(Aup, 0);
      //      digitalWrite(Adown, 0);
      //      digitalWrite(Cup, 0);
      //      digitalWrite(Bdown, 0);

      PORTD = B00100100;
      PORTB = B00000000;


      break;

    case 3:
      // La corriente entra por B y sale por A
      //      digitalWrite(Adown, 1);
      //      digitalWrite(Bup, 1);
      //
      //      digitalWrite(Cdown, 0);
      //      digitalWrite(Aup, 0);
      //      digitalWrite(Bdown, 0);
      //      digitalWrite(Cup, 0);

      PORTD = B00100000;
      PORTB = B00000001;


      break;

    case 4:
      //La corriente entra por C y sale por A
      //      digitalWrite(Cup, 1);
      //      digitalWrite(Adown, 1);
      //
      //      digitalWrite(Bup, 0);
      //      digitalWrite(Aup, 0);
      //      digitalWrite(Bdown, 0);
      //      digitalWrite(Cdown, 0);

      PORTD = B00001000;
      PORTB = B00000001;


      break;

    case 5:
      // la corriente entra por C y sale por B

      //      digitalWrite(Cup, 1);
      //      digitalWrite(Bdown, 1);
      //
      //      digitalWrite(Aup, 0);
      //      digitalWrite(Bup, 0);
      //      digitalWrite(Adown, 0);
      //      digitalWrite(Cdown, 0);

      PORTD = B00011000;
      PORTB = B00000000;


      break;

  }
//  Serial.print("Comparador: ");
//  Serial.println(control_comparador);
//  Serial.print("Secuencia: ");
//  Serial.println(control_secuencia);

  if (control_comparador == control_secuencia) {
    if (control_comparador < 6) {
      control_comparador++;
    }
    else{
      control_comparador = 0;
    }
  }


  //delay(3);
  //delayMicroseconds(500);




}


ISR (ANALOG_COMP_vect) {
  //delayMicroseconds(5);
  Serial.println(control_comparador);
  switch (control_comparador) {
    case 0:
      // Se entró a la interrupción por el comparador A0
      control_comparador = 1;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 3;

      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);


      //ACSR |= B00000010;      // Remember top set back the interrupt on falling edge for next ISR
      break;
    case 1:
      control_comparador = 2;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 1;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR

      break;
    case 2:
      control_comparador = 3;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 0;
      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);


      break;
    case 3:
      control_comparador = 4;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 3;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
      break;
    case 4:
      control_comparador = 5;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 1;
      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);

      break;
    case 5:
      control_comparador = 0;
      ADCSRA = B00000000;     // Disable the ADC module
      ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
      ADMUX = 0;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
      break;

  }

}
