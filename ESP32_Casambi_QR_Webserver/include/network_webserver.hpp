#ifndef _NETWORK_WEBSERVER_HPP_
#define _NETWORK_WEBSERVER_HPP_

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;

extern String yourfootnote;
extern String sitetitle;

extern char* webpage_new;

extern String siteversion; 

extern String www_username;
extern String www_password;

void WebserverInit();

#endif