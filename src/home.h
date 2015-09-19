static void main_window_select_click_handler(ClickRecognizerRef recognizer, void *context) {
/* SELECT PRESSED, OPEN SHOP */
  //snprintf(points_text, sizeof("12345678901234567890"), "Select %llu", points);
  //text_layer_set_text(text_layer, points_text);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "SHOP");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%s", points_text);
  
  window_stack_push(shop_main, true);//TEMP: GO TO SHOP
}

static void main_window_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "%llu", points);
}

static void main_window_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //text_layer_set_text(text_layer, "Down");
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
}

static void click_config_main_window(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, main_window_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, main_window_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, main_window_down_click_handler);
}
