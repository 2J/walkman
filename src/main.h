TextLayer *text_layer;

Window *main_window;

unsigned long long points;
char *points_text;

#define shop_max 3

Window *shop_main;

TextLayer *shop_title;
unsigned int shop_selection;

struct shop_item{
  int id; //id of item
  char* name;
  unsigned long long price; //initial price
  char increment; //increment multiplier. will be multiplied by 1+increment per item bought
  TextLayer *text_layer;
};