//#define InternalADCUtilities.h

class InternalADCUtilities
{
	public:
		InternalADCUtilities();
		uint32_t getCalibrated(int ADC_Raw);
		float readADC_Avg(int samples, int port);
}