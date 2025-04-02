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

#define SKILL0 "RESET"
#define SKILL1 "GRAB"   
#define SKILL2 "RELEASE"

#define SSID "RICS-PUB"
#define PASSWORD "ricsricsjabjab"

IPAddress local_IP(192, 168, 13, 3);  // Set your Static IP address
IPAddress gateway(192, 168, 1, 1);    // Set your Gateway IP address
IPAddress subnet(255, 255, 0, 0);

WebServer server(8009);

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
      SkillGrabG3();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 2:
      SkillReleaseG3();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
  }
}

void handleNotFound() {
  server.send(200, "text/plain", "POST REQUEST NOT FOUND");
}

//*********************************************************************************************
//
// G3
//
//*********************************************************************************************

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

//*********************************************************************************************
//
// Skills
//
//*********************************************************************************************
void Calibrate(){
  spinG3(true);
  openG3();
  upG3();
}

void SkillGrabG3() {
  spinG3(true);
  delay(DELAY_MAQUINA_2);
  openG3();
  delay(DELAY_MAQUINA_2);
  downG3();
  delay(DELAY_MAQUINA_2);
  closeG3();
  delay(DELAY_MAQUINA_2);
  upG3();
  delay(DELAY_MAQUINA_2);
}

void SkillReleaseG3(){
  spinG3(false);
  delay(DELAY_MAQUINA_2);
  openG3();
  delay(DELAY_MAQUINA_2);
  spinG3(true);
}