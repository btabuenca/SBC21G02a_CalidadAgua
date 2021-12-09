#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingsBoard.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <ElegantOTA.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>


#define WIFI_AP_NAME        "LaZona"
#define WIFI_PASSWORD       "12345678"
#define TOKEN               "ESP32_BeWater"
#define THINGSBOARD_SERVER  "thingsboard.cloud.io"
#define SERIAL_DEBUG_BAUD 115200
#define PIN_TURBIDEZ 32
#define PIN_OTA 34
#define PERIODO 10
#define SEGUNDOSOTA 300 //Segundos que permanecerá el dispositivo disponible para OTA
#define CALVTURB 0
#define KHIGHEC 0.9
#define KLOWEC 1.1
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
const char* ssid = WIFI_AP_NAME;
const char* password = WIFI_PASSWORD;
int ndor = 0;
int secsOTA=SEGUNDOSOTA;
bool otaIF;


//LCD 
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


WebServer server(80);

//Sensors
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
WiFiClient espClient;
ThingsBoard tb(espClient);


//ADC
Adafruit_ADS1115 ads;



void setup() {
   Serial.begin(SERIAL_DEBUG_BAUD);
   WiFi.begin(WIFI_AP_NAME, WIFI_PASSWORD);
   InitWiFi();
   sensorDS18B20.begin();
   ads.begin();
   pinMode(PIN_OTA, INPUT);
   lcd.init();                      
   lcd.backlight();
}


void loop() {
  welcomeMsg(); 
  wakeup();
  initConection();
  if(digitalRead(PIN_OTA) == HIGH){
    ndor=212;
    }
  if(ndor==212){      //212 ciclos para ser lanzado cada hora
    Serial.println("---------------------------");
    Serial.println("OTA ACTIVADA EN");
    Serial.println(WiFi.localIP());
    Serial.println("---------------------------");
    otaIF=true;
    server.handleClient();
    InitOTA();
    ndor=0;  
  }
  else ndor++;
  Serial.println("Mandando comandos a los sensores");
  getTemperature();
  getTurbidez();
  getEC();
  getTDS();
  sendData();
  if(otaIF){
    while(secsOTA>0){
        getTemperature();
        getTurbidez();
        getEC();
        getTDS();
        sendData();
        secsOTA--;
        delay(1000);
      }
     otaIF=false;
    }
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
  Serial.print("Direccion IP: ");
  Serial.println(WiFi.localIP());
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
  volts2=ads.computeVolts(adc2)*1000.0;
  EC=readEC(volts2,TempI);
  Serial.println("Electroconductividad");
  Serial.println(EC);
  //Serial.println(" | ");
  //Serial.println(volts2);
  }

float readEC(float voltage, float temperature){
      float kValue=1.0;
      float value=0.0;
      float rawEC=(1000.0*voltage/820.0)/200.0;
      if (voltage>2.5)kValue=KHIGHEC;
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
    Serial.print("Conectando a: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Fallo en conexión a Thingsboard");
      return;
    }
    else{
       Serial.print("Conexión a Thingsboard con éxito ");
      }
  }
}

void sendData(){
  //Manda a Thingsboard los datos obtenidos
  Serial.println("Sending data...");
  tb.sendTelemetryFloat("TemperaturaExterior", TempE);
  tb.sendTelemetryFloat("TemperaturaInterior", TempI);
  tb.sendTelemetryFloat("DiferenciaTemp", difTemp);
  tb.sendTelemetryFloat("Turbidez", turbidez);
  tb.sendTelemetryFloat("TDS", tds);
  tb.sendTelemetryFloat("Electroconductividad", EC);

  
  tb.loop(); //Esta instrucción ha de ser la última del método
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

void welcomeMsg(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("beWater");
  lcd.setCursor(0, 1);
  lcd.print("quality monitor");
  delay(3000);
  lcd.clear();
  }

 void infoMsg(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp. Int: ");
  lcd.setCursor(11,0);
  lcd.print(TempI);
  lcd.setCursor(0,1);
  lcd.print("Temp. Ext: ");
  lcd.setCursor(11,1);
  lcd.print(TempE);
  
  delay(5000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TDS: ");
  lcd.setCursor(5,0);
  lcd.print(tds);
  lcd.setCursor(0,1);
  lcd.print("EC: ");
  lcd.setCursor(4,1);
  lcd.print(EC);
  
  delay(5000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Turbidez: ");
  lcd.setCursor(5,0);
  lcd.print(tds);
  lcd.setCursor(0,1);
  lcd.print("EC: ");
  lcd.setCursor(4,1);
  lcd.print(EC);

  }
