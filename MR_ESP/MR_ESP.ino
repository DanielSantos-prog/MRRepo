//Projeto de monitoramento de nivel de rio
//Bibliotecas incluidas 
#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h> 
#include <WiFiClient.h> 

// definição de porta do servidor web
ESP8266WebServer server(80); 

//Entrada de Variaveis  

// Access Points com Nome/Senha
const char *ssid = "MR_ESP8266";
const char *password = "12113208";



#define LED 5
int statusLED = LOW; // variable for LED status

// -----------------------------------------------------------------------------------------------------------------Declare constants to make the page to be visited.
const String HtmlHtml = "<!DOCTYPE html> <html lang=\"pt-br\"><head ><meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Monitoramento de Nivel de Rios </title></head>\n";

const String HtmlTitle = "<body><header><h1><center>MONITORAMENTO DE NIVEL DE RIO </h1></center></header><br/><br/>\n";

const String HtmlNivelStateLow = "<div style=\"background-color:RED;text-align:left; width: 300px;\"><big>O nivel do rio está: <b>BAIXO </b></big></div>\n";
const String HtmlNivelStateHigh = "<div style=\"background-color:GREEN;text-align:left; width: 300px;\"><big>O nivel do rio está: <b>ALTO </b></big></div>\n";
const String HtmlNivelStateHigh_Low = "<div style=\"background-color:BLUE;text-align:left; width: 300px;\"><big>O nivel do rio está: <b>MEDIO </b></big></div>\n";

const String HtmlHtmlClose = "<footer ><br/><br/><br/><section style=\"text-align: left;\"><p2>Local: Palmas-TO</p2><br><p2>Rio: Tocantins  </p2><br><p2>Bomba:1  </p2></section></footer></body></html>";
// -----------------------------------------------------------------------------------------------------------------

// Function / procedure for turning on the LED
void handleLedOn() {
  statusLED = HIGH; // conditions to make the LED turn on
  digitalWrite(LED, statusLED);
  Serial.println("NodeMCU ESP8266 : LED is ON");
  response();
}

// Function / procedure for turning off the LED
void handleLedOff() {
  statusLED = LOW; // conditions to make the LED turn off
  digitalWrite(LED, statusLED);
  Serial.println("NodeMCU ESP8266 : LED is OFF");
  response();
}

// Function / procedure to handle each client making a request
void response(){
  String htmlRes = HtmlHtml + HtmlTitle;
  if(statusLED == LOW){
  }else{
  }
 
  htmlRes += HtmlNivelStateLow;
  htmlRes += HtmlHtmlClose;
 
  server.send(200, "text/html", htmlRes);
}
 
void setup() {
    delay(1000); 
    Serial.begin(115200);
    Serial.println();
 
    WiFi.softAP(ssid, password);
 
    IPAddress apip = WiFi.softAPIP(); // Get the IP server
    Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
    Serial.println(ssid);
    Serial.print("Visit this IP : ");
    Serial.print(apip); // Prints the IP address of the server to be visited
    Serial.println(" in your browser.");
    
    server.on("/", response); 
    server.on("/LEDOn", handleLedOn);
    server.on("/LEDOff", handleLedOff);
 
    server.begin(); // Start the server
    Serial.println("HTTP server beginned");
   
    pinMode(LED, OUTPUT);
    digitalWrite(LED, statusLED);
}
 
void loop() {
    server.handleClient();
    delay(1000);
    response();
    delay(1000);
    
}
