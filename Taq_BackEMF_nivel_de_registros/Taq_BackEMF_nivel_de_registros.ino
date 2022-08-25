const byte LED13 = 13;
volatile boolean enableLed = false;

void setup() {

  pinMode(LED13, OUTPUT);

  
  // put your setup code here, to run once:
  ACSR = 0x10;  //Limpiar bandera de interrupción del comparador
  ADCSRA = (0 << ADEN); // Deshabilitar modulo ADC, por que se van a usar los canales para como negative
  // inputs del comparador
  // Lo de << permite indicar el bit que se va a poner en 0.

  ADCSRB = (1 << ACME);  // Se habilita el multiplexor para las entradas del comparador

  ADMUX = 0;  // Se selecciona A0 como negative input
  // ADMUX = 1 para A1
  // ADMUX = 2 para A2

  ACSR |= 0x03; // interrupción rising edge


}

void loop() {
      if (enableLed) { //let's check if the analog comparator has raised the interrupt
        //yes, so we do a little blink of the LED
        digitalWrite(LED13, HIGH);
        delay(200);
        digitalWrite(LED13, LOW);
        enableLed = false;
    }

}  


ISR (ANALOG_COMP_vect) {

    if (!(ACSR & B00100000)) { //revisar el valor de ACO, si es 0, y se esta en falling
      //significa que la salida del comparador cambio de 0 a 1

    }

    else{
      if(ACSR & B00100000){ //revisar el valor de ACO, si es 1, y estamos en rising, 
        // significa que la salida del comparador cambio de 0 a 1
        enableLed = true;
      }
  }
  ACSR |= 0x03; //reactivar la interrupción
}
