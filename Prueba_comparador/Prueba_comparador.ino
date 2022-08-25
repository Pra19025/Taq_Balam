#include "analogComp.h"

//global variables
const byte LED13 = 13; //set the output LED
volatile boolean enableLed = false; //used to check if the interrupt has raised

//let's set up the hardware
void setup() {
    pinMode(LED13, OUTPUT); //LED pin as output
    analogComparator.setOn(AIN0, A0); //we instruct the lib to use voltages on the pins
    analogComparator.enableInterrupt(changeStatus, CHANGE); //we set the interrupt and when it has to be raised
    digitalWrite(LED13, HIGH);
}

//main loop
void loop() {
    if (enableLed) { //let's check if the analog comparator has raised the interrupt
        //yes, so we do a little blink of the LED
        digitalWrite(LED13, HIGH);
        delay(200);
        digitalWrite(LED13, LOW);
        enableLed = false;
    }
}

//interrupt to be raised by the analog comparator
void changeStatus() {
    enableLed = true; //let's inform the main loop that the condition has been reached by the analog comparator
}
