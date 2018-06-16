#include "HomeAssistantService.h"

HomeAssistantService::HomeAssistantService(uint8_t service) {
  switch (service) {
    case LIGHT_TURN_ON:
      this->endpoint = "light/turn_on";
      break;
    case LIGHT_TURN_OFF:
      this->endpoint = "light/turn_off";
      break;
    case LIGHT_TOGGLE:
      this->endpoint = "light/toggle";
      break;
    case SWITCH_TURN_ON:
      this->endpoint = "switch/turn_on";
      break;
    case SWITCH_TURN_OFF:
      this->endpoint = "switch/turn_off";
      break;
    case SWITCH_TOGGLE:
      this->endpoint = "switch/toggle";
      break;
    case SCRIPT_TURN_ON:
      this->endpoint = "script/turn_on";
      break;
    case SCRIPT_TURN_OFF:
      this->endpoint = "script/turn_off";
      break;
    case SCRIPT_TOGGLE:
      this->endpoint = "script/toggle";
      break;
    case INPUT_BOOL_TURN_ON:
      this->endpoint = "input_boolean/turn_on";
      break;
    case INPUT_BOOL_TURN_OFF:
      this->endpoint = "input_boolean/turn_off";
      break;
    case INPUT_BOOL_TOGGLE:
      this->endpoint = "input_boolean/toggle";
      break;
    case REMOTE_SEND_COMMAND:
      this->endpoint = "remote/send_command";
      break;
    case REMOTE_TURN_ON:
      this->endpoint = "remote/turn_on";
      break;
    case REMOTE_TURN_OFF:
      this->endpoint = "remote/turn_off";
      break;
    case REMOTE_TOGGLE:
      this->endpoint = "remote/toggle";
      break;

    case MEDIA_CLEAR_PLAYLIST:
      this->endpoint = "media_player/clear_playlist";
      break;
    case MEDIA_NEXT_TRACK:
      this->endpoint = "media_player/media_next_track";
      break;
    case MEDIA_PAUSE:
      this->endpoint = "media_player/media_pause";
      break;
    case MEDIA_PLAY:
      this->endpoint = "media_player/media_play";
      break;
    case MEDIA_PLAY_PAUSE:
      this->endpoint = "media_player/media_play_pause";
      break;
    case MEDIA_PREVIOUS_TRACK:
      this->endpoint = "media_player/media_previous_track";
      break;
    case MEDIA_SEEK:
      this->endpoint = "media_player/media_seek";
      break;
    case MEDIA_STOP:
      this->endpoint = "media_player/media_stop";
      break;
  }
}
