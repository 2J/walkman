#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

unsigned long long points;
char *points_text;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  snprintf(points_text, sizeof("12345678901234567890"), "Select %llu", ++points);
  text_layer_set_text(text_layer, points_text);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Select");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", points_text);
  
  window_stack_push(my_window, true);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%llu", points);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Down %llu", ++points);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%llu", points);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void handle_init(void) {
  my_window = window_create();
  points_text = malloc(sizeof("12345678901234567890"));
  window_set_click_config_provider(my_window, click_config_provider);
  text_layer = text_layer_create(layer_get_bounds(window_get_root_layer(my_window)));
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));
  window_stack_push(my_window, true);
  points=0;
}

void handle_deinit(void) {
  text_layer_destroy(text_layer);
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
