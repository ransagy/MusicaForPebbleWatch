#include "GeneralUtils.h"
void LogMessageWithTimestamp(AppLogLevel level, const char* message)
{
  char buffer[100], timestamp[20];
  const time_t currTime = time(NULL);
  const struct tm *currLocalTimeStruct = localtime(&currTime);
  strftime(timestamp, 20, "%m-%d %H:%M:%S", currLocalTimeStruct);
  snprintf(buffer, 100, "%s %s", timestamp, message);
  APP_LOG(level, buffer);
}

void AdjustTextLayerPosition(TextLayer* textLayer, const int topOffset, const int widthOffset)
{
  if (topOffset > 0 || widthOffset > 0) {
    GRect currFrame = layer_get_frame((Layer*)textLayer);
    GRect newFrame = GRect(currFrame.origin.x, currFrame.origin.y+topOffset, currFrame.size.w+widthOffset, currFrame.size.h);
    
    char buffer[60];
    snprintf(buffer, 60, "Old (%d,%d - %d,%d) new (%d,%d - %d,%d)", currFrame.origin.x, currFrame.origin.y, currFrame.size.w, currFrame.size.h, newFrame.origin.x, newFrame.origin.y, newFrame.size.w, newFrame.size.h);
    LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, buffer);
    
    layer_set_frame((Layer*)textLayer, newFrame);
  }
}