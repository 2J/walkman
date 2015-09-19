#pragma once
TextLayer *shop_title;
unsigned int shop_selection;

static void shop_main_load(Window *window);
static void shop_main_unload(Window *window);
static void shop_main_select_click_handler(ClickRecognizerRef recognizer, void *context);
static void shop_main_up_click_handler(ClickRecognizerRef recognizer, void *context);
static void shop_main_down_click_handler(ClickRecognizerRef recognizer, void *context);
static void click_config_shop_main(void *context);

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