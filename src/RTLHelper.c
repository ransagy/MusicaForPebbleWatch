#include "RTLHelper.h"

// TODO : Find out why the multibyte start for Hebrew here is 0xD7. Codepage difference?
static const int multiByte = 0xD7;
static const int firstHebChar = 0x90; //א
static const int lastHebChar = 0xAA; //ת
  
bool TextStartsWithRTL(const char* text) {
  // Only if we have any text and its at least a multi-byte char
  if (strlen(text) > 1) {
    return multiByte == text[strlen(text)-2] && (text[strlen(text)-1] >= firstHebChar && text[strlen(text)-1] <= lastHebChar);
  } else {
    return false;
  }
}

// Sad leftover from last attempt to reverse UTF8 strings in C.
char *utf8rev(char *str)
{
    /* this assumes that str is valid UTF-8 */
    char    *scanl, *scanr, *scanr2, c;

    /* first reverse the string */
    for (scanl= str, scanr= str + strlen(str); scanl < scanr;)
        c= *scanl, *scanl++= *--scanr, *scanr= c;

    /* then scan all bytes and reverse each multibyte character */
    for (scanl= scanr= str; (c= *scanr++);) {
        if ( (c & 0x80) == 0) // ASCII char
            scanl= scanr;
        else if ( (c & 0xc0) == 0xc0 ) { // start of multibyte
            scanr2= scanr;
            switch (scanr - scanl) {
                case 4: c= *scanl, *scanl++= *--scanr, *scanr= c; // fallthrough
                case 3: // fallthrough
                case 2: c= *scanl, *scanl++= *--scanr, *scanr= c;
            }
            scanr= scanl= scanr2;
        }
    }
    
    return str;
}

void TextLayerSetTextRTLAware(TextLayer* ltrLayer, TextLayer* rtlLayer, const char* text, bool forceRTL) {
  if (forceRTL || TextStartsWithRTL(text)) {
    text_layer_set_text(rtlLayer, text);
    layer_set_hidden((Layer*)rtlLayer, false);
    layer_set_hidden((Layer*)ltrLayer, true);
  } else {
    text_layer_set_text(ltrLayer, text);
    layer_set_hidden((Layer*)rtlLayer, true);
    layer_set_hidden((Layer*)ltrLayer, false);
  }
}