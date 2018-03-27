
#include "UbidotsMicroESP8266.h"

#define ID1  "XXXXXX"  // blinky
#define ID2  "XXXXX"//tempo
#define ID3  "XXXXXX"//Repetição
#define ID4  "XXXXXX"//menos
#define ID5  "XXXXXX"//mais
#define TOKEN "XXXXX"  // Put here your Ubidots TOKEN
#define WIFISSID "XXXX"//ssid
#define PASSWORD "XXXX"//senha


Ubidots client(TOKEN);
int aceso=0;
 int estado =0;
 int tempo=1;
 int repetir=0;
 int sld=0;
 int cont=0;
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
    digitalWrite(2,aceso);
   
  delay(tempo);
   
    
 }


