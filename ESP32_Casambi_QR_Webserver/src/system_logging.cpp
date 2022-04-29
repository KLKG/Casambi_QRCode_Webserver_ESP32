#include <Arduino.h>
#include <string.h>

#include <main.hpp>
#include <system_logging.hpp>

struct logging_buffer_entrys * logging_buffer;

unsigned char console_n = 0;     /* Anzahl der Zeichen im Buffer */
bool  console_transaction = false;
unsigned int waited_console_inserts = 0;

void console_put(int string_length, String s){
    for (int i=0;i<string_length+1;i++){
        logging_buffer[console_n].command[i] = s[i];
        logging_buffer[console_n].used = 1;
    }
    if (console_n < LOGGINGnMAX-1){
        console_n++;
    }else{
        console_n = 0;
    }
}

bool console_transaction_running(){
    if (console_transaction == false){
        console_transaction = true;
        return false;
    }else{
        return true;
    }
}


void system_logging_line(String s){
    #ifdef DEBUG_HTTP_KONSOLE
        while(console_transaction_running() == true){
            waited_console_inserts++;
            Serial.println("$");
        }

        int string_length = s.length();    
        console_put(string_length, s);
    #endif
    #ifdef DEBUG_SERIAL_PORT    
        Serial.println(s);
    #endif
    console_transaction = false;
}