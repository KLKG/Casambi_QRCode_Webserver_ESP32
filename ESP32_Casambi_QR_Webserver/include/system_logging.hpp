#ifndef _SYSTEM_LOGGING_HPP_
#define _SYSTEM_LOGGING_HPP_

#include <Arduino.h>
#include <string.h>

#define LOGGINGnMAX 200
#define logging_temp_lenth 500

struct logging_buffer_entrys {
  char command[500];
  unsigned char used = 0;
};

extern logging_buffer_entrys * logging_buffer;

extern unsigned char console_n;

extern bool  console_transaction;
extern unsigned int waited_console_inserts;

void console_put(int string_length, String s);
void system_logging_line(String s);

#endif