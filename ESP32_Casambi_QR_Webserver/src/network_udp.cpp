#include <Arduino.h>
#include <string.h>
#include <ETH.h>
#include <AsyncUDP.h>

#include <main.hpp>
#include <network.hpp>
#include <network_udp.hpp>
#include <system_logging.hpp>
#include <system_led.hpp>

AsyncUDP casambi_udp;

int udp_connection_state = 0;
int udp_port = 10021;

void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level){
    String command = String(gateway, HEX) + ".72.6.20." + String(level, HEX)  + ".10.0." + String(target_type, HEX) + "." + String(target_address, HEX);
    udp_send(command);
}
void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level, unsigned char tc){
    String command = String(gateway, HEX) + ".72.7.30." + String(tc, HEX)  + ".0.10.0." + String(target_type, HEX) + "." + String(target_address, HEX);
    udp_send(command);
}
void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level, unsigned char red, unsigned char green, unsigned char blue, unsigned char white){
    String command = String(gateway, HEX) + ".72.7.2f." + String(red, HEX)  + "." + String(green, HEX)  + "." + String(blue, HEX)  + "." + String(white, HEX)  + "." + String(target_type, HEX) + "." + String(target_address, HEX) + ".ff";
    udp_send(command);
}

void udp_rec_command(String Command){
  #ifdef UDP_DEBUG_RAW
    system_logging_line("UDP_REC: " + Command);
  #endif      
}

void udp_connect(){
  if(casambi_udp.listen(udp_port)) {
      udp_connection_state = udp_connection_state + 1;
      leds_udp_on_off = 1;
      system_logging_line ("UDP Listening on IP: "+IPaddress+" Port: "+String(udp_port, DEC));
      casambi_udp.onPacket([](AsyncUDPPacket packet) {
          String udp_data_rec = (char*)packet.data();
          udp_rec_command(udp_data_rec);
      });      
  }
}

void udp_send(String Command){
    if (udp_connection_state == 1){
        String final_command = Command + "\r\n";
        casambi_udp.broadcastTo(final_command.c_str(), udp_port);
    }
    #ifdef UDP_DEBUG_RAW
        system_logging_line(Command);      
    #endif    
}