# Home Assistant for Arduino

![](icon.png)

## Contributors
- Daniel Murphy (Creator)
- Brandon Farmer (Examples of usage)

## Supported Architectures
If you would like to contribute, please submit a pull request that matches the styling used in the current codebase and you will be added to the list of contributors.
- All ESP8266 platforms

## Dependencies
ESP8266HomeAssistant requires ArduinoJson to create and parse objects to Home Assistant. Therefore, this library must be installed. Additionally, the ESP8266 platform. This allows the device to use WiFi and HTTPClient libraries.
1. Install the ArduinoJson library ([ArduinoJson Website](https://arduinojson.org/))
  - If you do not know how to install a library, visit this link: https://www.arduino.cc/en/guide/libraries
2. Open the Arduino IDE and go to Preferences. In `Additional Boards Manager URLs` enter the following:
  - `http://arduino.esp8266.com/stable/package_esp8266com_index.json`

## Usage
The full usage of this library is included in the `examples` folder of this project ([See example file](examples/AllFeatures.ino)). Below is a summary of the library functions:

#### Creating an instance
```
// Creates a singleton instance of the Home Assistant client
HomeAssistant ha;
```

#### Connecting WiFi and Home Assistant
```
// Connects to the wifi and Home Assistant server
ha.begin(WIFI_SSID, WIFI_PASS, HA_BASE_URL, HA_PASS);

// Check if Home Assistant is successfully connected
bool connected = ha.connected()
```

#### Reading a state from an entity
```
// Entity ID Example: light.kitchen_light
String state = ha.readState("light.kitchen_light");
if (state == "on") {
  // Do something awesome
}
```

#### Turning On/Off a light or other entity
```
// Toggle, or turn a light on or off
// This library also supports scripts, switches, and input booleans
// Check the src/HomeAssistant/HomeAssistantServices.h for all supported services or view on the README.md
ha.callEntityService(LIGHT_TURN_ON, LIGHT_ENTITY_ID);
ha.callEntityService(LIGHT_TURN_OFF, LIGHT_ENTITY_ID);
ha.callEntityService(LIGHT_TOGGLE, LIGHT_ENTITY_ID);
```
