# Casambi_QRCode_Webserver_ESP32

This is a small web server based on an ESP32 (16MB + PSRAM). 
The QR codes contain all the information needed to control the Casambi systems via QR codes.

It can:
- single devices
- Groups, all ungrouped devices
- scenes
- all connected devices (broadcast)

in each case
- brightness
- Color temperature + brightness
- RGBW + brightness 

can be controlled.

The system is built in such a way that it can be supplemented with other controls at any time, or can be adapted to the customer's design.

For a little more customizability as well as more possibilities concerning the security, the whole thing is also available in a version PHP + HTML + MySQL and can then run on own hardware with few changes (https://github.com/KLKG/Casambi_QRCode_PHP).

--------------------------------------------------------------------------------------

## Topics
1. [Used Components](#used-components)
2. [About the project](#about-the-project)

--------------------------------------------------------------------------------------

## Used Components:

Freelancer:<br/>
[startbootstrap](http://startbootstrap.com)<br/>
MIT license

AsyncElegantOTA:<br/>
[GitHub](https://github.com/ayushsharma82/AsyncElegantOTA)<br/>
MIT License

esphome/AsyncTCP:<br/>
[GitHub](https://github.com/esphome/AsyncTCP)<br/>
LGPL-3.0 License

esphome/ESPAsyncWebServer:<br/>
[GitHub](https://github.com/esphome/ESPAsyncWebServer)<br/>

Font Awesome Basic:<br/>
[fontawesome](https://fontawesome.com/)<br/>

--------------------------------------------------------------------------------------

## About the project

We are not web designers and are happy about every hint / help that advances this small project.
Our goal is to give a little food for thought for the possibilities of our gateway.

Feel free to develop the project further. As part of our possibilities, we will also do some fine-tuning.

If you want to get more informations / see an demo just contact us. 

More Informations to ouer Gateway: (https://casambi.lithernet.de)
More Informations to ouer QRCode System: (https://qrcode.lithernet.de)
