#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <Arduino.h>
#include <string.h>
#include <ETH.h>
#include <phy_ksz8081.h>

#undef ETH_PHY_TYPE
#define ETH_PHY_TYPE ETH_PHY_KSZ8081 //rückgabe 2

extern unsigned char leds_network_on_off;

extern bool eth_connected;

extern unsigned char dhcp_active;
extern String IPaddress;
extern String Subnet;
extern String Gateway;
extern String DNS_1;
extern String DNS_2;
extern String Hostname;
extern String MacAdress;

void WiFiEvent(WiFiEvent_t event);
void NetworkInit();
void network_main_loop();

#endif