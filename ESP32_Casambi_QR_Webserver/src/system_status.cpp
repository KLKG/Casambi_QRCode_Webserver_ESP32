#include <Arduino.h>
#include <SPIFFS.h>
#include <FS.h>

#include <main.hpp>
#include <system_status.hpp>
#include <system_logging.hpp>
#include <system_time.hpp>

unsigned long runtime_ms_freememory = 0;

void report_memory(){
    system_logging_line("-------------------------");  
    system_logging_line("Memory Usage:");
    system_logging_line("Total heap: " + String(ESP.getHeapSize()));
    system_logging_line("Free heap: " + String(ESP.getFreeHeap()));  
    system_logging_line("Total PSRAM:" + String(ESP.getPsramSize()));
    system_logging_line("Free PSRAM: " + String(ESP.getFreePsram()));
    system_logging_line("Used PSRAM: " + String(ESP.getPsramSize() - ESP.getFreePsram(), DEC));
    system_logging_line("Total FS:" + String(SPIFFS.totalBytes()));
    system_logging_line("Used FS: " + String(SPIFFS.usedBytes()));
    system_logging_line("-------------------------");
}

void report_free_memory(){
    system_logging_line("-------------------------");
    system_logging_line("Free Memory:");
    system_logging_line("Time: " + print_2_digits_time(time_hour) + ":" + print_2_digits_time(time_minute) + ":" + print_2_digits_time(time_second));
    system_logging_line("Free heap: " + String(ESP.getFreeHeap()));
    system_logging_line("Free PSRAM: " + String(ESP.getFreePsram())); 
    system_logging_line("Used FS:" + String(SPIFFS.usedBytes()));       
    system_logging_line("-------------------------");
}

void system_status_main_loop(){
    unsigned long runtime_diff_freememory =  millis() - runtime_ms_freememory;
    if (runtime_diff_freememory > 30000){  
      report_free_memory();
      runtime_ms_freememory = millis();
    }  
}