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
#define SKILL1 "GRAB" //chupar ( ͡° ͜ʖ ͡°)
#define SKILL2 "RELEASE" //hawk tuah
#define SKILL3 "FEEDT1"
#define SKILL4 "FEEDG1"
#define SKILL5 "TOTAL" //fazer todo o loop

#define SSID "RICS-PUB"
#define PASSWORD "ricsricsjabjab"

IPAddress local_IP(192, 168, 250, 180);  // Set your Static IP address
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
  } else if (message == SKILL3) {
    Skill_Manager(3, message);
  } else if (message == SKILL4) {
    Skill_Manager(4, message);
  } else if (message == SKILL5) {
    Skill_Manager(5, message);
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
      SkillGrabG1();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 2:
      SkillReleaseG1();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 3:
      SkillFeedT1();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 4:
      SkillT1FeedG1();
      server.send(200, "text/plain", "Skill " + message + " done");
      break;
    case 5:
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
// T1 
//
//*********************************************************************************************

void SpinT1(bool horario) {
  if (horario) {
    digitalWrite(ATUADOR_2, LOW);
    digitalWrite(ATUADOR_1, HIGH);
  } else {
    digitalWrite(ATUADOR_1, LOW);
    digitalWrite(ATUADOR_2, HIGH);
  }
}
void StopT1() {
  digitalWrite(ATUADOR_1, LOW);
  digitalWrite(ATUADOR_2, LOW);
}

//*********************************************************************************************
//
// G1
//
//*********************************************************************************************

void OpenG1() {
  digitalWrite(ATUADOR_3, HIGH);
}
void CloseG1() {
  digitalWrite(ATUADOR_3, LOW);
}

void DownG1() {
  digitalWrite(ATUADOR_4, HIGH);
}
void UpG1() {
  digitalWrite(ATUADOR_4, LOW);
}

//*********************************************************************************************
//
// Skills
//
//*********************************************************************************************

void Calibrate() {
  SpinT1(true);
  UpG1();
  CloseG1();
}

void SkillGrabG1() {
  OpenG1();
  DownG1();
  delay(DELAY_MAQUINA_2);
  CloseG1();
  delay(DELAY_MAQUINA_1);
  UpG1();
}

void SkillReleaseG1(){
  DownG1();
  delay(DELAY_MAQUINA_2);
  OpenG1();
  delay(DELAY_MAQUINA_2);
  CloseG1();
  delay(DELAY_MAQUINA_1);
  UpG1();
}

void SkillFeedT1() {
  SpinT1(true);
  delay(DELAY_MAQUINA_2);  
}

void SkillT1FeedG1() {
  SpinT1(false);
  delay(DELAY_MAQUINA_2);
}

void SkillTotal() {
  SkillT1FeedG1();
  SkillGrabG1();
  SkillFeedT1();
  SkillReleaseG1();
}