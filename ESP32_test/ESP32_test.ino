#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ZTE_2.4G_UPGL5Y";
const char* password = "gvSbjXp4";

WebServer server(80);

String webpage = "<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Document</title></head><body> <h1>Test</h1> <h1>ESP32</h1></body></html>";

String header;

String outputState26 = "off";

const int output26 = 26;

void setup() {
  Serial.begin(115200);
  
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);
  /* ----------- WIFI CONNECTION -------------------- */
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //wifi connect with ssid & password
  WiFi.begin(ssid, password);
  //loading for wifi status if esp is connected to wifi
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  //get ip
  Serial.println(WiFi.localIP());
  /* -----------------------------------------------*/

  server.on("/", []() {
    server.send(200, "text\html", webpage);
  });
  server.begin();
}

void loop() {
  server.handleClient();
}