#include <pebble.h>

enum AppKeys {
  META_ARTIST_KEY = 0x0,       // TUPLE_CSTRING
  META_TRACK_KEY = 0x1,        // TUPLE_CSTRING
  META_ALBUM_KEY = 0x2,        // TUPLE_CSTRING
  ACTION_PLAYPAUSE_KEY = 0x3,  // TUPLE_INT32
  ACTION_INIT_KEY = 0x4,       // TUPLE_INT32
  ACTION_BACKWARD_KEY = 0x5,   // TUPLE_INT32
  ACTION_FORWARD_KEY = 0x6,    // TUPLE_INT32
  ACTION_VOLDOWN_KEY = 0x7,    // TUPLE_INT32
  ACTION_VOLUP_KEY = 0x8,      // TUPLE_INT32
  META_EXTRA_ARTIST_KEY = 0x9, // TUPLE_CSTRING
  META_EXTRA_TRACK_KEY = 0xA,  // TUPLE_CSTRING
  META_EXTRA_ALBUM_KEY = 0xB,  // TUPLE_CSTRING
  META_VOLSTATE_KEY = 0xC,     // TUPLE_INT32
  LOG_KEY = 0xD,               // TUPLE_CSTRING
};
  
void LogMessageWithTimestamp(AppLogLevel level, const char* message, const bool logToPhone);
void SendToPhone(Tuplet *data);
void AdjustTextLayerPosition(TextLayer* textLayer, const int topOffset, const int widthOffset);