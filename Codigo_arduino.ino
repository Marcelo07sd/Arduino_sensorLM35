#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Sensor = A0;
int PinRojo = 6;
int PinVerde = 7;
int PinAmarillo = 8;
int PinSpeaker = 9;

float Temperatura = 0;
float umbralMin = 20.0;
float umbralMax = 30.0;

unsigned long ultimoEnvio = 0;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);

  pinMode(PinVerde, OUTPUT);
  pinMode(PinRojo, OUTPUT);
  pinMode(PinAmarillo, OUTPUT);
  pinMode(PinSpeaker, OUTPUT);

  digitalWrite(PinAmarillo, LOW);
  digitalWrite(PinRojo, LOW);
  digitalWrite(PinVerde, LOW);

  lcd.print("Sensor LM35");
  lcd.setCursor(0, 1);
  lcd.print("Listo");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');

    if (comando.startsWith("SETMIN:")) {
      umbralMin = comando.substring(7).toFloat();
      Serial.println("Umbral Min Actualizado");
    } else if (comando.startsWith("SETMAX:")) {
      umbralMax = comando.substring(7).toFloat();
      Serial.println("Umbral Max Actualizado");
    }
  }

  int ValorSensor = analogRead(Sensor);
  float voltaje = ValorSensor * (5.0 / 1023.0);
  Temperatura = voltaje * 100.0;

  lcd.setCursor(0, 0);
  lcd.print(Temperatura, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  if (Temperatura < umbralMin) {
    lcd.setCursor(0, 1);
    lcd.print("Temperatura Baja ");
    digitalWrite(PinAmarillo, HIGH);
    digitalWrite(PinVerde, LOW);
    digitalWrite(PinRojo, LOW);
    playTone(600, 500); delay(100); playTone(600, 900); delay(100);
  } else if (Temperatura > umbralMax) {
    lcd.setCursor(0, 1);
    lcd.print("Temperatura Alta ");
    digitalWrite(PinAmarillo, LOW);
    digitalWrite(PinVerde, LOW);
    digitalWrite(PinRojo, HIGH);
    playTone(500, 600); delay(100); playTone(500, 800); delay(100);
  } else {
    lcd.setCursor(0, 1);
    lcd.print("Temperatura Normal");
    digitalWrite(PinAmarillo, LOW);
    digitalWrite(PinVerde, HIGH);
    digitalWrite(PinRojo, LOW);
    playTone(0, 0); delay(100);
  }

  if (millis() - ultimoEnvio > 1000) {  // Cada 1 segundo envía datos
    Serial.print("TEMP:");
    Serial.println(Temperatura);
    Serial.print("UMBRALMIN:");
    Serial.println(umbralMin);
    Serial.print("UMBRALMAX:");
    Serial.println(umbralMax);
    ultimoEnvio = millis();
  }
}

void playTone(long duracion, int frecuencia) {
  duracion *= 1000;
  int periodo = (frecuencia > 0) ? (1000000 / frecuencia) : 0;
  long lapso = 0;

  if (frecuencia == 0) {
    digitalWrite(PinSpeaker, LOW);
    return;
  }

  while (lapso < duracion) {
    digitalWrite(PinSpeaker, HIGH);
    delayMicroseconds(periodo / 2);
    digitalWrite(PinSpeaker, LOW);
    delayMicroseconds(periodo / 2);
    lapso += periodo;
  }
}
