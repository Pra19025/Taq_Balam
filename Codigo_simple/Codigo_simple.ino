
#define Aup 9 //PB1
#define Bup 5 //PD5
#define Cup 3 //PD3
#define Adown 8 //PB0
#define Bdown 4 //PD4
#define Cdown 2 //PD2

#define DELAY 2
void setup() {
  // put your setup code here, to run once:
  pinMode(Aup,OUTPUT);
  pinMode(Bup,OUTPUT);
  pinMode(Cup,OUTPUT);
  pinMode(Adown,OUTPUT);
  pinMode(Bdown,OUTPUT);
  pinMode(Cdown,OUTPUT);

  digitalWrite(Aup,0);
  digitalWrite(Bup,0);
  digitalWrite(Cup,1);
  digitalWrite(Adown,0);
  digitalWrite(Bdown,1);
  digitalWrite(Cdown,0);

//  digitalWrite(Aup,0);
//  digitalWrite(Bup,0);
//  digitalWrite(Cup,0);
//  digitalWrite(Adown,0);
//  digitalWrite(Bdown,0);
//  digitalWrite(Cdown,0);

}

void loop() {
 // La corriente entra Por A y sale por B
 digitalWrite(Cup,0);
 digitalWrite(Aup,1);
 delay(DELAY);
 //La corriente Entre Por A y sale por C
 digitalWrite(Bdown,0);
 digitalWrite(Cdown,1);
 delay(DELAY);
 // La Corriente entra por B y Sale por C
 digitalWrite(Aup,0);
 digitalWrite(Bup,1);
 delay(DELAY);
 // La corriente entra por B y sale por A
 digitalWrite(Cdown,0);
 digitalWrite(Adown,1);
 delay(DELAY);
 //La corriente entra por C y sale por A
 digitalWrite(Cup,1);
 digitalWrite(Bup,0);
 delay(DELAY);
 // la corriente entra por C y sale por B
 digitalWrite(Adown,0);
 digitalWrite(Bdown,1);
 delay(DELAY);
}
