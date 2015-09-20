//items initialization
//TODO: MAKE FUNCTION THAT APPENDS PRICE TO END
//TODO: MAKE FUNCTION THAT CHANGES PRICES INTO SCIENTIFIC NOTATION
struct shop_item items[3]= {
    {
        0,
        "Zombie",
        100,
        2,
        0,
        NULL
    },
    {
        1,
        "Child",
        200,
        2,
        0,
        NULL
    },
    {
        2,
        "Cheetah",
        300,
        2,
        0,
        NULL
    }
};

//select function declatation
static void shop_select(int shop_selection);

//shop window initialization
static void shop_main_load(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "INITIALIZATING SHOP");
  current_window = 1;
  GRect bounds = layer_get_bounds(window_get_root_layer(shop_main));
  
  //create texts
  shop_title = text_layer_create(layer_get_bounds(window_get_root_layer(shop_main)));
  shop_points = text_layer_create((GRect) { .origin = { 0, shop_font_height }, .size = { bounds.size.w, shop_font_height } });

  
  //text alignment
  text_layer_set_text_alignment(shop_title, GTextAlignmentCenter);
  text_layer_set_text_alignment(shop_points, GTextAlignmentRight);

  //text set string
  text_layer_set_text(shop_title, "SHOP");
  text_layer_set_text(shop_points, points_text);
  
  //add text to layer
  layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(shop_title));
  layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(shop_points));

  shop_selection = 0;
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "SHOP DEBUG %s", points_text);
  
  //initialize shop items
  for(int i=0;i<shop_max;i++){
    items[i].text_layer = text_layer_create((GRect) { .origin = { 0, shop_font_height*2+shop_font_height*i }, .size = { bounds.size.w, shop_font_height } });
    text_layer_set_text(items[i].text_layer, items[i].name);
    text_layer_set_text_alignment(items[i].text_layer, GTextAlignmentCenter);
    layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(items[i].text_layer));
  }
  
  shop_select(shop_selection);
}

//shop window destroy
static void shop_main_unload(Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "GOING OUT OF SHOP");
  current_window = 0;
  for(int i=0;i<shop_max;i++){
    text_layer_destroy(items[i].text_layer);
  }
  text_layer_destroy(shop_title);
  text_layer_destroy(shop_points);
}

//middle button pressed
static void shop_main_select_click_handler(ClickRecognizerRef recognizer, void *context) {
  //snprintf(points_text, sizeof("12345678901234567890"), "Select %llu", points);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "BUY %s", items[shop_selection].name);
  window_stack_push(shop_detail, true);//GO TO SHOP DETAILS
}

//up button pressed
static void shop_main_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(shop_selection>0) shop_select(--shop_selection);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "up SELECT %d", shop_selection);
}

//down button pressed
static void shop_main_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  if(shop_selection<shop_max-1) shop_select(++shop_selection);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "down SELECT %d", shop_selection);
}

static void click_config_shop_main(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, shop_main_select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, shop_main_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, shop_main_down_click_handler);
}

//shop selection
static void shop_select(int shop_selection){
  for(int i=0;i<shop_max;i++){
    if(shop_selection == i){
      text_layer_set_background_color(items[i].text_layer, GColorBlack);
      text_layer_set_text_color(items[i].text_layer, GColorWhite);
    }else{
      text_layer_set_background_color(items[i].text_layer, GColorWhite);
      text_layer_set_text_color(items[i].text_layer, GColorBlack);
    }
  }
}