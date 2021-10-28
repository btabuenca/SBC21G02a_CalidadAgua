#include <OneWire.h>
#include <DallasTemperature.h>
 
// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 33;

//Variables globales. Datos obtenidos
float tempExt=99;
float tempInt=99;
float difTemp=0;

 
// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void getTemp(){
  tempExt=sensorDS18B20.getTempCByIndex(0);
  tempInt=sensorDS18B20.getTempCByIndex(1);
  difTemp=tempExt-tempInt;
  Serial.println("Informe de temperatura");
  Serial.print("Temperatura sensor Exterior: ");
  Serial.print(tempExt);
  Serial.println(" C");
  Serial.print("Temperatura sensor Interior: ");
  Serial.print(tempInt);
  Serial.println(" C");
   Serial.print("Diferencia de temperatura");
  Serial.print(difTemp);
  Serial.println(" C");
  
  
  }
 
void setup() {
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin();

}
 
void loop() {
    // Mandamos comandos para toma de temperatura a los sensores
    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
   getTemp();
    
    delay(1000); 
}
