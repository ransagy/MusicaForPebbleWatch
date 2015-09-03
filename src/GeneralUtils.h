#include <pebble.h>
void LogMessageWithTimestamp(AppLogLevel level, const char* message);
void AdjustTextLayerPosition(TextLayer* textLayer, const int topOffset, const int widthOffset);