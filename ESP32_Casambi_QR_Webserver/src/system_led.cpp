#include <Arduino.h>
#include <Preferences.h>
#include <Adafruit_NeoPixel.h>

#include <main.hpp>
#include <system_led.hpp>

#define LED_PIN 13
#define LED_COUNT 4
#define ethernet_port_led 17

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned char mainled_state = 0;
unsigned char leds_network_on_off = 0;
unsigned char leds_ble_on_off = 0;
unsigned char leds_udp_on_off = 0;
unsigned char led_identify = 0;
unsigned char leds_active = 4;
unsigned char led_identify_started = 0;
unsigned char leds_need_to_be_off = 0;
unsigned char identify_state = 0;

unsigned long runtime_ms_mainled = 0;
unsigned long identify_ms_led = 0;

void led_init(){
    strip.begin();
    delay(1);
    strip.show(); // Initialize all pixels to 'off'  
    leds_active = 4;
}

void mainleds_setPixelColor(unsigned char lednr, unsigned char red, unsigned char green, unsigned char blue, unsigned char activateled){
    if (leds_active != 0){
        strip.setPixelColor(lednr, (red/leds_active), (green/leds_active), (blue/leds_active));
    }else{
        strip.setPixelColor(lednr, 0, 0, 0);
    }
    if (activateled == 1){
      delay(1);  
      strip.show();      
    }
}

void leds_off(){
    mainleds_setPixelColor(0, 0, 0, 0, 0);
    mainleds_setPixelColor(1, 0, 0, 0, 0);
    mainleds_setPixelColor(2, 0, 0, 0, 0);
    mainleds_setPixelColor(3, 0, 0, 0, 1);    
}

void leds_network(){
  if (led_identify==0){
    switch(leds_network_on_off){ 
        case 0: mainleds_setPixelColor(1, 0, 0, 0, 0); 
                //digitalWrite(ethernet_port_led, LOW);
                break;
        case 1: mainleds_setPixelColor(1, 255, 255, 0, 0);   
                //digitalWrite(ethernet_port_led, HIGH);
                break;
    }
  }
}

void leds_ble(){
  if (led_identify==0){
    switch(leds_ble_on_off){ 
        case 0: mainleds_setPixelColor(2, 255, 0, 0, 0); 
                break;
        case 1: mainleds_setPixelColor(2, 0, 0, 255, 0);   
                break;
    }
  }
}

void leds_udp(){
  if (led_identify==0){
    switch(leds_udp_on_off){ 
        case 0: mainleds_setPixelColor(3, 255, 0, 0, 0); 
                break;
        case 1: mainleds_setPixelColor(3, 0, 255, 0, 0);   
                break;
    }
  }
}

void leds_activity(){
    leds_ble();
    leds_network();
    leds_udp();
    switch(mainled_state){ 
        case 0: mainleds_setPixelColor(0, 0, 0, 0, 1);
                mainled_state = 1;
                break;
        case 1: mainleds_setPixelColor(0, 0, 255, 0, 1);
                mainled_state = 0;
                break;
    }
}

void leds_identify(){
    switch(identify_state){ 
        case 0: mainleds_setPixelColor(1, 0, 0, 0, 0);
                mainleds_setPixelColor(2, 0, 0, 0, 0);
                mainleds_setPixelColor(3, 0, 0, 0, 1); 
                identify_state = 1;
                break;
        case 1: mainleds_setPixelColor(1, 255, 0, 255, 0);
                mainleds_setPixelColor(2, 0, 0, 0, 0);
                mainleds_setPixelColor(3, 0, 0, 0, 1); 
                identify_state = 2;
                break;
        case 2: mainleds_setPixelColor(1, 255, 0, 255, 0);
                mainleds_setPixelColor(2, 255, 0, 255, 0);
                mainleds_setPixelColor(3, 0, 0, 0, 1); 
                identify_state = 3;
                break; 
        case 3: mainleds_setPixelColor(1, 255, 0, 255, 0);
                mainleds_setPixelColor(2, 255, 0, 255, 0);
                mainleds_setPixelColor(3, 255, 0, 255, 1); 
                identify_state = 4;
                break;
        case 4: mainleds_setPixelColor(1, 255, 0, 255, 0);
                mainleds_setPixelColor(2, 255, 0, 255, 0);
                mainleds_setPixelColor(3, 0, 0, 0, 1); 
                identify_state = 5;
                break;    
        case 5: mainleds_setPixelColor(1, 255, 0, 255, 0);
                mainleds_setPixelColor(2, 0, 0, 0, 0);
                mainleds_setPixelColor(3, 0, 0, 0, 1);
                identify_state = 0;
                break;                                                                                                   
    }    
}

void leds_main_loop(){

    //Activity LED
    unsigned long runtime_diff_mainled =  millis() - runtime_ms_mainled;
    if (runtime_diff_mainled > 1000){
        leds_activity();
        runtime_ms_mainled = millis(); 
    } 

    if (led_identify == 1){
        //Identify des Gerätes
        if (led_identify_started == 0){
          identify_ms_led = millis();
          led_identify_started = 1;
        }
        unsigned long identify_diff_led =  millis() - identify_ms_led;
        if (identify_diff_led > 10000){
            mainleds_setPixelColor(1, 0, 0, 0, 0);
            mainleds_setPixelColor(2, 0, 0, 0, 0);
            mainleds_setPixelColor(3, 0, 0, 0, 1);   
            led_identify = 0;        
            identify_state = 0; 
            led_identify_started = 0;
        }else if (identify_diff_led % 500 == 0){
            leds_identify();
        }        
    }
}