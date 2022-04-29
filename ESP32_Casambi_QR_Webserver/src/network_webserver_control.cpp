#include <Arduino.h>
#include <string.h>

#include <main.hpp>
#include <network_webserver.hpp>
#include <network_webserver_control.hpp>

void website_control(unsigned char gateway, unsigned char command, unsigned char target_type, unsigned char target_address){
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
    switch (command){
        case 1: //Level
            strcat(webpage_new, String("<h2 class=\"page-section-heading text-center text-uppercase text-white\">control - Level</h2>\n").c_str());
            break;
        case 2: //TC
            strcat(webpage_new, String("<h2 class=\"page-section-heading text-center text-uppercase text-white\">control - Tc</h2>\n").c_str());
            break;
        case 3: //RGBW
            strcat(webpage_new, String("<h2 class=\"page-section-heading text-center text-uppercase text-white\">control - RGBW</h2>\n").c_str());
            break;
    }
    strcat(webpage_new, String("<div class=\"divider-custom divider-light\">\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-icon\"><i class=\"fas fa-sliders-h\"></i></div>\n").c_str());
    strcat(webpage_new, String("<div class=\"divider-custom-line\"></div>\n").c_str());
    strcat(webpage_new, String("</div>\n").c_str());
    strcat(webpage_new, String("<div class=\"text-center mt-4\">\n").c_str());
    unsigned char temp_level = 0;
    unsigned char temp_tc = 0; 
    unsigned char temp_red = 0; 
    unsigned char temp_green = 0; 
    unsigned char temp_blue = 0; 
    unsigned char temp_white = 0; 
    switch (command){
        case 1: //Level
            strcat(webpage_new, String("<form name=\"doit\" action=\"sendcommand\" method=\"post\" target=\"hidden-form\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"gateway\" id=\"gateway\" value=\""+String(gateway, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"command\" id=\"command\" value=\""+String(command, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_type\" id=\"target_type\" value=\""+String(target_type, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_address\" id=\"target_address\" value=\""+String(target_address, DEC)+"\"><br><br>\n").c_str());    
            strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"level\" style=\"padding-right: 1rem\">Level:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"level\" name=\"level\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_level, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit'].submit()\"><output style=\"padding-left: 1rem\" id=\"sl_level\" name=\"sl_level\">"+String(temp_level, DEC)+"</output></td></tr>\n").c_str());    
            strcat(webpage_new, String("</table><br><br>\n").c_str());    
            //strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type=\"Submit\" name=\"send\" value=\"send\">\n").c_str());    
            strcat(webpage_new, String("</form>\n").c_str());     
            break;

        case 2: //TC
            strcat(webpage_new, String("<form name=\"doit_level\" action=\"sendcommand\" method=\"post\" target=\"hidden-form\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"gateway\" id=\"gateway\" value=\""+String(gateway, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"command\" id=\"command\" value=\""+String(command, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_type\" id=\"target_type\" value=\""+String(target_type, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_address\" id=\"target_address\" value=\""+String(target_address, DEC)+"\"><br><br>\n").c_str());   
            strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"level\" style=\"padding-right: 1rem\">Level:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"level\" name=\"level\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_level, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_level'].submit()\"><output style=\"padding-left: 1rem\" id=\"sl_level\" name=\"sl_level\">"+String(temp_level, DEC)+"</output></td></tr>\n").c_str());        
            //strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type=\"Submit\" name=\"send\" value=\"send\">\n").c_str());    
            strcat(webpage_new, String("</form>\n").c_str());  
            strcat(webpage_new, String("<tr><td>&nbsp;</td><td>&nbsp;</td></tr>\n").c_str());   
            strcat(webpage_new, String("<form name=\"doit_tc\" action=\"sendcommand\" method=\"post\" target=\"hidden-form\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"gateway\" id=\"gateway\" value=\""+String(gateway, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"command\" id=\"command\" value=\""+String(command, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_type\" id=\"target_type\" value=\""+String(target_type, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_address\" id=\"target_address\" value=\""+String(target_address, DEC)+"\"><br><br>\n").c_str());      
            strcat(webpage_new, String("<tr><td><label for=\"tc\" style=\"padding-right: 1rem\">Tc:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"tc\" name=\"tc\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_tc, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_tc'].submit()\"><output style=\"padding-left: 1rem\" for=\"tc\">"+String(temp_tc, DEC)+"</output></td></tr>\n").c_str());    
            strcat(webpage_new, String("</table><br><br>\n").c_str());    
            //strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type=\"Submit\" name=\"send\" value=\"send\">\n").c_str());    
            strcat(webpage_new, String("</form>\n").c_str());  
            break;

        case 3: //RGBW
            strcat(webpage_new, String("<form name=\"doit_level\" action=\"sendcommand\" method=\"post\" target=\"hidden-form\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"gateway\" id=\"gateway\" value=\""+String(gateway, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"command\" id=\"command\" value=\""+String(command, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_type\" id=\"target_type\" value=\""+String(target_type, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_address\" id=\"target_address\" value=\""+String(target_address, DEC)+"\"><br><br>\n").c_str());   
            strcat(webpage_new, String("<table style=\"margin: 0 auto; min-width: 3vw;\">\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"level\" style=\"padding-right: 1rem\">Level:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"level\" name=\"level\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_level, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_level'].submit()\"><output style=\"padding-left: 1rem\" id=\"sl_level\" name=\"sl_level\">"+String(temp_level, DEC)+"</output></td></tr>\n").c_str());        
            //strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type=\"Submit\" name=\"send\" value=\"send\">\n").c_str());    
            strcat(webpage_new, String("</form>\n").c_str());  
            strcat(webpage_new, String("<tr><td>&nbsp;</td><td>&nbsp;</td></tr>\n").c_str());  
            strcat(webpage_new, String("<form name=\"doit_rgbw\" action=\"sendcommand\" method=\"post\" target=\"hidden-form\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"gateway\" id=\"gateway\" value=\""+String(gateway, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"command\" id=\"command\" value=\""+String(command, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_type\" id=\"target_type\" value=\""+String(target_type, DEC)+"\">\n").c_str());
            strcat(webpage_new, String("<input type=\"hidden\" name=\"target_address\" id=\"target_address\" value=\""+String(target_address, DEC)+"\"><br><br>\n").c_str());     
            strcat(webpage_new, String("<tr><td><label for=\"red\" style=\"padding-right: 1rem\">Red:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"red\" name=\"red\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_red, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_rgbw'].submit()\"><output style=\"padding-left: 1rem\" for=\"red\">"+String(temp_red, DEC)+"</output></td></tr>\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"green\" style=\"padding-right: 1rem\">Green:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"green\" name=\"green\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_green, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_rgbw'].submit()\"><output style=\"padding-left: 1rem\" for=\"green\">"+String(temp_green, DEC)+"</output></td></tr>\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"blue\" style=\"padding-right: 1rem\">Blue:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"blue\" name=\"blue\" min=\"0\" max=\"255\" step=\"1\" value=\""+String(temp_blue, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_rgbw'].submit()\"><output style=\"padding-left: 1rem\" for=\"blue\">"+String(temp_blue, DEC)+"</output></td></tr>\n").c_str());    
            strcat(webpage_new, String("<tr><td><label for=\"white\" style=\"padding-right: 1rem\">White:</label></td><td><input type=\"range\" sytle=\"width: 21%\" id=\"white\" name=\"white\" min=\"0\" max=\"254\" step=\"1\" value=\""+String(temp_white, DEC)+"\" oninput=\"this.nextElementSibling.value = this.value\" onchange=\"document.forms['doit_rgbw'].submit()\"><output style=\"padding-left: 1rem\" for=\"white\">"+String(temp_white, DEC)+"</output></td></tr>\n").c_str());  
            strcat(webpage_new, String("</table><br><br>\n").c_str());  
            //strcat(webpage_new, String("<input class=\"btn btn-xl btn-outline-light\" type=\"Submit\" name=\"send\" value=\"send\">\n").c_str());  
            strcat(webpage_new, String("</form>\n").c_str());  
            break;
        
        default:   
            strcat(webpage_new, String("<p class=\"startscreen-subheading font-weight-light mb-0\">Sadfully there was an error ... or the code is unknown.</p>\n").c_str());      
            break;
    }
    strcat(webpage_new, String("</div>\n").c_str());  
    strcat(webpage_new, String("</div>\n").c_str());  
    strcat(webpage_new, String("</section>\n").c_str());  

    strcat(webpage_new, String("<iframe style=\"display:none\" name=\"hidden-form\"></iframe>\n").c_str());   

    strcat(webpage_new, String("<div class=\"copyright py-4 text-center text-white\">\n").c_str());    
    strcat(webpage_new, String("<div class=\"container\"><small>Copyright &copy; Licht Manufaktur Berlin GmbH 2022</small></div>\n").c_str());    
    strcat(webpage_new, String("</div>\n").c_str());  

    strcat(webpage_new, String("</body>\n").c_str());

    strcat(webpage_new, String("</html>\n").c_str());
}