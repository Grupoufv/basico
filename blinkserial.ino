int led=13;
int situa = 0; 
int tempo=100;
float tempo2=200;
String inputString = "";          
boolean stringCompleta = false;
char letra;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
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
  digitalWrite(led,HIGH);
  delay(tempo);
  digitalWrite(led,LOW);
}
if((letra=="I")){
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
 
    }
  }

void ResetString(){
   if(inputString!="S"){
   inputString="";
   }
}
