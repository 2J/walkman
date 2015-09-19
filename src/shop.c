#include <pebble.h>
#include "shop.h"

static void shop_main_load(Window *window) {
  shop_title = text_layer_create(layer_get_bounds(window_get_root_layer(shop_main)));
  layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(shop_title));
  text_layer_set_text(shop_title, "SHOP");
}

static void shop_main_unload(Window *window) {
  text_layer_destroy(shop_title);
}


static void shop_main_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //snprintf(points_text, sizeof("12345678901234567890"), "Select %llu", points);
  text_layer_set_text(text_layer, points_text);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "SHOP");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", points_text);
}

static void shop_main_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%llu", points);
}

static void shop_main_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
}

static void click_config_shop_main(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, shop_main_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, shop_main_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, shop_main_down_click_handler);
}