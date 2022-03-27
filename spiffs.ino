#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

WebServer server(80);

void top(){
  File file = SPIFFS.open("/password.html", "r");
  server.streamFile(file,"text/html");
  file.close();
}

void toggle() {
  static bool out = 0;
  out = !out;
  digitalWrite(2,out);
}


void setup(){

  Serial.begin(115200);
  
  pinMode(2, OUTPUT);
  SPIFFS.begin();
  WiFi.softAP("もんもん");
  server.on("/",top);
  server.on("/toggle",toggle);
  server.begin();
}

void loop(){
  server.handleClient();
}
