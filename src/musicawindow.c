#include "musicawindow.h"
#include <pebble.h>
  
static bool bIsPlayingState = false;
static bool bIsVolumeState = false;
static GBitmap *s_res_media_volumeup_icon_white;
static GBitmap *s_res_media_volumedown_icon_white;

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_media_backward_icon_white;
static GBitmap *s_res_media_play_icon_white;
static GBitmap *s_res_media_forward_icon_white;
static GFont s_res_gothic_18;
static GFont s_res_gothic_24_bold;
static ActionBarLayer *s_ActionBarLayer;
static TextLayer *s_ArtistTextLayer;
static TextLayer *s_TrackTextLayer;
static TextLayer *s_AlbumTextLayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_media_backward_icon_white = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_BACKWARD_ICON_WHITE);
  s_res_media_play_icon_white = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_PLAY_ICON_WHITE);
  s_res_media_forward_icon_white = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_FORWARD_ICON_WHITE);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  // s_ActionBarLayer
  s_ActionBarLayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_ActionBarLayer, s_window);
  action_bar_layer_set_background_color(s_ActionBarLayer, GColorBlack);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_backward_icon_white);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_SELECT, s_res_media_play_icon_white);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_forward_icon_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ActionBarLayer);
  
  // s_ArtistTextLayer
  s_ArtistTextLayer = text_layer_create(GRect(3, 0, 120, 40));
  text_layer_set_text(s_ArtistTextLayer, "Artist");
  text_layer_set_font(s_ArtistTextLayer, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ArtistTextLayer);
  
  // s_TrackTextLayer
  s_TrackTextLayer = text_layer_create(GRect(3, 52, 120, 55));
  text_layer_set_text(s_TrackTextLayer, "Track Title");
  text_layer_set_font(s_TrackTextLayer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_TrackTextLayer);
  
  // s_AlbumTextLayer
  s_AlbumTextLayer = text_layer_create(GRect(3, 110, 120, 40));
  text_layer_set_text(s_AlbumTextLayer, "Album");
  text_layer_set_font(s_AlbumTextLayer, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_AlbumTextLayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_ActionBarLayer);
  text_layer_destroy(s_ArtistTextLayer);
  text_layer_destroy(s_TrackTextLayer);
  text_layer_destroy(s_AlbumTextLayer);
  gbitmap_destroy(s_res_media_backward_icon_white);
  gbitmap_destroy(s_res_media_play_icon_white);
  gbitmap_destroy(s_res_media_forward_icon_white);
}
// END AUTO-GENERATED UI CODE

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_backward_icon_white);
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_forward_icon_white);
  } else {
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_volumeup_icon_white);
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_volumedown_icon_white);
  }
  
  bIsVolumeState = !bIsVolumeState;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsPlayingState) {
    text_layer_set_text(s_ArtistTextLayer, "No");
    text_layer_set_text(s_TrackTextLayer, "Music");
    text_layer_set_text(s_AlbumTextLayer, "Playing");
  } else {
    text_layer_set_text(s_ArtistTextLayer, "Loooooooooooooooooooooooooong Artist");
    text_layer_set_text(s_TrackTextLayer, "Looooooooooooooong Track Title");
    text_layer_set_text(s_AlbumTextLayer, "Loooooooooooooooooooooooooong Album");
  }
  
  bIsPlayingState = !bIsPlayingState;
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    text_layer_set_text(s_ArtistTextLayer, "Volume");
    text_layer_set_text(s_TrackTextLayer, "Going");
    text_layer_set_text(s_AlbumTextLayer, "Up");
  } else {
    text_layer_set_text(s_ArtistTextLayer, "Prev. Artist");
    text_layer_set_text(s_TrackTextLayer, "Prev. Track Title");
    text_layer_set_text(s_AlbumTextLayer, "Prev. Album");
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    text_layer_set_text(s_ArtistTextLayer, "Volume");
    text_layer_set_text(s_TrackTextLayer, "Going");
    text_layer_set_text(s_AlbumTextLayer, "Down");
  } else {
    text_layer_set_text(s_ArtistTextLayer, "Next Artist");
    text_layer_set_text(s_TrackTextLayer, "Next Track Title");
    text_layer_set_text(s_AlbumTextLayer, "Next Album");
  }
}

static void s_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, select_long_click_handler, NULL);
}

static void handle_window_load(Window* window) {
  s_res_media_volumeup_icon_white = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLUMEUP_ICON_WHITE);
  s_res_media_volumedown_icon_white = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLUMEDOWN_ICON_WHITE);
  
  action_bar_layer_set_click_config_provider(s_ActionBarLayer, (ClickConfigProvider)s_click_config_provider);
  text_layer_set_overflow_mode(s_AlbumTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_TrackTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_ArtistTextLayer, GTextOverflowModeFill);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_musicawindow(void) {
  initialise_ui();

  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  
  window_stack_push(s_window, true);
}

void hide_musicawindow(void) {
  window_stack_remove(s_window, true);
}