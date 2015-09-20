//shop detail window initialization
static void shop_detail_load(Window *window) {
  struct shop_item item = items[shop_selection];
  char *temp1;
  char *temp2;
  
  temp1 = malloc(sizeof("12345678901234567890"));
  temp2 = malloc(sizeof("12345678901234567890"));

  APP_LOG(APP_LOG_LEVEL_DEBUG, "INITIALIZATING SHOP DETAILS");
  current_window = 2;
  GRect bounds = layer_get_bounds(window_get_root_layer(shop_detail));
  
  unit_name = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text(unit_name, item.name);
  text_layer_set_text_alignment(unit_name, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(shop_detail), text_layer_get_layer(unit_name));
  
  owned = text_layer_create((GRect) { .origin = { 0, 40 }, .size = { bounds.size.w, 20 } });
  snprintf(temp1, sizeof("12345678901234567890"), "Owned: %d", item.num);
  text_layer_set_text(owned, temp1);
  text_layer_set_text_alignment(owned, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(shop_detail), text_layer_get_layer(owned));
  
  price = text_layer_create((GRect) { .origin = { 72, 128 }, .size = { 71, 20 } });
  snprintf(temp2, sizeof("12345678901234567890"), "Cost: %llu", item.price);
  text_layer_set_text(price, temp2);
  text_layer_set_text_alignment(price, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(shop_detail), text_layer_get_layer(price));
  
  button = text_layer_create((GRect) { .origin = { 72, 148 }, .size = { 71, 20 } });
  text_layer_set_text(button, "BUY");
  text_layer_set_text_alignment(button, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(shop_detail), text_layer_get_layer(button));
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "SHOP DETAIL DEBUG %s", points_text);
  
  layer_add_child(window_get_root_layer(shop_detail), text_layer_get_layer(shop_points));
  
  free(temp1);
  free(temp2);
}

//shop detail window destroy
static void shop_detail_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "GOING OUT OF SHOP DETAIL");
  current_window = 1;
  text_layer_destroy(unit_name);
  text_layer_destroy(owned);
  text_layer_destroy(price);
  text_layer_destroy(button);
  layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(shop_points));
}


static void shop_buy(int shop_selection){
  struct shop_item *item = &items[shop_selection];
  if(points >= item->price){ //can buy
    points -= item->price;
    item->num++;
    APP_LOG(APP_LOG_LEVEL_DEBUG, "NUMS: %d", item->num);
    //TODO: increase item price
    
    //increase owned number on screen
    char *temp = malloc(sizeof("12345678901234567890"));
    snprintf(temp, sizeof("12345678901234567890"), "Owned: %d", item->num);
    text_layer_set_text(owned, temp);
    free(temp);
    
    //TODO: make next two lines more elegant(refreshes page instantly
    snprintf(points_text, sizeof("12345678901234567890"), "POINTS: %llu", ++points);
    text_layer_set_text(shop_points, points_text);
  }else{ //cant buy, show error message
  }
}

//middle button pressed
static void shop_detail_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //snprintf(points_text, sizeof("12345678901234567890"), "Select %llu", points);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "BUY %s", items[shop_selection].name);
  shop_buy(shop_selection);
}

//up button pressed
static void shop_detail_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up");
}

//down button pressed
static void shop_detail_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down");
}

static void click_config_shop_detail(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, shop_detail_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, shop_detail_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, shop_detail_down_click_handler);
}