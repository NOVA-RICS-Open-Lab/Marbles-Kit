#define ATUADOR_1 23
#define ATUADOR_2 22
#define ATUADOR_3 21
#define ATUADOR_4 19
#define ATUADOR_5 18
#define ATUADOR_6 5
#define ATUADOR_7 17

void setup() {
  grabG3();
  delay(1000);
  dropG3();
}

void loop() {
}

void spinG3(bool xAxis) {
  if (xAxis) {
    digitalWrite(ATUADOR_6, LOW);
    digitalWrite(ATUADOR_5, HIGH);
  } else {
    digitalWrite(ATUADOR_5, LOW);
    digitalWrite(ATUADOR_6, HIGH);
  }
}
void stopG3() {
  digitalWrite(ATUADOR_5, LOW);
  digitalWrite(ATUADOR_6, LOW);
}

void openG3() {
  digitalWrite(ATUADOR_4, LOW);
  digitalWrite(ATUADOR_3, HIGH);
}
void closeG3() {
  digitalWrite(ATUADOR_3, LOW);
  digitalWrite(ATUADOR_4, HIGH);
}

void downG3() {
  digitalWrite(ATUADOR_1, LOW);
  digitalWrite(ATUADOR_2, HIGH);
}
void upG3() {
  digitalWrite(ATUADOR_2, LOW);
  digitalWrite(ATUADOR_1, HIGH);
}

void grabG3() {
  spinG3(true);
  delay(100);
  
  openG3();
  downG3();
  closeG3();
  upG3();
  delay(100);
}

void dropG3(){
  spinG3(false);
  openG3();
}