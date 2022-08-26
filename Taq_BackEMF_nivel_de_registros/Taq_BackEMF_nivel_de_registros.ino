const byte LED13 = 13;
volatile boolean enableLed = false;

void setup() {

  pinMode(LED13, OUTPUT);

  ACSR |= B00010000;      // Clear flag comparator interrupt (ACI bit to 1)
  ACSR &= B11011111;      // Set ACBG, to be equal to "0"
  ADCSRA = B00000000;     // Disable the ADC module because
  ADCSRB = B01000000;     // Enable the MUX selector for negative input of comparator
  ADMUX = 1;              // Select A0 as comparator negative input
  ACSR |= B00001011;      // Set interrupt on rising edge*/

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
  if (ACSR & B00100010)            //If we are into falling edge
  {
    if (!(ACSR & B00100000)) {     //If ACO is 0 (we have that ! for inverse)
      //A change from HIGH to LOW was detected
      //Do what you want to do here...
      enableLed = true;
      ACSR |= B00000011;      // Remember top set back the interrupt on rising edge for next ISR
    }
  }
  else                              //else, if we are into rising edge
  {
    if ((ACSR & B00100000)) {       //If ACO is 1
      //A change from LOW to HIGH was detected
      //Do what you want to do here...
      //enableLed = true;
      ACSR |= B00000010;      // Remember top set back the interrupt on falling edge for next ISR
    }
  }

}
