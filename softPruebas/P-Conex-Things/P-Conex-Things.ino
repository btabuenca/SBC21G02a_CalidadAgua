
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingsBoard.h>
#include <WiFi.h>

// WiFi access point
#define WIFI_AP_NAME        "LaZona"
// WiFi password
#define WIFI_PASSWORD       "12345678"
#define TOKEN               "Temperatura18b20"
#define THINGSBOARD_SERVER  "thingsboard.cloud"
#define SERIAL_DEBUG_BAUD 115200
const int pinDatosDQ= 33;
float TempI=0.0;
float TempE=0.0;
float difTemp=0.0;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

WiFiClient espClient;

ThingsBoard tb(espClient);

int status = WL_IDLE_STATUS;

void setup() {
   
   Serial.begin(SERIAL_DEBUG_BAUD);
   WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
   InitWiFi();
   sensorDS18B20.begin();
}

void loop() {
   
  delay(1000);
   if (WiFi.status() != WL_CONNECTED) {
    reconnect();
    return;
   }

     if (!tb.connected()) {

    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  Serial.println("Mandando comandos a los sensores");
  sensorDS18B20.requestTemperatures();
  TempE=sensorDS18B20.getTempCByIndex(0);
  TempI=sensorDS18B20.getTempCByIndex(1);
  difTemp=TempE-TempI;
  Serial.println(TempI);
  Serial.println(TempE);
  Serial.println(difTemp);
  Serial.println("Sending data...");
  tb.sendTelemetryFloat("Temperatura Exterior", TempE);
  tb.sendTelemetryFloat("Temperatura Interior", TempI);
  tb.sendTelemetryFloat("Diferencia Temp", difTemp);

  tb.loop();
  //Serial.println("Temperatura sensor 0:");
  //t=sensorDS18B20.getTempCByIndex(0);
  //Serial.println(sensorDS18B20.getTempCByIndex(0));
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

void reconnect() {
  // Loop until we're reconnected
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Connected to AP");
  }
}
