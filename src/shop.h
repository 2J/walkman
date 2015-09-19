#pragma once
Window *shop_main;
TextLayer *shop_title;
unsigned int shop_selection;

struct shop_item(){
  int id; //id of item
  char* name;
  unsigned long long price; //initial price
  char increment; //increment multiplier. will be multiplied by 1+increment per item bought
  TextLayer *text_layer;
}

shop_item items[3];

items[0]= {
    0,
    "Zombie",
    100,
    2,
    NULL
}

items[1]= {
    1,
    "Child",
    200,
    2,
    NULL
}

items[2]= {
    2,
    "Cheetah"
    300,
    2,
    NULL
}