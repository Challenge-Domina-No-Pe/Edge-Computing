#include <WiFi.h>
#include <PubSubClient.h>

// --- CONFIGURAÇÕES WIFI ---
const char* ssid = "Wokwi-GUEST";  
const char* password = "";

// --- CONFIGURAÇÕES MQTT ---
const char* mqtt_server = "20.48.230.121";
const int mqtt_port = 1883;
const char* mqtt_user = "";  
const char* mqtt_pass = "";

// --- TÓPICOS MQTT ---
const char* topic_dist1  = "bola/dist1";
const char* topic_dist2  = "bola/dist2";
const char* topic_status = "bola/status";

// --- PINS ---
const int trigPin1 = 5;
const int echoPin1 = 18;
const int trigPin2 = 19;
const int echoPin2 = 21;

// --- VARS ---
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastPub = 0;
const unsigned long PUB_INTERVAL = 2000; // a cada 2s

long readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long dur = pulseIn(echoPin, HIGH, 30000);
  if (dur == 0) return -1;
  return (long)round(dur * 0.0343 / 2.0);
}

void setup_wifi() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: "); Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (strlen(mqtt_user) == 0) {
      if (client.connect("ESP32Bola")) Serial.println("Conectado!");
    } else {
      if (client.connect("ESP32Bola", mqtt_user, mqtt_pass)) Serial.println("Conectado com auth!");
    }
    if (!client.connected()) {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando em 5s");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastPub >= PUB_INTERVAL) {
    long distance1 = readDistanceCM(trigPin1, echoPin1);
    long distance2 = readDistanceCM(trigPin2, echoPin2);

    String statusBola = "Bola em campo";

    bool sensor1Detect = (distance1 >= 0 && distance1 < 10);
    bool sensor2Detect = (distance2 >= 0 && distance2 < 10);

    if (sensor2Detect && !sensor1Detect) statusBola = "Bola fora";
    else if (sensor1Detect && sensor2Detect) statusBola = "Bola na linha";

    client.publish(topic_dist1, String(distance1).c_str());
    client.publish(topic_dist2, String(distance2).c_str());
    client.publish(topic_status, statusBola.c_str());

    Serial.print("Dist1: "); Serial.print(distance1);
    Serial.print(" | Dist2: "); Serial.print(distance2);
    Serial.print(" | Status: "); Serial.println(statusBola);

    lastPub = now;
  }
}
