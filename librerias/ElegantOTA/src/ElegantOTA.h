#ifndef ElegantOTA_h
#define ElegantOTA_h

#include "Arduino.h"
#include "stdlib_noniso.h"
#include "elegantWebpage.h"

#if defined(ESP8266)
    #define HARDWARE "ESP8266"
    #include "ESP8266WiFi.h"
    #include "WiFiClient.h"
    #include "ESP8266WebServer.h"
    #include "ESP8266HTTPUpdateServer.h"
#elif defined(ESP32)
    #define HARDWARE "ESP32"
    #include "WiFi.h"
    #include "WiFiClient.h"
    #include "WebServer.h"
    #include "Update.h"
#endif


class ElegantOtaClass{
  public:
      void setID(const char* id);

      #if defined(ESP8266)      
        void begin(ESP8266WebServer *server, const char * username = "", const char * password = "");
      #elif defined(ESP32)
        void begin(WebServer *server, const char * username = "", const char * password = "");
      #endif

  private:
      #if defined(ESP8266)
          ESP8266WebServer *_server;
          ESP8266HTTPUpdateServer _httpUpdater;
      #endif
      #if defined(ESP32)
          WebServer *_server;
      #endif

      const String getID();

      char _username[64];
      char _password[64];
      bool authenticate;
      String _id = getID();
      
};

extern ElegantOtaClass ElegantOTA;
#endif
