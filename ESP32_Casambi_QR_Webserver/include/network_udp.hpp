#ifndef _AA_NETWORK_UDP_AANET_HPP_
#define _AA_NETWORK_UDP_AANET_HPP_

#include <ETH.h>

extern int udp_connection_state;
extern int udp_port;

void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level);
void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level, unsigned char tc);
void create_command(unsigned char gateway, unsigned char target_type, unsigned char target_address, unsigned char level, unsigned char red, unsigned char green, unsigned char blue, unsigned char white);
void udp_connect();
void udp_rec_command(String Command);
void udp_send(String Command);
#endif