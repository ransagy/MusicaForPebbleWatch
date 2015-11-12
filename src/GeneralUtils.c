#include "GeneralUtils.h"

void LogMessageWithTimestamp(AppLogLevel level, const char* message, const bool logToPhone)
{
  char buffer[100], timestamp[20];
  const time_t currTime = time(NULL);
  const struct tm *currLocalTimeStruct = localtime(&currTime);
  strftime(timestamp, 20, "%m-%d %H:%M:%S", currLocalTimeStruct);
  snprintf(buffer, 100, "%s %s", timestamp, message);
  APP_LOG(level, buffer);
  
  if (logToPhone) {
    LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, "Trying to send log data to phone..", false);
    
    DictionaryIterator *iter;
    AppMessageResult result = app_message_outbox_begin(&iter);
    
    if (iter == NULL) {
      char iterBuffer[100];
      snprintf(iterBuffer, 100, "null iterator received from app_message_outbox_begin in LogMessageWithTimestamp : %d", result);
      LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, iterBuffer, false);
      return;
    }
  
    dict_write_cstring(iter, LOG_KEY, message);
    dict_write_end(iter);
    app_message_outbox_send();
  }
}

void SendToPhone(Tuplet *data) {
  
  LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, "Preparing to send data to phone..", false);
  
  DictionaryIterator *iter;
  AppMessageResult result = app_message_outbox_begin(&iter);
  
  if (iter == NULL) {
    char buffer[100];
    snprintf(buffer, 100, "null iterator received from app_message_outbox_begin : %d", result);
    LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, buffer, false);
    return;
  }

  dict_write_tuplet(iter, data);
  dict_write_end(iter);
  app_message_outbox_send();
}

void AdjustTextLayerPosition(TextLayer* textLayer, const int topOffset, const int widthOffset)
{
  if (topOffset > 0 || widthOffset > 0) {
    GRect currFrame = layer_get_frame((Layer*)textLayer);
    GRect newFrame = GRect(currFrame.origin.x, currFrame.origin.y+topOffset, currFrame.size.w+widthOffset, currFrame.size.h);
    
    char buffer[60];
    snprintf(buffer, 60, "Old (%d,%d - %d,%d) new (%d,%d - %d,%d)", currFrame.origin.x, currFrame.origin.y, currFrame.size.w, currFrame.size.h, newFrame.origin.x, newFrame.origin.y, newFrame.size.w, newFrame.size.h);
    LogMessageWithTimestamp(APP_LOG_LEVEL_DEBUG, buffer, false);
    
    layer_set_frame((Layer*)textLayer, newFrame);
  }
}