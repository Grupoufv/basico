int led=13;
int situa = 0; 
int tempo=100;
float tempo2;
String inputString = "";         
unsigned long previousMillis = 0;  
boolean stringCompleta = false;
char letra;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
Leitura();

  if(inputString=="+" ){
      tempo=tempo*2;
    }
    if(inputString=="-"){
    tempo=tempo/2;
    }
  Serial.println(inputString);
  Serial.println(tempo);
  if((letra=="R")||(letra=="S")){
    if (currentMillis - previousMillis >= tempo) {
    
    previousMillis = currentMillis;
    }
  digitalWrite(led,HIGH);
  delay(tempo);
  digitalWrite(led,LOW);
}
if((letra=="I")){
  if (currentMillis - previousMillis >= tempo2) {
    
    previousMillis = currentMillis;
    }
   digitalWrite(led,HIGH);
  delay(tempo2);
  digitalWrite(led,LOW);
 
  }
  digitalWrite(led,HIGH);
  delay(tempo);
  digitalWrite(led,LOW);
  if(inputString=="S"){
   inputString="";
   tempo=100;
   }
  ResetString();
  
}
void Leitura() {
  while (Serial.available()) {
     letra = (char)Serial.read();
    inputString += letra;
    if (letra == '\n') {
      stringCompleta = true;
    }
  /*  if(letra=='I'){
       tempo2= (float)Serial.read();
      }
    if(inputString=="R"){
       tempo=(int)Serial.read();
      
      }*/
    }
  }

void ResetString(){
   if(inputString!="S"){
   inputString="";
   }
}
