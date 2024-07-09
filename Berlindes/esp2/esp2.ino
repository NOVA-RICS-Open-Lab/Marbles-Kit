#include <WiFi.h>
#include <WebServer.h>

#define ATUADOR_1 23
#define ATUADOR_2 22
#define ATUADOR_3 21
#define ATUADOR_4 19
#define ATUADOR_5 18
#define ATUADOR_6 5
#define ATUADOR_7 17

#define DELAY_MAQUINA_1 200
#define DELAY_MAQUINA_2 2000
#define DELAY_MAQUINA_MOVE 10000

#define SKILL0 "RESET"
#define SKILL1 "GRAB"      //chupar ( ͡° ͜ʖ ͡°)
#define SKILL2 "RELEASE"   //hawk tuah
#define SKILL3 "MOVEG2G1"  //mover G2 para G1
#define SKILL4 "MOVEG2T2"  //mover G2 para T2
#define SKILL5 "MOVET2G2"  //mover T2 para G2
#define SKILL6 "MOVET2G3"  //mover T2 para G3
#define SKILL7 "TOTAL"     //fazer todo o loop

#define SSID "RICS-PUB"
#define PASSWORD "ricsricsjabjab"

IPAddress local_IP(192, 168, 2, 181);  // Set your Static IP address
IPAddress gateway(192, 168, 1, 1);    // Set your Gateway IP address
IPAddress subnet(255, 255, 0, 0);

WebServer server(8010);

void SetupPorts() {
  ///////////////////////////////////////////////
  //Inicializar os portos
  //Input
  pinMode(ATUADOR_1, OUTPUT);
  pinMode(ATUADOR_2, OUTPUT);
  pinMode(ATUADOR_3, OUTPUT);
  pinMode(ATUADOR_4, OUTPUT);
  pinMode(ATUADOR_5, OUTPUT);
  pinMode(ATUADOR_6, OUTPUT);
  pinMode(ATUADOR_7, OUTPUT);
}

void SetupWiFi() {
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Erro a configurar IP estático");
  }

  //WiFi.setSleep(WIFI_PS_NONE);

  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/berlindes/", HTTP_POST, handlePost);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void setup() {
  Serial.begin(115200);
  SetupPorts();
  Calibrate();
  SetupWiFi();
}

void loop() {
  server.handleClient();
  delay(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////// HTTP Requests /////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void handlePost() {

  String message = "";
  if (server.hasArg("skill")) {
    message = server.arg("skill");
  }

  if (message == SKILL0) {
    Skill_Manager(0, message);
  } else if (message == SKILL1) {
    Skill_Manager(1, message);
  } else if (message == SKILL2) {
    Skill_Manager(2, message);
  } else if (message == SKILL3) {
    Skill_Manager(3, message);
  } else if (message == SKILL4) {
    Skill_Manager(4, message);
  } else if (message == SKILL5) {
    Skill_Manager(5, message);
  } else if (message == SKILL6) {
    Skill_Manager(6, message);
  } else if (message == SKILL7) {
    Skill_Manager(7, message);
  } else {
    server.send(200, "text/plain", "Skill " + message + " not found");
  }
}

void Skill_Manager(int skillRequest, String message) {
  switch (skillRequest) {
    case 0:
      Calibrate();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 1:
      SkillGrabG2();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 2:
      SkillReleaseG2();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 3:
      SkillMoveG2G1();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 4:
      SkillMoveG2T2();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 5:
      SkillMoveT2G2();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 6:
      SkillMoveT2G3();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 7:
      SkillTotal();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
  }
}

void handleNotFound() {
  server.send(200, "text/plain", "POST REQUEST NOT FOUND");
}

//*********************************************************************************************
//
// G2
//
//*********************************************************************************************
void frontG2() {
  digitalWrite(ATUADOR_1, HIGH);
}
void backG2() {
  digitalWrite(ATUADOR_1, LOW);
}

void downG2() {
  digitalWrite(ATUADOR_2, HIGH);
}
void upG2() {
  digitalWrite(ATUADOR_2, LOW);
}

void stopInTheMiddle(bool toggle) {
  digitalWrite(ATUADOR_3, toggle);
}

void suckG2() {
  digitalWrite(ATUADOR_6, HIGH);
}
void unsuckG2() {
  digitalWrite(ATUADOR_6, LOW);
}

//*********************************************************************************************
//
// T2
//
//*********************************************************************************************
void leftT2() {
  digitalWrite(ATUADOR_5, LOW);
  digitalWrite(ATUADOR_4, HIGH);
}
void rightT2() {
  digitalWrite(ATUADOR_4, LOW);
  digitalWrite(ATUADOR_5, HIGH);
}

//*********************************************************************************************
//
// Skills
//
//*********************************************************************************************

void Calibrate() {
  rightT2();
  unsuckG2();
  upG2();
  backG2();
}

void SkillGrabG2() {
  downG2();
  delay(DELAY_MAQUINA_2);
  suckG2();
  delay(DELAY_MAQUINA_1);
  upG2();
}

void SkillMoveG2T2() {
  frontG2();
  delay(DELAY_MAQUINA_MOVE);  //ISTO DEVE PRECISAR DE MAIS TEMPO!!!
}

void SkillMoveG2G1() {
  backG2();
  delay(DELAY_MAQUINA_MOVE);  //ISTO DEVE PRECISAR DE MAIS TEMPO!!!
}

void SkillReleaseG2() {
  downG2();
  delay(DELAY_MAQUINA_2);
  unsuckG2();
  delay(DELAY_MAQUINA_2);
  upG2();
}

void SkillMoveT2G2() {
  leftT2();
  delay(DELAY_MAQUINA_1);
}

void SkillMoveT2G3() {
  rightT2();
  delay(DELAY_MAQUINA_1);
}

void SkillTotal() {
  SkillGrabG2();
  SkillMoveG2T2();
  SkillMoveT2G2();
  SkillReleaseG2();
  SkillMoveT2G3();
  SkillMoveG2G1();
}