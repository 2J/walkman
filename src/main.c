#include <pebble.h>

#include "main.h"
#include "home.h"
#include "shop.h"

static void tick_handler(struct tm *tick_timer, TimeUnits units_changed) { //function is called every second
  snprintf(points_text, sizeof("12345678901234567890"), "POINTS: %llu", ++points);
  text_layer_set_text(text_layer, points_text);
}

int oldX = 1000, steps = 0, state = 1;
  
static void data_handler(AccelData *data, uint32_t num_samples) {
  // Long lived buffer
  static char s_buffer[128];
  
  int sum = 0;
  
  for(int i = 0; i < 20; i++){
    sum += data[i].x;
  }
  
  sum /= 20;
  
  if (sum > oldX && state == 0){
    state = 1;
  }
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "SUM: %d, oldX: %d", sum, oldX);
  
  if (sum < oldX && oldX > 900 && state == 1){
    steps++;
    state = 0;
    
    APP_LOG(APP_LOG_LEVEL_DEBUG, "STEPS: %d", steps);
    
    // Compose string of all data
    snprintf(s_buffer, sizeof(s_buffer), "Steps: %d", steps);
  
    //Show the data
    text_layer_set_text(text_layer, s_buffer);
  }
  
  oldX = sum;
}

//MAIN HOME


//SHOP


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
  
  window_stack_push(main_window, true);
  // tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  points=0;

  // Subscribe to the accelerometer data service
  int num_samples = 20;
  accel_data_service_subscribe(num_samples, data_handler);

  // Choose update rate
  accel_service_set_sampling_rate(ACCEL_SAMPLING_100HZ);
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
