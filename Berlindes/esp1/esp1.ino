#define ATUADOR_1 23
#define ATUADOR_2 22
#define ATUADOR_3 21
#define ATUADOR_4 19
#define ATUADOR_5 18
#define ATUADOR_6 5
#define ATUADOR_7 17

void setup() {
  skillG1();
}

void loop() {
}

void spinT1(bool horario) {
  if (horario) {
    digitalWrite(ATUADOR_2, LOW);
    digitalWrite(ATUADOR_1, HIGH);
  } else {
    digitalWrite(ATUADOR_1, LOW);
    digitalWrite(ATUADOR_2, HIGH);
  }
}
void stopT1() {
  digitalWrite(ATUADOR_1, LOW);
  digitalWrite(ATUADOR_2, LOW);
}

void openG1() {
  digitalWrite(ATUADOR_3, HIGH);
}
void closeG1() {
  digitalWrite(ATUADOR_3, LOW);
}

void downG1() {
  digitalWrite(ATUADOR_4, HIGH);
}
void upG1() {
  digitalWrite(ATUADOR_4, LOW);
}


void skillG1() {
  spinT1(false);
  delay(100);
  
  openG1();
  downG1();
  delay(100);
  closeG1();
  upG1();
  delay(100);

  spinT1(true);
  downG1();
  openG1();
}