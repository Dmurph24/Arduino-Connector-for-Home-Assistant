#include <ESP8266HomeAssistant.h>

// Example PIR Sensor: https://www.adafruit.com/product/189

const char* SSID = "SSID";
const char* WIFI_PASS = "WifiPassword";

const String BASE_URL = "http://hassio.local:8123";
const String API_PASS = "APIPassword";

// See configuration.yaml to see how these are setup in Home Assistant
const String MOTION_ENTITY_ID = "input_boolean.motion_detected";
const String MOTION_THRESHOLD_ID = "sensor.motion_threshold";

// Sensor has to be inactive for X seconds (ms) before saying no motion is detected
int TIME_OFF_THRESHOLD = 1000 * 3; // Default value

// How often it updates the THRESHOLD for the motion sensor
const int THRESHOLD_REFRESH_RATE = 60000 * 15;

// Time in seconds when the THRESHOLD was last updated
int THRESHOLD_LAST_CHECKED = 0;

// Time in seconds when motion was last detected
int LAST_STATE_ON_CHANGE = -TIME_OFF_THRESHOLD;

// GPIO PIN that is connected to the PIR sensor
// This may vary
const int PIR_SENSOR = 2;

// Initial state of the motion sensor
bool PIR_STATE = false;

// True is Home Assistant is connected
bool CONNECTED = false;

HomeAssistant ha;

void setup() {
  Serial.begin(9600);

  // Setup the PinMode for the built in LED and PIR sensor
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);

  Serial.println("Connecting...");

  ha.begin(SSID, WIFI_PASS, BASE_URL, API_PASS);
  if (ha.connected()) {
    CONNECTED = true;

    // Poll the API to find the off THRESHOLD for the PIR sensor
    updateThreshold();
    Serial.print("Off threshold set to: ");
    Serial.println(TIME_OFF_THRESHOLD);
  }
}

void loop() {
  if (CONNECTED) {
    if (millis() > THRESHOLD_LAST_CHECKED + THRESHOLD_REFRESH_RATE) {
      // Update the threshold if we havent checked since the THRESHOLD_REFRESH_RATE
      updateThreshold();
    }
    loopMotionSensor();
  }
}

void updateThreshold() {
  TIME_OFF_THRESHOLD = ha.readState(MOTION_THRESHOLD_ID).toInt() * 1000;
  THRESHOLD_LAST_CHECKED = millis();
}

void loopMotionSensor() {
  // Read the value of the PIR sensor
  bool current_state = digitalRead(PIR_SENSOR);

  // Turn on/off the built in LED light based on the PIR sensor
  if (current_state) { digitalWrite(LED_BUILTIN, HIGH); }
  else { digitalWrite(LED_BUILTIN, LOW); }

  // If the sensor detects motion, update the LAST_STATE_ON_CHANGE to now
  if (current_state) {
    LAST_STATE_ON_CHANGE = millis();
  }

  if (current_state != PIR_STATE && current_state) {
    // If the state changes to ON, tell HomeAssistant and update the global state
    PIR_STATE = current_state;
    ha.callEntityService(INPUT_BOOL_TURN_ON, MOTION_ENTITY_ID);

  } else if (current_state != PIR_STATE && millis() - LAST_STATE_ON_CHANGE >= TIME_OFF_THRESHOLD) {
    // Otherwise if the state is off and we've met our threshold time for the state to be off...
    //   tell HomeAssistant and update the global state
    PIR_STATE = current_state;
    ha.callEntityService(INPUT_BOOL_TURN_OFF, MOTION_ENTITY_ID);

  } else if (current_state != PIR_STATE && random(9) == 0) {
    // Otherwise if the state changes but we havent met the threshold, print to Serial
    // (the random(9) just makes it so the Serial log isn't spammed constantly)
    Serial.print("State changed to off, but threshold of ");
    Serial.print((TIME_OFF_THRESHOLD - (millis() - LAST_STATE_ON_CHANGE)) / 1000);
    Serial.println(" seconds are remaining");
  }
}
