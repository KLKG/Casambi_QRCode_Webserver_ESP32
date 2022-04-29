#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Preferences.h>
#include <AsyncElegantOTA.h>
#include <SPIFFS.h>
#include <FS.h>

#include <main.hpp>
#include <network.hpp>
#include <network_udp.hpp>
#include <network_webserver.hpp>
#include <network_webserver_index.hpp>
#include <network_webserver_control.hpp>
#include <network_webserver_settings.hpp>
#include <network_webserver_error.hpp>
#include <system_logging.hpp>


char* webpage_new;

AsyncWebServer server(80);

String sitetitle      = "Casambi QR Code Scanner";
String yourfootnote   = "<a href='https://www.l-manufaktur.de/' target='_blank'>&copy; Lichtmanufaktur Berlin GmbH 2022</a>";

String www_username;
String www_password;

void WebserverInit(){
  setting_preferences.begin("settings", false);   
    www_username = setting_preferences.getString("wwwuser", "admin");
    www_password = setting_preferences.getString("wwwpas", "password");
  setting_preferences.end(); 

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    website_index();
    request->send_P(200, "text/html", webpage_new);
  });

  //http://192.168.1.85/control?gw=0&cmd=1&typ=0&tar=0
  //http://192.168.1.85/control?gw=0&cmd=2&typ=0&tar=0
  //http://192.168.1.85/control?gw=0&cmd=3&typ=0&tar=0
  server.on("/control", HTTP_GET, [](AsyncWebServerRequest * request) {
      if (request->hasParam("gw") && request->hasParam("cmd") && request->hasParam("typ") && request->hasParam("tar")) {
      unsigned char gateway = request->getParam("gw")->value().toInt();
      unsigned char command = request->getParam("cmd")->value().toInt();
      unsigned char target_type = request->getParam("typ")->value().toInt();
      unsigned char target_address = request->getParam("tar")->value().toInt();
      website_control(gateway, command, target_type, target_address);
      request->send_P(200, "text/html", webpage_new);
    }else{
      website_error();
      request->send_P(200, "text/html", webpage_new);      
    }
  });

  server.on("/sendcommand", HTTP_POST, [](AsyncWebServerRequest * request) {
    if (request->hasParam("gateway", true) && request->hasParam("command", true) && request->hasParam("target_type", true) && request->hasParam("target_address", true)) {
      unsigned char gateway = request->getParam("gateway", true)->value().toInt();
      unsigned char command = request->getParam("command", true)->value().toInt();
      unsigned char target_type = request->getParam("target_type", true)->value().toInt();
      unsigned char target_address = request->getParam("target_address", true)->value().toInt();
      unsigned char level = 0;
      switch (command){
        case 1: //level
          if (request->hasParam("level", true)) {
            level = request->getParam("level", true)->value().toInt();
            create_command(gateway, target_type, target_address, level);
            request->send_P(200, "text/html", "ok");
          }else{
            request->send_P(200, "text/html", "error");  
          }
          break;
        case 2: //tc
          if (request->hasParam("level", true)) {
            level = request->getParam("level", true)->value().toInt();
            create_command(gateway, target_type, target_address, level);
            request->send_P(200, "text/html", "ok");
          }else{
            request->send_P(200, "text/html", "error");  
          }
          if (request->hasParam("tc", true)) {
            unsigned char tc = request->getParam("tc", true)->value().toInt();
            create_command(gateway, target_type, target_address, 0, tc);
            request->send_P(200, "text/html", "ok");
          }else{
            request->send_P(200, "text/html", "error");  
          }
          break;
        case 3: //rgbw
          if (request->hasParam("level", true)) {
            level = request->getParam("level", true)->value().toInt();
            create_command(gateway, target_type, target_address, level);
            request->send_P(200, "text/html", "ok");
          }else{
            request->send_P(200, "text/html", "error");  
          }
          if (request->hasParam("red", true) && request->hasParam("green", true) && request->hasParam("blue", true) && request->hasParam("white", true)) {
            unsigned char red = request->getParam("red", true)->value().toInt();
            unsigned char green = request->getParam("green", true)->value().toInt();
            unsigned char blue = request->getParam("blue", true)->value().toInt();
            unsigned char white = request->getParam("white", true)->value().toInt();
            create_command(gateway, target_type, target_address, 255, red, green, blue, white);
            request->send_P(200, "text/html", "ok");
          }else{
            request->send_P(200, "text/html", "error");  
          }
          break;      
        default:
          request->send_P(200, "text/html", "error");  
          break;
      }
    }else{
      website_error();
      request->send_P(200, "text/html", webpage_new);        
    }
  });

  server.on("/config", HTTP_ANY, [](AsyncWebServerRequest * request) {
    if(!request->authenticate(www_username.c_str(), www_password.c_str()))
      return request->requestAuthentication();

    setting_preferences.begin("settings", false); 
      if (request->hasParam("DHCP", true)){
        if (request->getParam("DHCP", true)->value() == "active"){
          setting_preferences.putUChar("dhcp", 1);
          dhcp_active = 1;
        }else{
          setting_preferences.putUChar("dhcp", 0);
          dhcp_active = 0;
        }
      }
      if (request->hasParam("Hostname", true)){
        setting_preferences.putString("hostname", request->getParam("Hostname", true)->value());
        Hostname = request->getParam("Hostname", true)->value();
      }
      if (request->hasParam("IP-Adress", true)){
        setting_preferences.putString("ipadress", request->getParam("IP-Adress", true)->value());
        IPaddress = request->getParam("IP-Adress", true)->value();
      }
      if (request->hasParam("Subnet", true)){
        setting_preferences.putString("subnet", request->getParam("Subnet", true)->value());
        Subnet = request->getParam("Subnet", true)->value();
      }
      if (request->hasParam("Gateway", true)){
        setting_preferences.putString("gateway", request->getParam("Gateway", true)->value());
        Gateway = request->getParam("Gateway", true)->value();
      }
      if (request->hasParam("DNS1", true)){
        setting_preferences.putString("dns1", request->getParam("DNS1", true)->value());
        DNS_1 = request->getParam("DNS1", true)->value();
      }
      if (request->hasParam("DNS2", true)){
        setting_preferences.putString("dns2", request->getParam("DNS2", true)->value());  
        DNS_2 = request->getParam("DNS2", true)->value();
      }
      if (request->hasParam("udpport", true)){
        setting_preferences.putInt("udpport", request->getParam("wwwpas", true)->value().toInt());   
      }
      if (request->hasParam("wwwuser", true)){
        setting_preferences.putString("wwwuser", request->getParam("wwwuser", true)->value());   
        www_username = request->getParam("wwwuser", true)->value();
      }
      if (request->hasParam("wwwpas", true)){
        setting_preferences.putString("wwwpas", request->getParam("wwwpas", true)->value());   
        www_password = request->getParam("wwwpas", true)->value();
      }
      setting_preferences.end(); 
      if (request->hasParam("reboot", true)){
        system_logging_line ("Reboot"); 
        delay(500);
        ESP.restart();   
      } 
    website_settings();
    request->send_P(200, "text/html", webpage_new);
    request->send_P(200, "text/html", "ok");
  }); 

  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css", false);
  });

  server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/favicon.ico", "image/x-icon", false);
  });

  server.on("/logo_white.svg", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/logo_white.svg", "image/svg+xml", false);
  });

  server.on("/only_logo_white.svg", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/only_logo_white.svg", "image/svg+xml", false);
  });

  server.on("/solid.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/solid.min.js", "application/javascript", false);
  });

  server.on("/fontawesome.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/fontawesome.min.js", "application/javascript", false);
  });

  // Start ElegantOTA
  AsyncElegantOTA.begin(&server, www_username.c_str(), www_password.c_str());
  // Start server
  server.begin();

}