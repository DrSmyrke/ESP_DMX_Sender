#include "main.h"



//------------------------- VARIABLES ------------------------------------------
char tmpVal[ 10 ];
char pageBuff[ WEB_PAGE_BUFF_SIZE ];

#if defined(ARDUINO_ARCH_ESP8266)
	ESP8266WebServer webServer;
#elif defined(ARDUINO_ARCH_ESP32)
	WebServer webServer;
#endif
AppData appData;
char tempBuff[ 32 ];



//------------------------- FUNCTIONS ------------------------------------------
void setup()
{
	pinMode( LED_BUILTIN, OUTPUT );
	pinMode( D0, OUTPUT );
	digitalWrite( D0, HIGH );	// Transmit mode
	LittleFS.begin();


	delay( 100 );
	IPAddress apIP( 10, 10, 10, 10 );
	bool res = esp::wifi_init( DEVICE_NAME, apIP, apIP, IPAddress( 255, 255, 255, 0 ) );
	if( res ){
		digitalWrite( LED_BUILTIN, LOW );
	}else{
		digitalWrite( LED_BUILTIN, HIGH );
	}


	
	delay( 100 );
	esp::pageBuff = pageBuff;
	esp::addWebServerPages( &webServer, true, true );
	webServer.on( "/", handleRoot );
	webServer.on( "/index.js", handleIndexJS );
	webServer.on( "/index.css", handleIndexCSS );
	webServer.on( "/favicon.ico", handleFavICO );
	webServer.on( "/get", handleGet );
	webServer.on( "/set", HTTP_POST, handleSet );
	webServer.begin();

	delay( 100 );
    ESP8266DMX0.setMaxSlots( DMX_CHANNES );
	ESP8266DMX0.startDualOutput();

	for( uint16_t i = 0; i < DMX_CHANNES; i++){
		appData.channels[ i ] = 0;
		ESP8266DMX0.setSlot( i + 1, appData.channels[ i ] );
	}
}

void loop()
{
	webServer.handleClient();
}
