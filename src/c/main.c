#include <pebble.h>
#include "src/c/splash_window.h"
#include "src/c/main_window.h"
#include "src/c/error_window.h"

void launch_main_window(void *data){
  window_stack_push(main_window_get_window(), true);
}

int main(){
  splash_window_create();
  main_window_create();
  error_window_create();
  
  window_stack_push(splash_window_get_window(), true);
  
  //App Timer to have the splash window disappear
  app_timer_register(1000, launch_main_window, NULL);
  
  app_event_loop();
  splash_window_destroy();
  main_window_destroy();
  error_window_destroy();
}