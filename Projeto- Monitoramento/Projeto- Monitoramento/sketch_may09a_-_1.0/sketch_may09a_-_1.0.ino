#include <LiquidCrystal.h> // Incluindo biblioteca para o Display LCD
LiquidCrystal lcd(7,12,1, 4, 3, 2); // Criando Classe para os pinos ligados ao display
#include <Sim800l.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
Sim800l Sim800l;

int sensoru=13;// primeiro sensor (nível de água aumentando);
//int sensord=1;// segundo sensor (nível de água perigoso);
//int l=8; // led
int i; // CONTADOR
int ln =6;
int lb=5;

char* texto = "Sensor acionado!";
char* texto2 = "Nivel Alto!";
char* numero = "02163992498302";

void setup() {
Serial.begin(9600);
pinMode(13,INPUT);
//pinMode(8, OUTPUT);
//pinMode(6, OUTPUT);
Sim800l.begin(); 
lcd.begin(16, 2);// iniciando a classe "lcd"; 
/*16= número de colunas
2=número de linhas
 */

pinMode(6, OUTPUT);
pinMode(5, OUTPUT);
Serial.println("Aguardando acionamento do sensor...");
}

void loop() {
  // aqui as variáveis receberão a leitura  dos pinos de INPUT
 sensoru=digitalRead(13); 
 Serial.println(sensoru);
   
  if(sensoru==LOW){
 
   lcd.setCursor(1, 0); // escreve na primeira linha do display
   lcd.print("NIVEL DE AGUA:");//texto a ser exibido.
   lcd.setCursor(0, 1);// escreve na segunda linha do display
   lcd.print("SEGURO");
    digitalWrite(6, HIGH);
    digitalWrite(5, LOW);
    Serial.println("Nivel de agua normal...");
   
    /*Sim800l.sendSms(numero, texto2);
    Serial.println("SMS Enviado...");*/
    }
    
 if(sensoru==HIGH){
    digitalWrite(6, LOW);
    digitalWrite(5, HIGH);
   
   lcd.setCursor(1, 0);
   lcd.print("NIVEL DE AGUA:");
   lcd.setCursor(0, 1);
   lcd.print("ACIMA DO NORMAL");

   Serial.println("Sensor acionado! Enviando SMS...");
    Sim800l.sendSms(numero, texto);
    Serial.println("SMS Enviado...");
  
}
    
  }
