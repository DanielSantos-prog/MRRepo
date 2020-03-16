#include <LiquidCrystal.h> // Incluindo biblioteca para o Display LCD
LiquidCrystal lcd(7,12,5, 4, 3, 2); // Criando Classe para os pinos ligados ao display
#include <Sim800l.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
Sim800l Sim800l;

int sensoru=0;// primeiro sensor (nível de água aumentando);
int sensord=1;// segundo sensor (nível de água perigoso);
int l=8; // led
int i; // CONTADOR


void setup() {
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(8, OUTPUT);
pinMode(6, OUTPUT);

lcd.begin(16, 2);// iniciando a classe "lcd" 
/*16= número de colunas
2=número de linhas
 */
 
}
void loop() {
  // aqui as variáveis receberão a leitura  dos pinos de INPUT
 sensoru=digitalRead(9); 
 sensord=digitalRead(10);

  if(sensoru==LOW && sensord==LOW){
    // neste if temos nossa primeira condição (nível de água seguro)
   lcd.setCursor(1, 0); // escreve na primeira linha do display
   lcd.print("NIVEL DE AGUA:");//texto a ser exibido.
   lcd.setCursor(0, 1);// escreve na segunda linha do display
   lcd.print("SEGURO");
  
    }
    
 if(sensoru==HIGH && sensord==LOW){
 /* Sengunda condição - ( nível de agua elevado)
  Onde apenas o sensoru (primeiro sensor) detectou água
  o que indica que o nível da água subiu, porém não o ponto de
  chegar às casas.
  Neste caso a intensão é deixar a população em aleta.
 */
   lcd.setCursor(1, 0);
   lcd.print("NIVEL DE AGUA:");
   lcd.setCursor(0, 1);
   lcd.print("ACIMA DO NORMAL");
 digitalWrite(8,HIGH ); // LED aceso (neste nível temos apenas alerta visual)
 digitalWrite(6,LOW ); // Buzzer desligado
}
    

if(sensoru==HIGH && sensord==HIGH){

   /* Nível crítico, quando os dois sensores detectarem 
    nível de água elevado.
 */


// botão não acionado, LED e Buzzer acionados alternadamente linhas (82-89)
 lcd.setCursor(1, 0);
 lcd.print("BUSQUE ABRIGO");
 lcd.setCursor(0, 1);
 lcd.print("REPORTANDO A DC");
 digitalWrite(8,HIGH);
 digitalWrite(6,HIGH);
 digitalWrite(8,LOW);
 delay(500);
 digitalWrite(6,LOW);
 digitalWrite(8,HIGH);
 delay(500);
 /* Os equipamentos de alerta visual e sonoro foram pulsantes por dois motivos
   1= Uma luz piscando e uma sirene pulsando chama mais atenção que em regime contínuo
   2= É uma maneira de economizar bateria, por isso são acionados de maneira alternada
   pois em um sistema de segurança é necessário que se tenha baterias que alimentem o
   dispositvo em caso falta de energia elétrica
  */
  
}

  }
