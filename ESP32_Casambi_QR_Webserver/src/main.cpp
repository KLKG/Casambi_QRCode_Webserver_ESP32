#include <Arduino.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <FS.h>

#include <main.hpp>
#include <network.hpp>
#include <network_webserver.hpp>
#include <system_watchdog.hpp>
#include <system_status.hpp>
#include <system_logging.hpp>
#include <system_time.hpp>
#include <system_button.hpp>
#include <system_led.hpp>

String siteversion = "0.1";

Preferences setting_preferences; 

void setup()
{
  Serial.begin(115200);

  bool success = SPIFFS.begin();

  if(success){
    Serial.println("File system mounted with success");  
  }else{
      Serial.println("Error mounting the file system");  
  }

  webpage_new = (char*) ps_calloc(500000, sizeof(char));
  logging_buffer = (logging_buffer_entrys *) ps_calloc(LOGGINGnMAX, sizeof(logging_buffer_entrys));
  setting_preferences.begin("startup", false);   
  unsigned int startup_counter = setting_preferences.getUInt("start_ctr", 0);
  startup_counter++;
  system_logging_line("Startup Cycles: " + String(startup_counter, DEC));
  setting_preferences.putUInt("start_ctr", startup_counter);
  setting_preferences.end();   

  report_memory();

  watchdog_init();

  led_init();
  button_init();

  NetworkInit();
  delay(10000); //Attention after this network is ready and stable 
  timeInit(); 
  WebserverInit();


  #ifdef print_system_states
    report_free_memory();
  #endif  
}

void loop(){
  network_main_loop();

  leds_main_loop();
  button_main_loop();

  watchdog_main_loop();

  #ifdef print_system_states
  	system_status_main_loop();
  #endif

  system_time_main_loop();
}