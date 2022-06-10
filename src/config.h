#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#define HOST_NAME		"ilumen_Mst_DMX_"
#define AP_KEY			"12345678"
#define BUTTON_PIN		10

#ifndef __CONFIG_H
#define __CONFIG_H



IPAddress	apIP( 10, 10, 10, 10 );
IPAddress	apGW( 0, 0, 0, 0 );
IPAddress	apMASK( 255, 255, 255, 0 );

struct MyConf{
	char deviceName[ 32 ];
	char apPass[ 16 ];
	uint16_t address;
};

MyConf conf;

ESP8266WebServer AP_webServer( 80 );

#endif // __CONFIG_H
