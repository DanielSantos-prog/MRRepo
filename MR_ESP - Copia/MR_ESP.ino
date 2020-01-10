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
const String HtmlHtml = "<html><head>"
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlTitle = "<h1>Control LED Using NodeMCU WiFi Access Point</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>OFF</b></big><br/><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>ON</b></big><br/><br/>\n";
const String HtmlButtons = 
"<a href=\"LEDOn\"><button style=\"background-color:green;color:white;width:20%;height:5%;\">ON </button></a>\n"
"<a href=\"LEDOff\"><button style=\"background-color:red;color:white;width:20%;height:5%;\">OFF </button></a><br/>";
const String HtmlHtmlClose = "</html>";
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
    htmlRes += HtmlLedStateLow;
  }else{
    htmlRes += HtmlLedStateHigh;
  }
 
  htmlRes += HtmlButtons;
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
}
