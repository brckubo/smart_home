

/*
  Basic ESP8266 MQTT example
  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.
  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off
  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.
  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"
*/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "1111";
const char* password = "cgl12345.";
const char* mqtt_server = "47.97.91.15";

int SWITCH_LED = 14;
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("init_ok");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]");
  char * charr = "";
  String cmd = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    charr += (char)payload[i];
  }
  cmd = String(charr);
  Serial.println(cmd);
  DynamicJsonDocument  jsonBuffer(200);
  // Switch on the LED if an 1 was received as first character
  Serial.println(payload[0]);
  deserializeJson(jsonBuffer, cmd);
  JsonObject root = jsonBuffer.as<JsonObject>();
  if (root["cmd"] == "open") {
    digitalWrite(SWITCH_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(SWITCH_LED, LOW);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("cglbsout", "hello world");
      // ... and resubscribe
      client.subscribe("cglbsin");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

char *mystrcat(char *str1, char *str2) {
  char *outcome = str1;
  while (*str1)str1++;
  while (*str1++ = *str2++);
  return outcome;

}

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //Serial.print(Serial.read());
  if (Serial.available() > 0) {
    String comdata = "";
    while (Serial.available() > 0) {
      comdata += char(Serial.read());
      delay(2);
    }
    if (comdata.length() > 0) {
      //char c[60];
      //comdata.toCharArray(c,comdata.length());
      //strcpy(c, comdata.c_str());
      client.publish("cglbsout", comdata.c_str());
      Serial.print(comdata.c_str());
      Serial.print(comdata);
    }
  }
//    unsigned long now = millis();
//    if (now - lastMsg > 2000) {
//      lastMsg = now;
//      ++value;
//      snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
//      Serial.print("Publish message: ");
//      Serial.println(msg);
//      client.publish("cglbsout", msg);
//    }
}
