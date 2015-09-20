

//global
unsigned long long points;
char *points_text;
char current_window = 0; //0: MAIN, 1: SHOP, 2: SHOP DETAIL

//home
TextLayer *text_layer;
Window *main_window;

//shop
#define shop_max 3
#define shop_font_height 20
Window *shop_main;
TextLayer *shop_title;
TextLayer *shop_points;
unsigned int shop_selection;
struct shop_item{
  int id; //id of item
  char* name;
  unsigned long long price; //initial price
  char increment; //increment multiplier. will be multiplied by (1+increment) per item bought
  unsigned int num; //number of units
  TextLayer *text_layer;
};

//buy
Window *shop_detail;
TextLayer *unit_name, *owned, *price, *button;
