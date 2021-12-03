  /*
  BIBLIOTECA DE UTILIDADES PARA EL ADC DEL ESP32
  Por Juan Arquero
  */
  
  #include "InternalADCUtilities.h"
  #include "esp_adc_cal.h"
  
  InternalADCUtilities::InternalADCUtilities(){}
  
  uint32_t InternalADCUtilities::getCalibrated(int ADC_Raw)
  {
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1000, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
  }

  float InternalADCUtilities::readADC_Avg(int samples, int port) //Cambiar para que en lugar de tomar media de ultimas 12 lecturas, haga 12 lecturas consecutivas y de media
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
