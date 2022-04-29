#ifndef _SYSTEM_LED_HPP_
#define _SYSTEM_LED_HPP_

extern unsigned char mainled_state;
extern unsigned char leds_network_on_off;
extern unsigned char leds_ble_on_off;
extern unsigned char leds_udp_on_off;
extern unsigned char led_identify;
extern unsigned char leds_active;

void led_init();
void mainleds_setPixelColor(unsigned char lednr, unsigned char red, unsigned char green, unsigned char blue, unsigned char activateled);
void leds_off();
void leds_network();
void leds_ble();
void leds_activity();
void leds_identify();
void leds_main_loop();
#endif