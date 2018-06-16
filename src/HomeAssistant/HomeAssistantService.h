#ifndef HomeAssistantService_h
#define HomeAssistantService_h

#define LIGHT_TURN_ON 0
#define LIGHT_TURN_OFF 1
#define LIGHT_TOGGLE 2

#define SWITCH_TURN_ON 3
#define SWITCH_TURN_OFF 4
#define SWITCH_TOGGLE 5

#define SCRIPT_TURN_ON 6
#define SCRIPT_TURN_OFF 7
#define SCRIPT_TOGGLE 8

#define INPUT_BOOL_TURN_ON 9
#define INPUT_BOOL_TURN_OFF 10
#define INPUT_BOOL_TOGGLE 11

#define REMOTE_SEND_COMMAND 12
#define REMOTE_TOGGLE 13
#define REMOTE_TURN_ON 14
#define REMOTE_TURN_OFF 15

#define MEDIA_CLEAR_PLAYLIST 16
#define MEDIA_NEXT_TRACK 17
#define MEDIA_PAUSE 18
#define MEDIA_PLAY 19
#define MEDIA_PLAY_PAUSE 20
#define MEDIA_PREVIOUS_TRACK 21
#define MEDIA_STOP 22
#define MEDIA_SEEK 23

#define TTS_GOOGLE_SAY 24

#include "Arduino.h"

class HomeAssistantService {
  public:
    HomeAssistantService(uint8_t service);
    String endpoint;
};

#endif
