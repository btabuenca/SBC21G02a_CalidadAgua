
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
#define PERIODO 10
#define CALVTURB 0.3

#define uS_TO_S_FACTOR 1000000ULL  
 
int AN_Pot1_i = 0;
int AN_Pot1_Filtered = 0;

const int pinDatosDQ= 33;
int status = WL_IDLE_STATUS;
float TempI=0.0;
float TempE=0.0;
float difTemp=0.0;
float calTurb=0.0;
float turbidez=0.0;
bool sent=false;


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
  sent=false;
  delay(1000);
  wakeup();
  initConection();
  Serial.println("Mandando comandos a los sensores");
  getTemperature();
  getTurbidez();
  sendData();
  delay(5000);
  while(!sent){}
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

void getTurbidez(){
    analogReadResolution(12);
    
    calTurb = readADC_Avg(20,PIN_TURBIDEZ);
    float vol=calTurb/1000.0;
    if(calTurb<1650-(CALVTURB*1000))turbidez=3000;
    else if(calTurb>=2780-(CALVTURB*1000))turbidez=0;   //Cambiar valor si recibimos negativos
    else turbidez= - 2572.2*((vol+CALVTURB)*(vol+CALVTURB)) + 8700.5*(vol+CALVTURB) - 4352.9 ;
    

    Serial.println("Valor Voltaje Turb Calibrado");
    Serial.println(calTurb);

    Serial.println("Valor Turbidez");
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
  tb.sendTelemetryFloat("Turbidez", turbidez);
  
  tb.loop(); //Esta instrucción ha de ser la última del método
  sent=true;
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
