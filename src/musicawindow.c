#include "musicawindow.h"
#include "RTLHelper.h"
#include <inttypes.h>
#include <pebble.h>
  
static bool bIsPlayingState = false;
static bool bIsVolumeState = false;
static GBitmap *s_res_media_volup_icon;
static GBitmap *s_res_media_voldown_icon;

enum AppKeys {
  META_ARTIST_KEY = 0x0,       // TUPLE_CSTRING
  META_TRACK_KEY = 0x1,        // TUPLE_CSTRING
  META_ALBUM_KEY = 0x2,        // TUPLE_CSTRING
  ACTION_PLAYPAUSE_KEY = 0x3,  // TUPLE_INT32
  ACTION_INIT_KEY = 0x4,       // TUPLE_INT32
  ACTION_BACKWARD_KEY = 0x5,   // TUPLE_INT32
  ACTION_FORWARD_KEY = 0x6,    // TUPLE_INT32
  ACTION_VOLDOWN_KEY = 0x7,    // TUPLE_INT32
  ACTION_VOLUP_KEY = 0x8,      // TUPLE_INT32
  META_EXTRA_ARTIST_KEY = 0x9, // TUPLE_CSTRING
  META_EXTRA_TRACK_KEY = 0xA,  // TUPLE_CSTRING
  META_EXTRA_ALBUM_KEY = 0xB,  // TUPLE_CSTRING
};

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_media_backward_icon;
static GBitmap *s_res_media_playpause_icon;
static GBitmap *s_res_media_forward_icon;
static TextLayer *s_AlbumTextLayer;
static TextLayer *s_TrackTextLayer;
static TextLayer *s_ArtistTextLayer;
static TextLayer *s_RTL_AlbumSecondTextLayer;
static TextLayer *s_RTL_AlbumFirstTextLayer;
static TextLayer *s_RTL_TrackSecondTextLayer;
static TextLayer *s_RTL_TrackFirstTextLayer;
static TextLayer *s_RTL_ArtistSecondTextLayer;
static TextLayer *s_RTL_ArtistFirstTextLayer;
static ActionBarLayer *s_ActionBarLayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_gothic_24 = fonts_get_system_font(FONT_KEY_GOTHIC_24);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_media_backward_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_BACKWARD_ICON);
  s_res_media_playpause_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_PLAYPAUSE_ICON);
  s_res_media_forward_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_FORWARD_ICON);
  // s_AlbumTextLayer
  s_AlbumTextLayer = text_layer_create(GRect(3, 95, 115, 55));
  text_layer_set_background_color(s_AlbumTextLayer, GColorClear);
  text_layer_set_text(s_AlbumTextLayer, "Album Here");
  text_layer_set_font(s_AlbumTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_AlbumTextLayer);
  
  // s_TrackTextLayer
  s_TrackTextLayer = text_layer_create(GRect(3, 40, 115, 60));
  text_layer_set_background_color(s_TrackTextLayer, GColorClear);
  text_layer_set_text(s_TrackTextLayer, "Fetching Music..");
  text_layer_set_font(s_TrackTextLayer, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_TrackTextLayer);
  
  // s_ArtistTextLayer
  s_ArtistTextLayer = text_layer_create(GRect(3, -5, 115, 55));
  text_layer_set_background_color(s_ArtistTextLayer, GColorClear);
  text_layer_set_text(s_ArtistTextLayer, "Artist Here");
  text_layer_set_font(s_ArtistTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ArtistTextLayer);
  
  // s_RTL_AlbumSecondTextLayer
  s_RTL_AlbumSecondTextLayer = text_layer_create(GRect(3, 122, 115, 27));
  text_layer_set_background_color(s_RTL_AlbumSecondTextLayer, GColorClear);
  text_layer_set_text(s_RTL_AlbumSecondTextLayer, "אלבום שם");
  text_layer_set_text_alignment(s_RTL_AlbumSecondTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_AlbumSecondTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_AlbumSecondTextLayer);
  
  // s_RTL_AlbumFirstTextLayer
  s_RTL_AlbumFirstTextLayer = text_layer_create(GRect(3, 100, 115, 27));
  text_layer_set_background_color(s_RTL_AlbumFirstTextLayer, GColorClear);
  text_layer_set_text(s_RTL_AlbumFirstTextLayer, "אלבום פה");
  text_layer_set_text_alignment(s_RTL_AlbumFirstTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_AlbumFirstTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_AlbumFirstTextLayer);
  
  // s_RTL_TrackSecondTextLayer
  s_RTL_TrackSecondTextLayer = text_layer_create(GRect(3, 70, 115, 30));
  text_layer_set_background_color(s_RTL_TrackSecondTextLayer, GColorClear);
  text_layer_set_text(s_RTL_TrackSecondTextLayer, "למוזיקה");
  text_layer_set_text_alignment(s_RTL_TrackSecondTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_TrackSecondTextLayer, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_TrackSecondTextLayer);
  
  // s_RTL_TrackFirstTextLayer
  s_RTL_TrackFirstTextLayer = text_layer_create(GRect(3, 40, 115, 31));
  text_layer_set_background_color(s_RTL_TrackFirstTextLayer, GColorClear);
  text_layer_set_text(s_RTL_TrackFirstTextLayer, "ממתין");
  text_layer_set_text_alignment(s_RTL_TrackFirstTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_TrackFirstTextLayer, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_TrackFirstTextLayer);
  
  // s_RTL_ArtistSecondTextLayer
  s_RTL_ArtistSecondTextLayer = text_layer_create(GRect(3, 15, 115, 27));
  text_layer_set_background_color(s_RTL_ArtistSecondTextLayer, GColorClear);
  text_layer_set_text(s_RTL_ArtistSecondTextLayer, "אמן שם");
  text_layer_set_text_alignment(s_RTL_ArtistSecondTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_ArtistSecondTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_ArtistSecondTextLayer);
  
  // s_RTL_ArtistFirstTextLayer
  s_RTL_ArtistFirstTextLayer = text_layer_create(GRect(3, -5, 115, 27));
  text_layer_set_background_color(s_RTL_ArtistFirstTextLayer, GColorClear);
  text_layer_set_text(s_RTL_ArtistFirstTextLayer, "אמן פה");
  text_layer_set_text_alignment(s_RTL_ArtistFirstTextLayer, GTextAlignmentRight);
  text_layer_set_font(s_RTL_ArtistFirstTextLayer, s_res_gothic_24);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_RTL_ArtistFirstTextLayer);
  
  // s_ActionBarLayer
  s_ActionBarLayer = action_bar_layer_create();
  action_bar_layer_add_to_window(s_ActionBarLayer, s_window);
  action_bar_layer_set_background_color(s_ActionBarLayer, GColorBlack);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_UP, s_res_media_backward_icon);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_SELECT, s_res_media_playpause_icon);
  action_bar_layer_set_icon(s_ActionBarLayer, BUTTON_ID_DOWN, s_res_media_forward_icon);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_ActionBarLayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_AlbumTextLayer);
  text_layer_destroy(s_TrackTextLayer);
  text_layer_destroy(s_ArtistTextLayer);
  text_layer_destroy(s_RTL_AlbumSecondTextLayer);
  text_layer_destroy(s_RTL_AlbumFirstTextLayer);
  text_layer_destroy(s_RTL_TrackSecondTextLayer);
  text_layer_destroy(s_RTL_TrackFirstTextLayer);
  text_layer_destroy(s_RTL_ArtistSecondTextLayer);
  text_layer_destroy(s_RTL_ArtistFirstTextLayer);
  action_bar_layer_destroy(s_ActionBarLayer);
  gbitmap_destroy(s_res_media_backward_icon);
  gbitmap_destroy(s_res_media_playpause_icon);
  gbitmap_destroy(s_res_media_forward_icon);
}
// END AUTO-GENERATED UI CODE

static void sendToPhone(Tuplet *data) {
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  
  if (iter == NULL) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "null iterator received from app_message_outbox_begin!");
    return;
  }

  dict_write_tuplet(iter, data);
  dict_write_end(iter);
  app_message_outbox_send();
}

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
  Tuplet tuple = TupletInteger(ACTION_PLAYPAUSE_KEY, (bIsPlayingState ? 0 : 1));
  sendToPhone(&tuple);
  
  // Toggle playing state.
  bIsPlayingState = !bIsPlayingState;
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    // Handle volume up here.
    Tuplet tuple = TupletInteger(ACTION_VOLUP_KEY, 0);
    sendToPhone(&tuple);
  } else {
    // Handle prev track here.
    Tuplet tuple = TupletInteger(ACTION_BACKWARD_KEY, 0);
    sendToPhone(&tuple);
  }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if (bIsVolumeState) {
    // Handle volume down here.
    Tuplet tuple = TupletInteger(ACTION_VOLDOWN_KEY, 0);
    sendToPhone(&tuple);
  } else {
    // Handle next track here.
    Tuplet tuple = TupletInteger(ACTION_FORWARD_KEY, 0);
    sendToPhone(&tuple);
  }
}

static void s_click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 0, select_long_click_handler, NULL);
}

static void clearLayers() {
  text_layer_set_text(s_ArtistTextLayer, "");
  text_layer_set_overflow_mode(s_ArtistTextLayer, GTextOverflowModeFill);
  layer_set_hidden((Layer*)s_ArtistTextLayer, true);

  text_layer_set_text(s_RTL_ArtistFirstTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_ArtistFirstTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_ArtistFirstTextLayer, true);

  text_layer_set_text(s_RTL_ArtistSecondTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_ArtistSecondTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_ArtistSecondTextLayer, true);

  text_layer_set_text(s_TrackTextLayer, "");
  text_layer_set_overflow_mode(s_TrackTextLayer, GTextOverflowModeFill);
  layer_set_hidden((Layer*)s_TrackTextLayer, true);

  text_layer_set_text(s_RTL_TrackFirstTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_TrackFirstTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_TrackFirstTextLayer, true);

  text_layer_set_text(s_RTL_TrackSecondTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_TrackSecondTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_TrackSecondTextLayer, true);
  
  text_layer_set_text(s_AlbumTextLayer, "");
  text_layer_set_overflow_mode(s_AlbumTextLayer, GTextOverflowModeFill);
  layer_set_hidden((Layer*)s_AlbumTextLayer, true);

  text_layer_set_text(s_RTL_AlbumFirstTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_AlbumFirstTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_AlbumFirstTextLayer, true);

  text_layer_set_text(s_RTL_AlbumSecondTextLayer, "");
  text_layer_set_overflow_mode(s_RTL_AlbumSecondTextLayer, GTextOverflowModeWordWrap);
  layer_set_hidden((Layer*)s_RTL_AlbumSecondTextLayer, true);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Message received!");
  
  clearLayers();
  
  // Get the first pair
  Tuple *t = dict_read_first(iterator);

  // Process all pairs present
  while(t != NULL) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Got key %"PRIu32" and value %s", t->key, t->value->cstring);
    // Process this pair's key
    switch (t->key) {
      // If we got any of the META keys from the companion app, we should be in playing mode.
      case META_ARTIST_KEY:
        TextLayerSetTextRTLAware(s_ArtistTextLayer, s_RTL_ArtistFirstTextLayer, t->value->cstring, false);
        break;
      case META_TRACK_KEY:
        TextLayerSetTextRTLAware(s_TrackTextLayer, s_RTL_TrackFirstTextLayer, t->value->cstring, false);
        break;
      case META_ALBUM_KEY:
        TextLayerSetTextRTLAware(s_AlbumTextLayer, s_RTL_AlbumFirstTextLayer, t->value->cstring, false);
        break;
      case META_EXTRA_ARTIST_KEY:
        TextLayerSetTextRTLAware(s_ArtistTextLayer, s_RTL_ArtistSecondTextLayer, t->value->cstring, true);
        break;
      case META_EXTRA_TRACK_KEY :
        TextLayerSetTextRTLAware(s_TrackTextLayer, s_RTL_TrackSecondTextLayer, t->value->cstring, true);
        break;
      case META_EXTRA_ALBUM_KEY :
        TextLayerSetTextRTLAware(s_AlbumTextLayer, s_RTL_AlbumSecondTextLayer, t->value->cstring, true);
        break;
    }

    // Get next pair, if any
    t = dict_read_next(iterator);
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void initComms() {
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage comms.
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void handle_window_load(Window* window) {
  s_res_media_volup_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLUP_ICON);
  s_res_media_voldown_icon = gbitmap_create_with_resource(RESOURCE_ID_MEDIA_VOLDOWN_ICON);
  
  action_bar_layer_set_click_config_provider(s_ActionBarLayer, (ClickConfigProvider)s_click_config_provider);
  text_layer_set_overflow_mode(s_AlbumTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_TrackTextLayer, GTextOverflowModeFill);
  text_layer_set_overflow_mode(s_ArtistTextLayer, GTextOverflowModeFill);

  clearLayers();
  
  // init AppMessage API.
  initComms();
  
  // Fetch existing metadata.
  Tuplet tuple = TupletInteger(ACTION_INIT_KEY, 0);
  sendToPhone(&tuple);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
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