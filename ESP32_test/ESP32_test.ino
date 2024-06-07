#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "ZTE_2.4G_UPGL5Y";
const char* password = "gvSbjXp4";

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

//------------------htmlcode----------------------//
String webpage = "<!DOCTYPE html><html lang='en'><head> <meta charset='UTF-8'> <meta name='viewport' content='width=device-width, initial-scale=1.0'> <title>Document</title></head><body> <h1>RANDOM NUMBER GENERATOR</h1> <h3>RANDOM NUMBER: <span id='rand'>-</span></h3></body><script> var Socket; function init() { Socket = new WebSocket('ws://' + window.location.hostname + ':81/'); Socket.onmessage = function(event) { processCommand(event); }; } function processCommand(event) { document.getElementById('rand').innerHTML = event.data; console.log(event.data); } window.onload = function(event) { init(); }</script></html>";
//------------------------------------------------//

int interval = 1000;
unsigned long previousMillis = 0;

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
  //initiate webpage
  server.on("/", []() {
    server.send(200, "text\html", webpage);
  });
  server.begin();
  webSocket.begin();
}

void loop() {
  server.handleClient();
  webSocket.loop();

  unsigned long currentTime = millis();
  if (currentTime - previousMillis > interval) {
    String str = String(random(100));
    int str_len = str.length() + 1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    webSocket.broadcastTXT(char_array);
    previousMillis = currentTime;
  }
}