
#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingsBoard.h>
#include <WiFi.h>
#include "esp_adc_cal.h"

#define WIFI_AP_NAME        "LaZona"
#define WIFI_PASSWORD       "12345678"
#define TOKEN               "ESP32SBC"
#define THINGSBOARD_SERVER  "demo.thingsboard.io"
#define SERIAL_DEBUG_BAUD 115200
#define PIN_TURBIDEZ 32
#define FILTER_LEN  15
 
uint32_t AN_Pot1_Buffer[FILTER_LEN] = {0};
int AN_Pot1_i = 0;
int AN_Pot1_Filtered = 0;

const int pinDatosDQ= 33;
int status = WL_IDLE_STATUS;
float TempI=0.0;
float TempE=0.0;
float difTemp=0.0;
float calTurb=0.0;
float turbidez=0.0;


OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
WiFiClient espClient;
ThingsBoard tb(espClient);


void setup() {
   Serial.begin(SERIAL_DEBUG_BAUD);
   WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
   InitWiFi();
   sensorDS18B20.begin();
}


void loop() {
  initConection();
  Serial.println("Mandando comandos a los sensores");
  getTemperature();
  getTurbidez();
  sendData();
}



void InitWiFi()
{
  Serial.println("Conectando al AP ...");
  WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado al AP");
}

void reconnect() {
  status = WiFi.status();
  if ( status != WL_CONNECTED) {
    WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("Conectado al AP");
  }
}

void getTurbidez(){
    //analogSetSamples(8);
    analogReadResolution(12);
    int rawTurb = analogRead(PIN_TURBIDEZ);
    
    //Serial.println(turbidez);
    calTurb = getCalibrated(rawTurb)/1000.0;
    AN_Pot1_Filtered=readADC_Avg(calTurb);
    //float vol=(calTurb*3.3)/4095;
    turbidez= -2572.2*calTurb*calTurb + 8700.5*calTurb - 4352.9 ;
    Serial.println("Valor sin calibrar:");
    Serial.println(rawTurb);
    Serial.println("Valor Calibrado");
    Serial.println(calTurb);
    Serial.println("Valor Calibrado Multi");
    Serial.println(AN_Pot1_Filtered);
    Serial.println("Valor Sensor");
    Serial.println(turbidez);
    
  }

void getTemperature(){
  //Adquiere la temperatura de los sensores y calcula su diferencia
  sensorDS18B20.requestTemperatures();
  TempE=sensorDS18B20.getTempCByIndex(0);
  TempI=sensorDS18B20.getTempCByIndex(1);
  difTemp=TempE-TempI;
  Serial.println(TempI);
  Serial.println(TempE);
  Serial.println(difTemp);  
  }

void initConection(){
    //Conecta la placa con Thingsboard
   delay(1000);
   if (WiFi.status() != WL_CONNECTED) {
    reconnect();
    return;
   }
   if (!tb.connected()) {
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }
}

void sendData(){
  //Manda a Thingsboard los datos obtenidos
  Serial.println("Sending data...");
  tb.sendTelemetryFloat("Temperatura Exterior", TempE);
  tb.sendTelemetryFloat("Temperatura Interior", TempI);
  tb.sendTelemetryFloat("Diferencia Temp", difTemp);
  tb.sendTelemetryFloat("Turbidez", calTurb);
  
  tb.loop(); //Esta instrucción ha de ser la última del método
  }

uint32_t getCalibrated(int ADC_Raw){
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1000, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
  }

  uint32_t readADC_Avg(int ADC_Raw)
{
  int i = 0;
  uint32_t Sum = 0;
  
  AN_Pot1_Buffer[AN_Pot1_i++] = ADC_Raw;
  if(AN_Pot1_i == FILTER_LEN)
  {
    AN_Pot1_i = 0;
  }
  for(i=0; i<FILTER_LEN; i++)
  {
    Sum += AN_Pot1_Buffer[i];
  }
  return (Sum/FILTER_LEN);
}
