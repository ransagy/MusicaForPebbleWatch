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