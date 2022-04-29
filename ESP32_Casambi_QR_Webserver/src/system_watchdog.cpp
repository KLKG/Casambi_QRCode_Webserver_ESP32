#include <Arduino.h>
#include <esp_task_wdt.h>

#include <main.hpp>
#include <system_watchdog.hpp>
#include <system_logging.hpp>

//3 seconds WDT
#define WDT_TIMEOUT 60

unsigned long runtime_ms_watchdog = 0;

void watchdog_init(){
  system_logging_line("Configuring WDT...");
  esp_task_wdt_init(WDT_TIMEOUT, true); //enable panic so ESP32 restarts
  esp_task_wdt_add(NULL); //add current thread to WDT watch
}

void watchdog_main_loop(){
  //Watchdog resetten
  unsigned long runtime_diff_watchdog =  millis() - runtime_ms_watchdog;
  if (runtime_diff_watchdog > 1000){  
    esp_task_wdt_reset();
    runtime_ms_watchdog = millis();
  }
}