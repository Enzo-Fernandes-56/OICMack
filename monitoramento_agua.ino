#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Credenciais Wi-Fi
const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";

// Broker MQTT
const char* mqtt_server = "broker.hivemq.com"; 

WiFiClient espClient;
PubSubClient client(espClient);

// Sensor e atuador
const int PINO_SENSOR = D2;
const int PINO_LED = D1;
volatile unsigned long contador = 0;

const float FATOR_CALIBRACAO = 4.5;
unsigned long tempo_antes = 0;
float fluxo = 0;
float volume_total = 0;

void contador_pulso() {
  contador++;
}

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    client.connect("ESP8266Client");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(PINO_SENSOR, INPUT_PULLUP);
  pinMode(PINO_LED, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(PINO_SENSOR), contador_pulso, FALLING);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  tempo_antes = millis();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (millis() - tempo_antes > 1000) {
    detachInterrupt(digitalPinToInterrupt(PINO_SENSOR));

    fluxo = ((1000.0 / (millis() - tempo_antes)) * contador) / FATOR_CALIBRACAO;
    float volume = fluxo / 60.0;
    volume_total += volume;

    // Atuador: liga LED se fluxo > 1.0 L/min
    if (fluxo > 1.0) {
      digitalWrite(PINO_LED, HIGH);
    } else {
      digitalWrite(PINO_LED, LOW);
    }

    // Envio MQTT
    char fluxoMsg[32];
    dtostrf(fluxo, 6, 2, fluxoMsg);
    client.publish("agua/fluxo", fluxoMsg);

    char volumeMsg[32];
    dtostrf(volume_total, 6, 2, volumeMsg);
    client.publish("agua/volume", volumeMsg);

    Serial.print("Fluxo: "); Serial.print(fluxo); Serial.println(" L/min");
    Serial.print("Volume Total: "); Serial.println(volume_total);

    contador = 0;
    tempo_antes = millis();
    attachInterrupt(digitalPinToInterrupt(PINO_SENSOR), contador_pulso, FALLING);
  }
}
