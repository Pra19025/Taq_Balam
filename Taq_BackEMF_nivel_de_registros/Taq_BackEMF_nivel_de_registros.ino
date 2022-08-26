const byte LED13 = 13;
volatile boolean bandera = false;

#define Aup 7
#define Bup 5
#define Cup 3
#define Adown 8
#define Bdown 4
#define Cdown 2

int A = 0;


#define DELAY 2

int control_comparador = 0;
int control_secuencia = 0;


void setup() {
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

  //pinMode(LED13, OUTPUT);
  //Serial.begin(9600);


  //Ejecución en bucle abierto
  int i = 0;
digitalWrite(LED13, 1);
  while(i<1000){
   
        // La corriente entra Por A y sale por B
        digitalWrite(Cup, 0);
        digitalWrite(Aup, 1);
        control_comparador=1;
        delay(DELAY);
        //La corriente Entre Por A y sale por C
        digitalWrite(Bdown, 0);
        digitalWrite(Cdown, 1);
        control_comparador=2;
         delay(DELAY);
        digitalWrite(Aup, 0);
        digitalWrite(Bup, 1);
        control_comparador=3;
        delay(DELAY);
        // La corriente entra por B y sale por A
        digitalWrite(Cdown, 0);
        digitalWrite(Adown, 1);
        control_comparador=4;
        delay(DELAY);
        //La corriente entra por C y sale por A
        digitalWrite(Cup, 1);
        digitalWrite(Bup, 0);
        control_comparador=5;
        delay(DELAY);
        // la corriente entra por C y sale por B
        digitalWrite(Adown, 0);
        digitalWrite(Bdown, 1);
        control_comparador=0;
        delay(DELAY);
        i++;
  }

  //Serial.println("Entramos");
  
  ACSR |= B00010000;      // Clear flag comparator interrupt (ACI bit to 1)
  ACSR &= B11011111;      // Set ACBG, to be equal to "0"
  ADCSRA = B00000000;     // Disable the ADC module because
  ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
  ADMUX = 0;              // Select A0 as comparator negative input
  ACSR |= B00001011;      // Set interrupt on rising edge*/
 i = 0;
while(i<1000 && !bandera){
    switch (control_comparador) {
      case 0:
        // La corriente entra Por A y sale por B
        digitalWrite(Cup, 0);
        digitalWrite(Aup, 1);
        control_comparador=1;
        break;
      case 1:
        //La corriente Entre Por A y sale por C
        digitalWrite(Bdown, 0);
        digitalWrite(Cdown, 1);
        control_comparador=2;
        break;
  
      case 2:
        // La Corriente entra por B y Sale por C
        digitalWrite(Aup, 0);
        digitalWrite(Bup, 1);
        control_comparador=3;
        break;
  
      case 3:
        // La corriente entra por B y sale por A
        digitalWrite(Cdown, 0);
        digitalWrite(Adown, 1);
        control_comparador=4;
        break;
  
  
      case 4:
        //La corriente entra por C y sale por A
        digitalWrite(Cup, 1);
        digitalWrite(Bup, 0);
        control_comparador=5;
        break;
  
      case 5:
        // la corriente entra por C y sale por B
        digitalWrite(Adown, 0);
        digitalWrite(Bdown, 1);
        control_comparador=0;
        break;
  }
  i++;
  delay(DELAY);
}

  //Serial.println("Salimos");
  digitalWrite(LED13, 0);
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


ISR (ANALOG_COMP_vect) {
  bandera = true;
  //delayMicroseconds(200);
 // A = digitalRead(LED13);
  

  //control_comparador++;

  //  if (ACSR & B00100010)            //If we are into falling edge
  //  {
  //    if (!(ACSR & B00100000)) {     //If ACO is 0 (we have that ! for inverse)
  //      //A change from HIGH to LOW was detected
  //      //Do what you want to do here...
  //      //enableLed = true;
  //      //ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
  //      control_comparador++;
  //    }
  //  }
  //  else                              //else, if we are into rising edge
  //  {
  //    if ((ACSR & B00100000)) {       //If ACO is 1
  //      //A change from LOW to HIGH was detected
  //      //Do what you want to do here...
  //      //enableLed = true;
  //      //ACSR |= B00000010;      // Remember top set back the interrupt on falling edge for next ISR
  //      control_comparador++;
  //    }
  //  }

  switch (control_comparador) {
    case 0:
      // Se entró a la interrupción por el comparador A0
      control_comparador=1;
      ADMUX = 2;

      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);

      //ACSR |= B00000010;      // Remember top set back the interrupt on falling edge for next ISR
      break;
    case 1:
      control_comparador=2;
      ADMUX = 1;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
      break;
    case 2:
      control_comparador=3;
      ADMUX = 0;
      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);

      break;
    case 3:
      control_comparador=4;
      ADMUX = 2;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
      break;
    case 4:
      control_comparador=5;
      ADMUX = 1;
      ACSR |= (1 << 1);
      ACSR &= ~(1 << 0);

      break;
    case 5:
      control_comparador = 0;
      ADMUX = 0;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
      break;


  }

}
