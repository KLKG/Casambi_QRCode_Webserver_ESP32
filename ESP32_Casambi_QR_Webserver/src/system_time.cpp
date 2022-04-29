#include <Arduino.h>

#include <main.hpp>
#include <system_time.hpp>
#include <system_logging.hpp>

unsigned long runtime_ms_system = 0;

String ntpServer;
long  gmtOffset_sec;
int   daylightOffset_sec;
unsigned char ntpServer_active;
unsigned char ntp_got_time = 0;

int time_year = 2020;
int time_month = 1;
int time_day = 1;
int time_hour = 0;
int time_minute = 0;
int time_second = 0;

void timeInit(){
  setting_preferences.begin("settings", false); 
    ntpServer_active = setting_preferences.getUChar("ntpact", 0);
    ntpServer = setting_preferences.getString("ntpsrv", "pool.ntp.org");
    gmtOffset_sec = setting_preferences.getLong("ntpoff", 0);
    daylightOffset_sec = setting_preferences.getInt("ntpday", 3600);
  setting_preferences.end(); 

  if (ntpServer_active == 1){    
    char buffer[100]; 
    ntpServer.toCharArray(buffer, 20);
    configTime(gmtOffset_sec, daylightOffset_sec, buffer);
    system_logging_line("started NTP-Server"); 
    struct tm timeinfo;
    if(getLocalTime(&timeinfo)){
      time_day = timeinfo.tm_mday;
      time_month = 1 + timeinfo.tm_mon;
      time_year = 1900 + timeinfo.tm_year;
      time_hour = timeinfo.tm_hour;
      time_minute = timeinfo.tm_min;
      time_second = timeinfo.tm_sec;
      system_logging_line(print_2_digits_time(time_hour) + ":" + print_2_digits_time(time_minute) + ":" + print_2_digits_time(time_second));
      system_logging_line(print_2_digits_time(time_day) + "." + print_2_digits_time(time_month) + "." + print_2_digits_time(time_year));
      ntp_got_time = 1;
    }else{
      system_logging_line("Failed to obtain time");
      ntp_got_time = 0;
    }
  }  
}

void system_time_main_loop(){
  int runtime_rest = 0;
  unsigned long runtime_diff_system =  millis() - runtime_ms_system;
  if (runtime_diff_system > 1000){
    runtime_rest = runtime_diff_system%1000;
    while(runtime_diff_system/1000 >= 1) {
      time_second++;
      if (time_second == 60){
        time_second = 0;
        time_minute ++;
        if (time_minute == 60){
          time_minute = 0;
          time_hour++;
          if (time_hour == 24){
            time_hour = 0;
            printLocalTime();
          }
        }
		  }
      runtime_diff_system = runtime_diff_system - 1000;
    }
    runtime_ms_system = millis() - runtime_rest;
  }   
}

void printLocalTime(){
  struct tm timeinfo;
  if (ntpServer_active == 1){
    if(!getLocalTime(&timeinfo)){
      system_logging_line("Failed to obtain time");
      return;
    }else{
      time_day = timeinfo.tm_mday;
      time_month = 1 + timeinfo.tm_mon;
      time_year = 1900 + timeinfo.tm_year;
      time_hour = timeinfo.tm_hour;
      time_minute = timeinfo.tm_min;
      time_second = timeinfo.tm_sec;
    }
  }
  system_logging_line(print_2_digits_time(time_hour) + ":" + print_2_digits_time(time_minute) + ":" + print_2_digits_time(time_second));
  system_logging_line(print_2_digits_time(time_day) + "." + print_2_digits_time(time_month) + "." + print_2_digits_time(time_year));
}

String print_2_digits_time(unsigned long time){
  if (time < 10){
    return("0" + String(time));
  }else{
    return(String(time));
  }
}

String print_time(unsigned long milis){
  unsigned long seconds = milis / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;
  milis %= 1000;
  seconds %= 60;
  minutes %= 60;
  hours %= 24;
  return(print_2_digits_time(hours) + ":" + print_2_digits_time(minutes) + ":" + print_2_digits_time(seconds));
}