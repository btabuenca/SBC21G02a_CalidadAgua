#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingsBoard.h>
#include <WiFi.h>
#include "esp_adc_cal.h"
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <ElegantOTA.h>
#include <WebServer.h>

#define WIFI_AP_NAME        "LaZona"
#define WIFI_PASSWORD       "12345678"
#define TOKEN               "ESP32_BeWater_SBC"
#define THINGSBOARD_SERVER  "thingsboard.cloud.io"
#define SERIAL_DEBUG_BAUD 115200
#define PIN_TURBIDEZ 32
#define PIN_EC 35
#define PERIODO 10

#define CALVTURB 0
#define KHIGHEC 1
#define KLOWEC 1


#define uS_TO_S_FACTOR 1000000ULL  
 
int AN_Pot1_i = 0;
int AN_Pot1_Filtered = 0;

const int pinDatosDQ= 33;
int status = WL_IDLE_STATUS;
float TempI=0.0;
float TempE=0.0;
float difTemp=0.0;
float calTurb=0.0;
int turbidez=0;
float EC = 0.0;
float tds = 0.0;
float volts0, volts1, volts2, volts3;

int16_t adc0, adc1, adc2, adc3;

//OTA
const char* ssid = "LaZona";
const char* password = "12345678";
int ndor = 0;

WebServer server(80);

//Sensors
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
WiFiClient espClient;
ThingsBoard tb(espClient);

//ADC
Adafruit_ADS1115 ads;
//float Voltage = 0.0;



void setup() {
   Serial.begin(SERIAL_DEBUG_BAUD);
   WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
   InitWiFi();
   sensorDS18B20.begin();
   ads.begin();
}


void loop() {
  delay(1000); 
  wakeup();
  initConection();
  if(ndor==0){
    server.handleClient();
    InitOTA();
    ndor=10;
  }
  else ndor--;
  Serial.println("Mandando comandos a los sensores");
  getTemperature();
  getTurbidez();
  getEC();
  getTDS();
  sendData();
  delay(5000);
  sleep(PERIODO);
  
  
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

void InitOTA (){
  
   server.on("/", []() {
    server.send(200, "text/plain", "Servidor OTA de BeWater");
  });

  ElegantOTA.begin(&server);    // Start ElegantOTA
  server.begin();
  Serial.println("HTTP server started");

}

  
void getEC(){
  adc2 = ads.readADC_SingleEnded(2);
  volts2=ads.computeVolts(adc2);
  EC=readEC(volts2,TempI);
  Serial.println("Electroconductividad");
  Serial.println(EC);
  }

float readEC(float voltage, float temperature){
      float kValue=1.0;
      float value=0.0;
      float rawEC=1000*voltage/820.0/200.0;
      if (rawEC>2.5)kValue=KHIGHEC;
      else if (rawEC<2.0)kValue=KLOWEC;
      value=rawEC*kValue;
      value = value / (1.0+0.0185*(temperature-25.0));
      return value;
  }

void getTurbidez(){
    
    adc3 = ads.readADC_SingleEnded(3);
    volts3=ads.computeVolts(adc3)*1000;
    if(volts3<2500)turbidez=3000;
    else if(volts3>=4200)turbidez=0;   //Cambiar valor si recibimos negativos
    else turbidez= - 1120.4*((volts3/1000)*(volts3/1000)) + 5742.3*(volts3/1000) - 4352.9 ;
    
    Serial.println("Valor Turbidez");
    Serial.println(turbidez);

  }

void getTDS(){
    float compensationCoefficient = 1.0 + 0.02 * (TempI - 25.0);
    
    adc0 = ads.readADC_SingleEnded(0);
    volts0=ads.computeVolts(adc0);

    float compensationVolatge = volts0 / compensationCoefficient; //temperature compensation
    tds = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; 
    
    Serial.println("Valor TDS");
    Serial.println(tds);

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
  tb.sendTelemetryFloat("Turbidez", turbidez);
    tb.sendTelemetryFloat("TDS", tds);

  
  tb.loop(); //Esta instrucción ha de ser la última del método
  }

uint32_t getCalibrated(int ADC_Raw){
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1000, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
  }

  float readADC_Avg(int samples, int port) //Cambiar para que en lugar de tomar media de ultimas 12 lecturas, haga 12 lecturas consecutivas y de media
{
  int i = 0;
  float Sum = 0.0;
  float AN_Pot1_Buffer[samples] = {0.0};
  int raw=0;

  
  for(i=0; i<samples; i++)
  {
    raw=analogRead(port);
    Sum += getCalibrated(raw);
  }
  return (Sum/samples);
}

void sleep(int secs){
    esp_sleep_enable_timer_wakeup(secs *uS_TO_S_FACTOR);
    Serial.println("Going to sleep now");
    Serial.flush(); 
    esp_deep_sleep_start();
  }

void wakeup(){
   esp_sleep_wakeup_cause_t wakeup_reason;
   wakeup_reason = esp_sleep_get_wakeup_cause();
   switch(wakeup_reason)
  {
    //case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    //case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    //case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    //case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}
