#include<ESP8266WiFi.h>


const char* ssid = "nomeWifi";
const char* password = "senha";
int controle = 0;
int ligado =0;
const char* host = "192.168.43.8";
#define sensorUmidade A0 // Sensor de umidade de solo do módulo
unsigned long tempoAnterior = 0; // Variável utilizada para guardar o tempo anterior
unsigned long intervalo = 1000;
uint8_t GPIO_Pin = D2;

void ICACHE_RAM_ATTR IntCallback(){
  digitalWrite(D5,!digitalRead(D5));
  controle =1;
  
  if(digitalRead(D5) == HIGH && ligado==0){ligado=1;}
  if(digitalRead(D5) == LOW && ligado ==1){ligado=0;}
 
}

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(D5, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(GPIO_Pin), IntCallback, RISING);
 // Serial.println();
  //Serial.print("Conectando com");
  //Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
   }
  //Serial.println("");
  //Serial.print("Wifi Conectado");
  //Serial.println("Endereço de IP:");
  //Serial.println(WiFi.localIP());
  
}

void loop() {

    //---------------------

  //----------------------
  
  //Serial.print("Conectando com ");
  //Serial.println(host);

  WiFiClient client;

  const int httpPort = 80;
  if(!client.connect(host,httpPort))
  {
    //Serial.println("Falha na conexao");
    return;
    }
  String url = "/tesla/";

  if(controle ==0){
         url += "consultlamp.php?";
         url += "id_lamp=1&id_user=11";
         url += " ";
  }else{
    if(ligado ==1){
         url += "lamp.php?";
         url += "status=ON&id=1";
         url += " ";
         controle =0;
         
    }else{
         url += "lamp.php?";
         url += "status=OFF&id=1";
         url += " ";
         controle=0;
      }
      
    
    }  
         
   Serial.print("Requisitando URL:");
   Serial.println(url);

   client.print(String("GET ") + url + "HTTP/1.1\r\n" + "Host:" + host +"\r\n"+ "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while(client.available() ==0)
  {
    if(millis() - timeout >5000)
    {
      //Serial.println(">>> Client Timeout |");
      client.stop();
      return;
      }
    
    }
   
      while(client.available())
      {
          String line = client.readStringUntil('\r');
    //      Serial.print(line);
      //    Serial.flush();
          if (line.indexOf("OFF") > 0) {
          digitalWrite(D5,LOW);
          }
          if (line.indexOf("ON") > 0) {
          digitalWrite(D5,HIGH);
          }
        }  
         
      //Serial.println();
      //Serial.println("conexao fechada");

  
}
