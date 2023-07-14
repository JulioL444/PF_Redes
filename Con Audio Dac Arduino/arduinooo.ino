#include <WiFi.h>
#include <WebServer.h>
#include "SoundData.h"

// WiFi credentials
const char* ssid = "Nexxt_2D7348";
const char* password = "ganancias5";

int a = 15, b = 2, c = 4, d = 5, e = 18, f = 19, g = 21;
int value = 0;

WebServer server(80);

void playSound(const unsigned char* soundValue, int soundSize) {
  for (int i = 0; i < soundSize; i++) {
    dacWrite(DAC1, soundValue[i]);
    delayMicroseconds(38);
  }
}

void handleRoot() {
  if (server.method() == HTTP_POST) {
    String incomingData = server.arg("plain");
    value = incomingData.toInt();
    Serial.println("Datos recibidos: " + String(value));

    // Controlar el display de 7 segmentos basado en el valor recibido
    if (value == 1) {
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, LOW);
    } else if (value == 2) {
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
    } else if (value == 3) {
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
    } else if (value == 4) {
      digitalWrite(a, LOW);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
    } else if (value == 5) {
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
    } else if (value == 0) {
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
    }

    // Reproducir el sonido utilizando DAC
    int soundSize;
    const unsigned char* soundValue = SoundData::getSoundValue(value, soundSize);

    playSound(soundValue, soundSize);

    delay(10); // Ajustar el tiempo de espera a 10 milisegundos

    server.send(200, "text/plain", "OK");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  // Conectar a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a la red WiFi");
  // Imprimir la dirección IP del Arduino
  Serial.print("URL del Arduino: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  server.on("/", handleRoot);

  server.begin();
  Serial.println("Servidor iniciado");
}

void loop() {
  server.handleClient();
}

