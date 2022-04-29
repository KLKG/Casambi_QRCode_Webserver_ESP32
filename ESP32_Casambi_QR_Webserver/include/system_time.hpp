#ifndef _SYSTEM_TIME_HPP_
#define _SYSTEM_TIME_HPP_

#include <Arduino.h>
#include <string.h>

extern String ntpServer;
extern long  gmtOffset_sec;
extern int   daylightOffset_sec;
extern unsigned char ntpServer_active;

extern int time_year;
extern int time_month;
extern int time_day;
extern int time_hour;
extern int time_minute;
extern int time_second;

extern unsigned long runtime_ms_system;

void timeInit();
void system_time_main_loop();
void printLocalTime();
String print_2_digits_time(unsigned long time);
String print_time(unsigned long milis);
#endif