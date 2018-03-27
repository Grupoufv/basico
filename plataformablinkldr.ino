#include "UbidotsMicroESP8266.h"

#define ID0  "XXXXXXX"  // Put here your Ubidots variable ID
#define ID1  "XXXXXXX"  // blinky
#define ID2  "XXXXXXX"//tempo
#define ID3  "XXXXXX"//Repetição
#define ID4  "XXXXXX"//menos
#define ID5  "XXXXXXX"//mais
#define ID6  "XXXXXX"//control
#define ID7  "XXXXXXX"//night
#define TOKEN  "XXXXX"  // Put here your Ubidots TOKEN
#define WIFISSID "XXXXX"//ssid
#define PASSWORD "XXXXX"//senha



Ubidots client(TOKEN);
int aceso=0;
 int estado =0;
 int tempo=1;
 int repetir=0;
 int sld=0;
 int cont=0;
 float media=0;
 float minima=2000;
 float maxima=-1;
 float soma=0;
 float itera=0;
 
void setup() {
    Serial.begin(115200);
    pinMode(2,OUTPUT);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  //ler tudo
    int blinky= client.getValue(ID1);
    
    int mais = client.getValue(ID5);
    
    int menos = client.getValue(ID4);
    
    int repetir2 = client.getValue(ID3);
    int tempo2=client.getValue(ID2);
    int night=client.getValue(ID7);
    int control=client.getValue(ID6);
   
    float value = analogRead(A0);
 
    client.add("lumens", value);
    client.add("Media",media);
    client.add("max",maxima);
    client.add("min",minima);
    
    client.sendAll(true);
    
    Serial.println("VVVVVV");
    Serial.println(value);
    switch(estado){
      case 0:
      repetir=repetir2;
      sld=tempo2;
      tempo=tempo2;
      estado=1;
      break;
      
      case 1:
      if(aceso==1){
         aceso=0;
        }else if(aceso==0){
          aceso=1;
          }

        ///
        if(sld!=tempo2&&tempo2>=0){
          tempo=tempo2;
          sld=tempo2;
          }
          
          if(repetir!=repetir2&&repetir2>=0){
            estado=3;
            cont=2*repetir2;
            repetir=repetir2;
            }
          ///
      if(mais==1){
           tempo=tempo*2;
          }
         if(menos==1){
           tempo=tempo/2;
         }
        if(blinky==0){
          aceso=0;
          estado=2;
         }
       break;
      case 2:
      if(blinky==1){
        estado=1;
      }
      tempo=1;
      aceso=1;
      break;
      
 case 3:
 cont--;
 if(cont==0){
  estado=2;
  }
   if(aceso==1){
         aceso=0;
        }else if(aceso==0){
          aceso=1;
          }
          
     break;

     
    }
    if(control==1){
      tempo=value;
      }
    //sld=tempo2;
    Serial.println("\n Valor Recebido : ");
    Serial.println("\n Repetir : ");
    
    Serial.println(repetir);
    Serial.println("\n tempo em milissegundos : ");
    Serial.println(tempo2);
     Serial.println("\n estado: ");
     
            Serial.println(blinky);
            Serial.println("\n mais : ");
            Serial.println(mais);
            Serial.println("\n menos : ");
            Serial.println(menos);
            Serial.println("\n O tempo e o estado: ");
Serial.println(tempo);
Serial.println(aceso);
    digitalWrite(2,aceso||(night==1&&value>400));
   
  delay(tempo);
   itera++;
   soma+=value;
   media=soma/itera;
  if(maxima<value){
    maxima=value;
    }  
    if(minima>value){
       minima=value;
      }
 }
  
