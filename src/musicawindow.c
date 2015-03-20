#include "musicawindow.h"
#include "RTLHelper.h"
#include <inttypes.h>
#include <pebble.h>
  
static bool bIsPlayingState = false;
static bool bIsVolumeState = false;
static GBitmap *s_res_media_volup_icon;
static GBitmap *s_res_media_voldown_icon;
static char tempText[100] = "בדיקה";

static AppSync s_sync;
static uint8_t s_sync_buffer[500];

enum CurrentMetadataKey {
  META_ARTIST_KEY = 0x0,  // TUPLE_CSTRING
  META_TRACK_KEY = 0x1,   // TUPLE_CSTRING
  META_ALBUM_KEY = 0x2,   // TUPLE_CSTRING
  META_ACTION_KEY = 0x3,  // TUPLE_INT
};

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_media_backward_icon;
static GBitmap *s_res_media_playpause_icon;
static GBitmap *s_res_media_forward_icon;
static GFont s_res_gothic_24;
static GFont s_res_gothic_28_bold;
static ActionBarLayer *s_ActionBarLayer;
static TextLayer *s_ArtistTextLayer;
static TextLayer *s_TrackTextLayer;
static TextLayer *s_AlbumTextLayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_media_backward_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_BACKWARD_ICON);
  s_res_media_playpause_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_PLAYPAUSE_ICON);
  s_res_media_forward_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_FORWARD_ICON);
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_ActionBarLayer
  s_ActionBarLayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_ActionBarLayer, s_window);
  action_bar_layer_set_background_color(s_ActionBarLayer, GColorBlack);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_backward_icon);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_SELECT, s_res_media_playpause_icon);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_forward_icon);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ActionBarLayer);
  
  // s_ArtistTextLayer
  s_ArtistTextLayer = text_layer_create(GRect(3, -5, 115, 55));
  text_layer_set_background_color(s_ArtistTextLayer, GColorClear);
  text_layer_set_text(s_ArtistTextLayer, "Artist");
  text_layer_set_font(s_ArtistTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ArtistTextLayer);
  
  // s_TrackTextLayer
  s_TrackTextLayer = text_layer_create(GRect(3, 40, 115, 60));
  text_layer_set_background_color(s_TrackTextLayer, GColorClear);
  text_layer_set_text(s_TrackTextLayer, "Track Title");
  text_layer_set_font(s_TrackTextLayer, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_TrackTextLayer);
  
  // s_AlbumTextLayer
  s_AlbumTextLayer = text_layer_create(GRect(3, 95, 115, 55));
  text_layer_set_background_color(s_AlbumTextLayer, GColorClear);
  text_layer_set_text(s_AlbumTextLayer, "Album");
  text_layer_set_font(s_AlbumTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_AlbumTextLayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  action_bar_layer_destroy(s_ActionBarLayer);
  text_layer_destroy(s_ArtistTextLayer);
  text_layer_destroy(s_TrackTextLayer);
  text_layer_destroy(s_AlbumTextLayer);
  gbitmap_destroy(s_res_media_backward_icon);
  gbitmap_destroy(s_res_media_playpause_icon);
  gbitmap_destroy(s_res_media_forward_icon);
}
// END AUTO-GENERATED UI CODE

static void select_long_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_backward_icon);
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_forward_icon);
  } else {
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_volup_icon);
    action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_voldown_icon);
  }
  
  bIsVolumeState = !bIsVolumeState;
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsPlayingState) {
    // Handle pausing here.
  } else {
    // Handle playing here.
  }
  
  bIsPlayingState = !bIsPlayingState;
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    // Handle volume up here.
  } else {
    // Handle prev track here.
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    // Handle volume down here.
  } else {
    // Handle next track here.
  }
}

static void s_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, select_long_click_handler, NULL);
}

static void sync_changed_handler(const uint32_t key, const Tuple *new_tuple, const Tuple *old_tuple, void *context) {
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync callback with key : %"PRIu32"", key);
  
  // If we got this from the companion app, we should be in playing mode.
  bIsPlayingState = true;
  
  switch (key) {
    case META_ARTIST_KEY:
    TextLayerSetTextRTLAware(s_ArtistTextLayer, new_tuple->value->cstring);
    break;
    case META_TRACK_KEY:
    TextLayerSetTextRTLAware(s_TrackTextLayer, new_tuple->value->cstring);
    break;
    case META_ALBUM_KEY:
    TextLayerSetTextRTLAware(s_AlbumTextLayer, new_tuple->value->cstring);
    break;
  }
}

static void sync_error_handler(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d , Dictionary Error: %d", app_message_error, dict_error);
}

static void initComms() {
  // Open AppMessage comms.
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  // Setup initial values.
  Tuplet initial_values[] = {
    TupletCString(META_ARTIST_KEY, "No"),
    TupletCString(META_TRACK_KEY, "Musica"),
    TupletCString(META_ALBUM_KEY, "Playing"),
  };

  // Begin using AppSync.
  app_sync_init(&s_sync, s_sync_buffer, sizeof(s_sync_buffer), initial_values, ARRAY_LENGTH(initial_values), sync_changed_handler, sync_error_handler, NULL);
}

static void handle_window_load(Window* window) {
  s_res_media_volup_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLUP_ICON);
  s_res_media_voldown_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLDOWN_ICON);
  
  action_bar_layer_set_click_config_provider(s_ActionBarLayer, (ClickConfigProvider)s_click_config_provider);
  text_layer_set_overflow_mode(s_AlbumTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_TrackTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_ArtistTextLayer, GTextOverflowModeFill);
  
  // init AppSync.
  initComms();
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  
  // Finish using AppSync
  app_sync_deinit(&s_sync);
}

void show_musicawindow(void) {
  initialise_ui();
  
  // Init status bar icon. Has to be done BEFORE pushing to stack, of course :)
  window_set_status_bar_icon(s_window, gbitmap_create_with_resource(RESOURCE_ID_HEADPHONES_STATUS_ICON));

  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = handle_window_load,
    .unload = handle_window_unload,
  });
  
  window_stack_push(s_window, true);
}

void hide_musicawindow(void) {
  window_stack_remove(s_window, true);
}