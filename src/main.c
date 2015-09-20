#include <pebble.h>

#include "main.h"
#include "home.h"
#include "shop.h"
  
static void tick_handler(struct tm *tick_timer, TimeUnits units_changed) { //function is called every second
  snprintf(points_text, sizeof("12345678901234567890"), "POINTS: %llu", ++points);
  if(current_window == 0){//IN HOME SCREEN
    APP_LOG(APP_LOG_LEVEL_DEBUG, "CURRENTLY AT HOME");
    text_layer_set_text(text_layer, points_text);
  }else if(current_window == 1){//IN SHOP
    APP_LOG(APP_LOG_LEVEL_DEBUG, "CURRENTLY AT SHOP");
    text_layer_set_text(shop_points, points_text);
  }
}

void handle_init(void) {
  points_text = malloc(sizeof("12345678901234567890"));
  
  //main window
  main_window = window_create();
  text_layer = text_layer_create(layer_get_bounds(window_get_root_layer(main_window)));
  layer_add_child(window_get_root_layer(main_window), text_layer_get_layer(text_layer));
  window_set_click_config_provider(main_window, click_config_main_window);
  
  //shop window
  shop_main = window_create();
  window_set_window_handlers(shop_main, (WindowHandlers) {
    .load = shop_main_load,
    .unload = shop_main_unload,
  });
  window_set_click_config_provider(shop_main, click_config_shop_main);
  
  
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  window_stack_push(main_window, true);
  points=0;
}

void handle_deinit(void) {
  text_layer_destroy(text_layer);
  tick_timer_service_unsubscribe();
  window_destroy(main_window);
  //window_destroy(shop_main);
  
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
