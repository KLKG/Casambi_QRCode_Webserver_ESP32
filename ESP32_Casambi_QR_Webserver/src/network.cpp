#include <Arduino.h>
#include <ETH.h>
#include <Preferences.h>

#include <main.hpp>
#include <system_led.hpp>
#include <network.hpp>
#include <network_udp.hpp>
#include <phy_ksz8081.h>
#include <system_logging.hpp>
#include <system_led.hpp>

bool eth_connected = false;

unsigned char dhcp_active;
String IPaddress;
String Subnet;
String Gateway;
String DNS_1;
String DNS_2;
String Hostname;
String MacAdress;


void WiFiEvent(WiFiEvent_t event){
String temp_string_2;

  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      system_logging_line("ETH Started");
      ETH.setHostname(Hostname.c_str());
      IPaddress = "0.0.0.0";
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      system_logging_line("ETH Connected");
    leds_network_on_off = 1;  
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      leds_network_on_off = 1;  
      temp_string_2 = "ETH MAC: ";
      temp_string_2 += ETH.macAddress();
      MacAdress = ETH.macAddress();
      temp_string_2 += ", IPv4: ";
      temp_string_2 += ETH.localIP().toString();
      if (ETH.fullDuplex()) {
        temp_string_2 += ", FULL_DUPLEX";
      }
      temp_string_2 += ", ";
      temp_string_2 += String(ETH.linkSpeed(), DEC);
      system_logging_line(temp_string_2 + "Mbps");
      system_logging_line("Use this URL to connect: http://" + ETH.localIP().toString() + "/");
      IPaddress = ETH.localIP().toString();
      Subnet = ETH.subnetMask().toString();
      Gateway = ETH.gatewayIP().toString();
      DNS_1 = ETH.dnsIP(0).toString();
      DNS_2 = ETH.dnsIP(1).toString();
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      system_logging_line("ETH Disconnected");
      leds_network_on_off = 0;    
      leds_udp_on_off = 0;
      eth_connected = false;
      udp_connection_state=0;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      system_logging_line("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}

void NetworkInit(){
  setting_preferences.begin("settings", false);   
    dhcp_active = setting_preferences.getUChar("dhcp", 0);
    IPaddress = setting_preferences.getString("ipadress", "192.168.1.85");
    Subnet = setting_preferences.getString("subnet", "255.255.255.0");
    Gateway = setting_preferences.getString("gateway", "192.168.1.1");
    DNS_1 = setting_preferences.getString("dns1", "192.168.1.1"); 
    DNS_2 = setting_preferences.getString("dns2", "192.168.1.1");
    Hostname = setting_preferences.getString("hostname", "casa_qr_code");  
    udp_port = setting_preferences.getInt("udpport", 10021);  
  setting_preferences.end(); 

  WiFi.onEvent(WiFiEvent);

  if (dhcp_active == 1){
    ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLOCK_GPIO0_OUT);    
  } else{
    IPAddress temp_ip;
    IPAddress temp_gateway;
    IPAddress temp_subnet;
    IPAddress temp_dns_1;
    IPAddress temp_dns_2;
    
    temp_ip.fromString(IPaddress);
    temp_gateway.fromString(Gateway);
    temp_subnet.fromString(Subnet); 
    temp_dns_1.fromString(DNS_1);
    temp_dns_2.fromString(DNS_2);    
    ETH.begin(ETH_PHY_ADDR, ETH_PHY_POWER, ETH_PHY_MDC, ETH_PHY_MDIO, ETH_PHY_TYPE, ETH_CLOCK_GPIO0_OUT);
    ETH.config(temp_ip, temp_gateway, temp_subnet, temp_dns_1, temp_dns_2);
  }

  system_logging_line("Ethernet ready");
}

void network_main_loop(){
  if (eth_connected == true){
    if (udp_connection_state == 0){
      udp_connect();
    }  
  }
}