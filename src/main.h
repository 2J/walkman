TextLayer *text_layer;

Window *main_window;

unsigned long long points;
char *points_text;

#define shop_max 3
#define shop_font_height 20

Window *shop_main;

TextLayer *shop_title;
TextLayer *shop_points;
unsigned int shop_selection;
char current_window = 0; //0: MAIN, 1: SHOP

struct shop_item{
  int id; //id of item
  char* name;
  unsigned long long price; //initial price
  char increment; //increment multiplier. will be multiplied by 1+increment per item bought
  TextLayer *text_layer;
};