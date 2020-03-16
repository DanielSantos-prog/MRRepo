#include <Sim800l.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
Sim800l Sim800l;

int sensoru=13;
int sensor=9;
int i; 
int a;
int ln =6;
int lb=5;

char* texto = "ALERTA: Nivel do Rio Baixo!";
char* textom = "ALERTA: Nivel do Rio Medio!";
char* txt = "Nivel do Rio Normal.";
char* txter = "Verifique seu Sistema...Comportamento Anormal!";
char* numero = "02163992498302";

void setup() {
Serial.begin(9600);
pinMode(13,INPUT);
Sim800l.begin(); 

pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
}

void loop() {
  // aqui as variáveis receberão a leitura  dos pinos de INPUT
 sensoru=digitalRead(13); 
 sensor=digitalRead(9);
   
  if(sensor==LOW){
 
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);

    if(a==1){
   Sim800l.sendSms(numero, txt);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(6, HIGH);
    delay(100);
      }
      a=0;
    }
 if ((sensor==HIGH) && (sensoru==LOW)){ 
  a=1;
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
   Sim800l.sendSms(numero, textom);
   i=0;
    while(i==0){
      sensoru=digitalRead(13);
      sensor=digitalRead(9);
      if(sensoru==HIGH){
        i=1;
        }
      if(sensor==LOW){
        i=1;
        }
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    delay(100);
    digitalWrite(6, HIGH);
    digitalWrite(5, HIGH);
    delay(100); 
  
    } 
}
    
 if((sensoru==HIGH) && (sensor==HIGH)){
  a=1;
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
   Sim800l.sendSms(numero, texto);
   Serial.println("SMS Enviado...");
   
  while(sensoru==1){
    sensoru=digitalRead(13);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
    sensoru=digitalRead(13);
    }
}
 if((sensoru==HIGH) && (sensor==LOW)){
   Sim800l.sendSms(numero, txter);
   
  while(sensoru==1){
    sensoru=digitalRead(13);
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    delay(100);
    }
}
   
  }
