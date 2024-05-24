#include <ESP8266WiFi.h>
#include <MQTT.h>
#include <SoftwareSerial.h>

const char ssid[] = "Patrick's Hotspot";
const char pass[] = "uXysm0EZC*";

unsigned long lastMillis = 0;
bool enable = true;

WiFiClientSecure net;
MQTTClient client;

SoftwareSerial STMSerial(D5, D6);

void messageReceived(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == "action")
  {
    if (payload == "on")
    {
      digitalWrite(D3, LOW);
      enable = true;
    }
    else if (payload == "off")
    {
      digitalWrite(D3, HIGH);
      enable = false;
    }
  }
  if (topic == "led")
  {
    if (payload == "on")
    {
      digitalWrite(D3, HIGH);
    }
    else if (payload == "off")
    {
      digitalWrite(D3, LOW);
    }
  }
}

void connect()
{
  Serial.print("Checking wifi connection");
  digitalWrite(D4, HIGH);
  digitalWrite(D3, HIGH);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  net.setInsecure();

  Serial.print("\n\rConnecting to Broker...");
  while (!client.connect("nodemcu", "testing", "TestingUser0"))
  {
    Serial.print(".");
    digitalWrite(D4, digitalRead(D4) ? LOW : HIGH);
    delay(1000);
  }

  Serial.println("\n\rConnected!");
  digitalWrite(D4, LOW);
  if (enable)
    digitalWrite(D3, LOW);
  client.subscribe("action");
  client.subscribe("led");
  client.onMessage(messageReceived);
}

void setup()
{
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  STMSerial.begin(9600);
  client.begin("3b7db1e2ccfd4b04a3581f1b10711506.s1.eu.hivemq.cloud", 8883, net);
  connect();
}

void loop()
{
  while (!client.connected())
  {
    Serial.print("Reconnecting...");
    connect();
  }
  if (millis() - lastMillis > 10000)
  {
    lastMillis = millis();
    client.publish("status", "online");
  }
  if (STMSerial.available())
  {
    String data = STMSerial.readStringUntil('\r');
    data.trim();
    Serial.println("Sending :" + data);
    if (data.length() > 0 && enable)
    {
      client.publish("raw", data);
    }
  }
  client.loop();
}