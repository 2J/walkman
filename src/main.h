#include <pebble.h>
unsigned long long points;
char *points_text;

Window *main_window;
Window *shop_main;

static void tick_handler(struct tm *tick_timer, TimeUnits units_changed) ;
void handle_init(void) ;
void handle_deinit(void);