#include <WiFi.h>

const char* ssid = "ZTE_2.4G_UPGL5Y";
const char* password = "gvSbjXp4";

WiFiServer server(80);

String header;

String outputState26 = "off";

const int output26 = 26;

void setup() {
  Serial.begin(115200);
  
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();




}

void loop() {

}