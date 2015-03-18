#include "RTLHelper.h"

static const char FirstHebChar = (char)1488; //א
static const char LastHebChar = (char)1514; //ת
  
bool TextStartsWithRTL(const char* text) {
  return text[0] >= FirstHebChar && text[0] <= LastHebChar;
}

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

void TextLayerSetTextRTLAware(TextLayer* layer, const char* text) {
  if (TextStartsWithRTL(text)) {
    char* newText = malloc(strlen(text)+1);
    strncpy(newText,text,strlen(text));
    text_layer_set_text(layer, utf8rev(newText));
    text_layer_set_text_alignment(layer, GTextAlignmentRight);
    //free(newText);
  } else {
    text_layer_set_text(layer, text);
    text_layer_set_text_alignment(layer, GTextAlignmentLeft);
  }
}