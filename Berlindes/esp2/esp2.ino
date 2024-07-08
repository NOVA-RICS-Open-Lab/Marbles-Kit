#define ATUADOR_1 23
#define ATUADOR_2 22
#define ATUADOR_3 21
#define ATUADOR_4 19
#define ATUADOR_5 18
#define ATUADOR_6 5
#define ATUADOR_7 17

void setup() {
  skillG2();
}

void loop() {
}

void frontG2() {
  digitalWrite(ATUADOR_1,HIGH);
}
void backG2() {
  digitalWrite(ATUADOR_1,LOW);
}

void downG2(){
  digitalWrite(ATUADOR_2,HIGH);
}
void upG2(){
  digitalWrite(ATUADOR_2,LOW);
}

void stopInTheMiddle(bool toggle){
  digitalWrite(ATUADOR_3,toggle);
}

void leftT2() {
  digitalWrite(ATUADOR_5, LOW);
  digitalWrite(ATUADOR_4, HIGH);
}
void rightT2() {
  digitalWrite(ATUADOR_4, LOW);
  digitalWrite(ATUADOR_5, HIGH);
}

void suckG2() {
  digitalWrite(ATUADOR_6, HIGH);
}
void unsuckG2() {
  digitalWrite(ATUADOR_6, LOW);
}

void skillG2() {
  downG2();
  suckG2();
  upG2();
  frontG2();
  rightT2();
  downG2();
  unsuckG2();
  leftT2();
}