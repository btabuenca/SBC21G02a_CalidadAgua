
#include <OneWire.h>
#include <DallasTemperature.h>

const int pinDatosDQ= 33;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   sensorDS18B20.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Mandando comandos a los sensores");
  sensorDS18B20.requestTemperatures();
  Serial.println("Temperatura sensor 0:");
  Serial.println(sensorDS18B20.getTempCByIndex(0));
  Serial.println(" C");

  delay(1000);

}
