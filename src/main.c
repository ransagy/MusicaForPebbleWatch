#include <pebble.h>
#include <musicawindow.h>

int main(void) {
  show_musicawindow();
  app_event_loop();
  hide_musicawindow();
}