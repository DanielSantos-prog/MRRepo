

#include <Sim800l.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
Sim800l Sim800l;

int sensoru=13;// primeiro sensor (nível de água aumentando);
int i; // CONTADOR
int ln =6;
int lb=5;

char* texto = "Sensor acionado!";
char* numero = "02163992498302";

void setup() {
Serial.begin(9600);
pinMode(13,INPUT);
Sim800l.begin(); 

pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
Serial.println("Aguardando acionamento do sensor...");
}

void loop() {
  // aqui as variáveis receberão a leitura  dos pinos de INPUT
 sensoru=digitalRead(13); 
 Serial.println(sensoru);
   
  if(sensoru==LOW){
 
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    Serial.println("Nivel de agua normal...");
    }
    
 if(sensoru==HIGH){
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
   
   Serial.println("Sensor acionado! Enviando SMS...");
   Sim800l.sendSms(numero, texto);
   Serial.println("SMS Enviado...");
   
  while(sensoru==1){
    sensoru=digitalRead(13);
    Serial.println("Acionado,SMS já enviado ");
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    sensoru=digitalRead(13);
    }
}
    
  }
