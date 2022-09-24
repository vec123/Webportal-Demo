
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-vs-code-platformio-littlefs/  
*********/

#include <Arduino.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <functions.h>

AsyncWebServer server(80);
String currentState = "Start_up";
String currentButton = "Off";

 String processor(const String& var){
  if(var == "STATE"){
    return currentState;
  }
  if(var == "BUTTON"){
    return currentButton;
  }
  return String();
 }


const char* ssid = "Vodafonemagneticjesus";
const char* password = "Inthelandofnails:)";

void setup() {
  Serial.begin(115200);
  Serial.println("Startup");

  //---------WiFi
  WiFi_setup(ssid, password);
  Serial.print(WiFi.localIP());


  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/index.html", String(), false, processor);
  });
      // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(LittleFS, "/style.css", "text/css");
      });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {  
     String inputMessage;
     String inputParam;    
     String inputButton;            
     if (request->hasParam("input1")) {
      inputMessage = request->getParam("input1")->value();
      currentState = inputMessage;
      writeFile(LittleFS, "/inputMode.txt", inputMessage.c_str());
      inputParam = "input1";
      Serial.println(inputMessage);
                    }  

    if (request->hasParam("input2")) {
      inputButton = request->getParam("input2")->value();
      currentButton = inputButton;
      writeFile(LittleFS, "/inputButton.txt", inputButton.c_str());
      inputParam = "input2";
      Serial.println(inputButton);
      }
  });
  server.begin();
}
 
void loop() {

   // String message = readFile(LittleFS, "/inputMode.txt");
   // Serial.println(message);
   // String button = readFile(LittleFS, "/inputButton.txt");
   // Serial.println(button);
}