#include <pebble.h>

Window *my_window;
TextLayer *text_layer;

Window *main_window;
Window *shop_main;

unsigned long long points;
char *points_text;

TextLayer *shop_title;
unsigned int shop_selection;

struct shop_item{
  int id; //id of item
  char* name;
  unsigned long long price; //initial price
  char increment; //increment multiplier. will be multiplied by 1+increment per item bought
  TextLayer *text_layer;
};

struct shop_item items[3]= {

    {
        0,
        "Zombie",
        100,
        2,
        NULL
    },

    {
        1,
        "Child",
        200,
        2,
        NULL
    },

    {
        2,
        "Cheetah",
        300,
        2,
        NULL
    }
};

static void tick_handler(struct tm *tick_timer, TimeUnits units_changed) { //function is called every second
  snprintf(points_text, sizeof("12345678901234567890"), "POINTS: %llu", ++points);
  text_layer_set_text(text_layer, points_text);
}

//MAIN HOME
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

//SHOP
static void shop_main_load(Window *window) {
  shop_title = text_layer_create(layer_get_bounds(window_get_root_layer(shop_main)));
  layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(shop_title));
  text_layer_set_text(shop_title, "SHOP");
  shop_selection = 0;
  for(int i=0;i<3;i++){
    items[i].text_layer = text_layer_create(layer_get_bounds(window_get_root_layer(shop_main)));
    text_layer_set_text(items[i].text_layer, items[i].name);
    layer_add_child(window_get_root_layer(shop_main), text_layer_get_layer(items[i].text_layer));
  }
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
