#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "XXXXX"//ssid
#define wifi_password "XXXXX"//senha

#define mqtt_server "XXXXX"
#define mqtt_port XXXXX
#define mqtt_user "XXXXX"
#define mqtt_password "XXXX"

#define in_topic "351/L1"
#define out_topic "/352"
#define out_topic2"ldr/var"

#define in_led 2
float valueldr=0;
int tempo=100;
WiFiClient espClient;
PubSubClient client;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setClient(espClient);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(in_led, OUTPUT);
  digitalWrite(in_led, HIGH);
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}

void reconnect() {
  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 
 Serial.print("] ");
 for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
  Serial.print(receivedChar);
  if (receivedChar == '1')
        digitalWrite(in_led, LOW);
    if (receivedChar == '0')
        digitalWrite(in_led, HIGH);
  
 }

 Serial.println();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
    valueldr = analogRead(A0);
  client.loop();
 
  client.publish(out_topic, String(random(2)).c_str(), true);
  client.subscribe(in_topic);
 
  delayMicroseconds(1000);
  client.publish(out_topic2, String(valueldr).c_str(), true);
   delayMicroseconds(1000);
}
