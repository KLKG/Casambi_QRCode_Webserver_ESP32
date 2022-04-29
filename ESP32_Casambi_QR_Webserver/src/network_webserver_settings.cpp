#include <Arduino.h>
#include <string.h>

#include <main.hpp>
#include <network.hpp>
#include <network_udp.hpp>
#include <network_webserver.hpp>
#include <network_webserver_settings.hpp>
#include <system_time.hpp>

void website_settings(){
    strcpy(webpage_new, "");
    strcat(webpage_new, String("<!DOCTYPE html>\n").c_str());
    strcat(webpage_new, String("<html lang=\"en\">\n").c_str());
    strcat(webpage_new, String("<head>\n").c_str());
    strcat(webpage_new, String("<meta charset=\"utf-8\" />\n").c_str());
    strcat(webpage_new, String("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=no\" />\n").c_str());
    strcat(webpage_new, String("<meta name=\"description\" content=\"\" />\n").c_str());
    strcat(webpage_new, String("<meta name=\"author\" content=\"\" />\n").c_str());
    strcat(webpage_new, String("<title>Casambi QR-Code Scanner</title>\n").c_str());
    strcat(webpage_new, String("<link rel=\"icon\" type=\"image/x-icon\" href=\"favicon.ico\" />\n").c_str());
    strcat(webpage_new, String("<link href=\"style.css\" rel=\"stylesheet\" />\n").c_str());
    strcat(webpage_new, String("<script src=\"solid.min.js\"></script>\n").c_str());
    strcat(webpage_new, String("<script src=\"fontawesome.min.js\"></script>\n").c_str());
    strcat(webpage_new, String("</head>\n").c_str());

    strcat(webpage_new, String("<body id=\"page-top\">\n").c_str());

    strcat(webpage_new, String("<nav class=\"navbar bg-secondary text-uppercase fixed-top\" id=\"mainNav\">\n").c_str());
    strcat(webpage_new, String("<div class=\"container\" style=\"justify-content: flex-start\">\n").c_str());
    strcat(webpage_new, String("<img class=\"startscreen-avatar\" style=\"height: 3rem\" src=\"only_logo_white.svg\" alt=\"Lithernet\" />\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());
    strcat(webpage_new, String("</nav>\n").c_str());

    strcat(webpage_new, String("<section class=\"startscreen bg-primary text-white mb-0\" id=\"control\">\n").c_str());
    strcat(webpage_new, String("<div class=\"container\">\n").c_str());
    strcat(webpage_new, String("<h2 class=\"page-section-heading text-center text-uppercase text-white\">Settings</h2>\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom divider-light\">\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-icon\"><i class=\"fas fa-tools\"></i></i></div>\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());
    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    strcat(webpage_new, String("<form action=\"config\" method=\"post\">\n").c_str());
    strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">DHCP</label></td>\n").c_str());
    if (ntpServer_active == 1){
        strcat(webpage_new, String("<td><select name=\"DHCP\" id=\"DHCP\"><option selected>active</option><option>inactive</option></select></td>\n").c_str());
    }else{
        strcat(webpage_new, String("<td><select name=\"DHCP\" id=\"DHCP\"><option>active</option><option selected>inactive</option></select></td>\n").c_str());
    }       
    strcat(webpage_new, String("</tr>\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Hostname</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='Hostname' value='"+ Hostname +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());  
    strcat(webpage_new, String("<tr>\n").c_str());
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">IP-Adress</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='IP-Adress' value='"+ IPaddress +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Subnet</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='Subnet' value='"+ Subnet +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Gateway</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='Gateway' value='"+ Gateway +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Namserver 1</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='DNS1' value='"+ DNS_1 +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Namserver 2</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='DNS2' value='"+ DNS_2 +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());    
    strcat(webpage_new, String("</table><br><br>\n").c_str());
    strcat(webpage_new, String("<button class=\"btn btn-xl btn-outline-light\" type='submit' name='Settings'> Save </button>\n").c_str());
    strcat(webpage_new, String("</form>\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());    

    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    strcat(webpage_new, String("<form action=\"config\" method=\"post\">\n").c_str());
    strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">UDP-Port</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='udpport' value='"+ String(udp_port, DEC) +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());    
    strcat(webpage_new, String("</table><br><br>\n").c_str());
    strcat(webpage_new, String("<button class=\"btn btn-xl btn-outline-light\" type='submit' name='UdpSettings'> Save </button>\n").c_str());
    strcat(webpage_new, String("</form>\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());    

    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    strcat(webpage_new, String("<form action=\"config\" method=\"post\">\n").c_str());
    strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Username</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='wwwuser' value='"+ www_username +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str()); 
    strcat(webpage_new, String("<tr>\n").c_str());  
    strcat(webpage_new, String("<td><label style=\"padding-right: 1rem\">Password</label></td>\n").c_str());
    strcat(webpage_new, String("<td><input type='text' name='wwwpas' value='"+ www_password +"'></td>\n").c_str());
    strcat(webpage_new, String("</tr>\n").c_str());       
    strcat(webpage_new, String("</table><br><br>\n").c_str());
    strcat(webpage_new, String("<button class=\"btn btn-xl btn-outline-light\" type='submit' name='UserSettings'> Save </button>\n").c_str());
    strcat(webpage_new, String("</form>\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());  

    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    strcat(webpage_new, String("<form method='POST' action='/config'>\n").c_str());
    strcat(webpage_new, String("<button class=\"btn btn-xl btn-outline-light\" type='submit' name='reboot'> Reboot </button>\n").c_str());
    strcat(webpage_new, String("</form>\n").c_str());   
    strcat(webpage_new, String("</div>\n").c_str());     

    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type='button' onClick=\"location.href='update'\" VALUE='Update'>\n").c_str()); 
    strcat(webpage_new, String("</div>\n").c_str());    
    strcat(webpage_new, String("</section>\n").c_str());


    strcat(webpage_new, String("<div class=\"copyright py-4 text-center text-white\">\n").c_str());    
    strcat(webpage_new, String("<div class=\"container\"><small>Copyright &copy; Licht Manufaktur Berlin GmbH 2022</small></div>\n").c_str());    
    strcat(webpage_new, String("</div>\n").c_str());  
      
    strcat(webpage_new, String("</body>\n").c_str());

    strcat(webpage_new, String("</html>\n").c_str());
}