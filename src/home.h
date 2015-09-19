#pragma once
TextLayer *text_layer;
static void main_window_select_click_handler(ClickRecognizerRef recognizer, void *context);
static void main_window_up_click_handler(ClickRecognizerRef recognizer, void *context);
static void main_window_down_click_handler(ClickRecognizerRef recognizer, void *context);
static void click_config_main_window(void *context);