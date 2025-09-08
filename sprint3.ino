#include <WiFi.h>
#include <HTTPClient.h>

// Pinos dos dois sensores ultrassônicos
#define TRIG1 5   // Sensor 1 (direita)
#define ECHO1 18
#define TRIG2 19  // Sensor 2 (esquerda)
#define ECHO2 21

// LED e Buzzer
#define ALERT_LED_PIN 2
#define BUZZER_PIN 4

// Wi-Fi e ThingSpeak
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* apiKey = "VMJC6RB3I8P7UL88";
const char* server = "http://api.thingspeak.com";

// Distância limite
const int DIST_MAX = 400;

// Variável para guardar o último sensor detectado
int ultimoSensor = 0; // 0 = nenhum, 1 = direita, 2 = esquerda

void setup() {
  Serial.begin(115200);

  // Pinos dos sensores
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  // Pinos de saída
  pinMode(ALERT_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(ALERT_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" conectado!");
}

long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH);
  long distancia = (duracao / 2) * 0.0344;
  return distancia;
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Lê as distâncias dos dois sensores
    long dist1 = medirDistancia(TRIG1, ECHO1);
    long dist2 = medirDistancia(TRIG2, ECHO2);

    Serial.print("Sensor 1 (direita): ");
    Serial.print(dist1);
    Serial.print(" cm | Sensor 2 (esquerda): ");
    Serial.print(dist2);
    Serial.println(" cm");

    // Detecta bola em cada sensor
    bool bolaSensor1 = dist1 < DIST_MAX;
    bool bolaSensor2 = dist2 < DIST_MAX;

    // Atualiza o último sensor ativado
    if (bolaSensor1) ultimoSensor = 1;
    if (bolaSensor2) ultimoSensor = 2;

    // Lógica de saída da bola
    if (ultimoSensor == 2 && !bolaSensor1) {
      // Saiu pela esquerda → ativa alerta
      digitalWrite(ALERT_LED_PIN, HIGH);
      tone(BUZZER_PIN, 1000);
    } else if (ultimoSensor == 1) {
      // Voltou pela direita → desativa alerta
      digitalWrite(ALERT_LED_PIN, LOW);
      noTone(BUZZER_PIN);
    }

    // Envia dados ao ThingSpeak
    HTTPClient http;
    String url = String(server) + "/update?api_key=" + apiKey +
                 "&field1=" + String(dist1) +
                 "&field2=" + String(dist2);
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak.");
    } else {
      Serial.print("Erro ao enviar dados. Código HTTP: ");
      Serial.println(httpCode);
    }
    http.end();
  } else {
    Serial.println("WiFi não conectado. Tentando reconectar...");
  }

  delay(1000); 
}