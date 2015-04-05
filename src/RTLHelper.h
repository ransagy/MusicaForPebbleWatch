#include <pebble.h> 
  
bool TextStartsWithRTL(const char* text);
void TextLayerSetTextRTLAware(TextLayer* ltrLayer, TextLayer* rtlLayer, const char* text, bool forceRTL);