#ifndef HomeAssistant_h
#define HomeAssistant_h

#include "Arduino.h"
#include "ArduinoJson.h"
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

class HomeAssistant
{
  public:
    HomeAssistant();
    void begin(const char* ssid, const char* wifi_pass, const String api_base, const String api_pass = "");
    bool connected();
    bool wifiConnected();
    String readState(const String entity_id);
    String readResponse(const String entity_id);
    bool setEntityStateWithPayload(const String entity_id, const String payload);
    bool setEntityState(const String state, const String entity_id);
    bool callService(uint8_t service, String payload);
    bool callEntityService(uint8_t service, const String entity_id);
  private:
    bool healthCheck();
    String stateFromString(const String payload);
    String serviceJson(const String entity_id);
    String stateJson(const String state);
    void setupHttpClient(HTTPClient* http, String url);
    bool post(const String url, String body);
    String get(const String url);

    String _API_BASE;
    String _API_PASS;
    bool _API_NO_PASS = true;
};

#endif
