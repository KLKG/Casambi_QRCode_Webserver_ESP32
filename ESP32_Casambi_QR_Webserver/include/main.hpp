#ifndef _MAIN_HPP_
#define _MAIN_HPP_

#include <Preferences.h>

//------------------------ Debug - Settings -------
/*Switches for Debug Outputs
  DEBUG = All Debug Messages
  DEBUG_HTTP_KONSOLE = Output in Web Console
  DEBUG_SERIAL_PORT = Output über Serial Port / USB*/
//#define DEBUG
//#define DEBUG_HTTP_KONSOLE
#define DEBUG_SERIAL_PORT

/*Switches to give system debugg information about system states
  print_system_states = periodic output of system states on UART*/
#define print_system_states
//#define print_system_states_webserver

//------------------------ Release - Settings -----
#define RELEASE
//-------------------------------------------------


extern String siteversion;

extern Preferences setting_preferences; 
void setup();
void loop();

#endif