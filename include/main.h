#ifndef __MAIN_H_
#define __MAIN_H_

//------------------------- INCLUDES -------------------------------------------
#include "http.h"
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <esp_functions.h>
#include <LXESP8266UART0DMX.h>

//------------------------- DEFINES --------------------------------------------
#define DMX_CHANNES							512
#define WEB_PAGE_BUFF_SIZE					2048
#define DEVICE_NAME							"DMX Sender"


//------------------------- STRUCTURES -----------------------------------------
struct AppData{
	uint8_t channels[ DMX_CHANNES ];
};

//------------------------- VARIABLES ------------------------------------------
extern char tmpVal[ 10 ];
extern char pageBuff[ WEB_PAGE_BUFF_SIZE ];

#if defined(ARDUINO_ARCH_ESP8266)
	extern ESP8266WebServer webServer;
#elif defined(ARDUINO_ARCH_ESP32)
	extern WebServer webServer;
#endif
extern AppData appData;

extern char tempBuff[ 32 ];

//------------------------- FUNCTIONS ------------------------------------------


#endif //__MAIN_H_
