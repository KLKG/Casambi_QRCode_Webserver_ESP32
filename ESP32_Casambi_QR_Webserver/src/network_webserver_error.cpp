#include <Arduino.h>
#include <string.h>

#include <main.hpp>
#include <network_webserver.hpp>
#include <network_webserver_error.hpp>

void website_error(){
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

    strcat(webpage_new, String("<section class=\"startscreen bg-primary text-white text-center\">\n").c_str());
    strcat(webpage_new, String("<div class=\"container d-flex align-items-center flex-column\">\n").c_str());
    strcat(webpage_new, String("<img class=\"startscreen-avatar mb-5\" src=\"logo_white.svg\" alt=\"Lithernet\" />\n").c_str());    
    strcat(webpage_new, String("<div class=\"divider-custom divider-light\">\n").c_str());    
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());    
    strcat(webpage_new, String("<div class=\"divider-custom-icon\"><i class=\"fas fa-camera\"></i></div>\n").c_str());    
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());    
    strcat(webpage_new, String("</div>\n").c_str());    
    strcat(webpage_new, String("<p class=\"startscreen-subheading font-weight-light mb-0\">Sadfully there was an error ... or the code is unknown.</p>\n").c_str());    
    strcat(webpage_new, String("</section>\n").c_str());   

    strcat(webpage_new, String("<div class=\"copyright py-4 text-center text-white\">\n").c_str());    
    strcat(webpage_new, String("<div class=\"container\"><small>Copyright &copy; Licht Manufaktur Berlin GmbH 2022</small></div>\n").c_str());    
    strcat(webpage_new, String("</div>\n").c_str());    

    strcat(webpage_new, String("</body>\n").c_str());

    strcat(webpage_new, String("</html>\n").c_str());
}