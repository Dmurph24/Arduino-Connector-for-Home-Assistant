#include <ESP8266HomeAssistant.h>

// Wifi credentials to connect to the network
const char* WIFI_SSID = "NetworkSSID";
const char* WIFI_PASS = "***********";

// Home Assistant server IP Address (internal or external)
const char* HA_BASE_URL = "http://<home-assistant-ip-address>";
const char* HA_PASS = "***********";

// Creates a singleton instance of the Home Assistant client
HomeAssistant ha;

// Declare the entities to be read or modified to here
const String LIGHT_ENTITY_ID = "light.<your-entity-id>";
const String MEDIA_PLAYER_ENTITY_ID = "media_player.<your-entity-id>";

void setup() {
  Serial.begin(9600);

  // Let Home Assistant connect to your wifi, then connect to the Home Assistant Server
  ha.begin(WIFI_SSID, WIFI_PASS, HA_BASE_URL, HA_PASS);

  // Check if Home Assistant is successfully connected
  if (ha.connected()) {

    Serial.println("Home Assistant Connected");

    // To check if your wifi is successfully connected
    bool wifiIsConnected = ha.wifiConnected();

    // Sending a Talk-to-speech request with a custom payload
    ha.callService(TTS_GOOGLE_SAY, ttsPayload());

    // Toggle, or turn a light on or off
    // This library also supports scripts, switches, and input booleans
    // Check the src/HomeAssistant/HomeAssistantServices.h for all supported services or view on the README.md
    ha.callEntityService(LIGHT_TURN_ON, LIGHT_ENTITY_ID);
    ha.callEntityService(LIGHT_TURN_OFF, LIGHT_ENTITY_ID);
    ha.callEntityService(LIGHT_TOGGLE, LIGHT_ENTITY_ID);

    // Play or pause a media player
    ha.callEntityService(MEDIA_PLAY, MEDIA_PLAYER_ENTITY_ID);
    ha.callEntityService(MEDIA_PAUSE, MEDIA_PLAYER_ENTITY_ID);

    // To read the state of an entity
    ha.readState(LIGHT_ENTITY_ID);

    // Sometimes you may want to access the attributes of an entity
    // This can be done by using the following:
    String jsonResponse = ha.readResponse(LIGHT_ENTITY_ID);
    int brightness = brightnessFromPayload(jsonResponse);

  } else {
    Serial.println("Not connected to Home Assistant");
  }
}

void loop() {
  // Do something real fancy in here
}

/*
 * Creates a String payload for the TTS (Text to speech) service using ArduinoJSON
 * See the ArduinoJson Library for detailed examples on how to create json objects
 * To avoid losing memory access to the json buffer, all payloads must be sent as a String object
 */
String ttsPayload() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["entity_id"] = MEDIA_PLAYER_ENTITY_ID;
  root["message"] = "The ESP8266 Chip has just became online";
  String payload;
  root.printTo(payload);
  return payload;
}

/*
 * Returns the rgb_color attribute from the entity state response
 * Parses the response using the ArduinoJson library
 * See the ArduinoJson Library for detailed examples on how to parse json objects with Strings
 */
int brightnessFromPayload(const String payload) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);
  return root["attributes"]["brightness"];
}
