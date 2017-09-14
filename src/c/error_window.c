#include <pebble.h>
#include "error_window.h"

Window *errorWindow;
Layer *errorGraphicsLayer;
char currentErrorText[1][20];

void error_window_show(char *error){
  strncpy(currentErrorText[0], error, sizeof(currentErrorText));
  if(errorGraphicsLayer){
    layer_mark_dirty(errorGraphicsLayer);
  }
  window_stack_push(errorWindow, true);
}

//Where something is actually drawn
void error_graphics_proc(Layer *layer, GContext *ctx){
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, currentErrorText[0], fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0, 0, 144, 50), GTextOverflowModeWordWrap, GTextAlignmentCenter, NULL);

  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 3);
  graphics_draw_round_rect(ctx, GRect(5, 5, 120, 140), 5);
}

void error_window_load(Window *window){
  Layer * window_layer = window_get_root_layer(window);
  
  errorGraphicsLayer = layer_create(GRect(0, 0, 144, 168));
  layer_set_update_proc(errorGraphicsLayer, error_graphics_proc);
  layer_add_child(window_layer, errorGraphicsLayer);
  
}

void error_window_unload(Window *window){
  layer_destroy(errorGraphicsLayer);
}

void error_window_create(){
  errorWindow = window_create();
  window_set_window_handlers(errorWindow, (WindowHandlers){
    .load = error_window_load,
    .unload = error_window_unload
  });
}

void error_window_destroy(){
  window_destroy(errorWindow);
}

Window *error_window_get_window(){
  return errorWindow;
}
