#include "http.h"
#include "main.h"

//-------------------------------------------------------------------------------
void handleRoot(void)
{
	esp::webSendFile( &webServer, "/index.html", "text/html" );
}

//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void handleGet(void)
{
	esp::setNoCacheContent( &webServer );

	strcpy( pageBuff, "{" );
	//-------------------------------------------------------------
	// strcat( pageBuff, "\"addr\": " ); utoa( conf.address, tmpVal, 10 ); strcat( pageBuff, tmpVal );
	strcat( pageBuff, "\"chans\": [" );

		for( uint16_t i = 0; i < DMX_CHANNES; i++){
			if( i > 0 ) strcat( pageBuff, ", " );

			utoa( appData.channels[ i ], tmpVal, 10 ); strcat( pageBuff, tmpVal );
			// strcat( pageBuff, "\"" ); utoa( i + 1, tmpVal, 10 ); strcat( pageBuff, tmpVal );
			// strcat( pageBuff, "\": " ); utoa( appData.channels[ i ], tmpVal, 10 ); strcat( pageBuff, tmpVal );
		}
	strcat( pageBuff, "]" );
	//-------------------------------------------------------------
	strcat( pageBuff, "}" );
	webServer.send ( 200, "text/html", pageBuff );
}

//-------------------------------------------------------------------------------
void handleSet(void)
{
//	if( !AuthCheck() ){
//		return;
//	}
	esp::setNoCacheContent( &webServer );
	//-------------------------------------------------------------
	if( webServer.hasArg( "reboot" ) ){
		webServer.send ( 200, "text/html", "OK" );
		ESP.restart();
		return;
	}else if( webServer.hasArg( "channel" ) && webServer.hasArg( "value" ) ){
		uint8_t value = webServer.arg( "value" ).toInt();
		uint16_t channel = webServer.arg( "channel" ).toInt();
		if( value > 255 ) value = 255;
		if( channel > DMX_CHANNES ) value = DMX_CHANNES;
		appData.channels[ channel - 1 ] = value;
		ESP8266DMX0.setSlot( channel + 1, value );
	}
	//-------------------------------------------------------------
	webServer.send ( 200, "text/html", "OK" );
}

//-------------------------------------------------------------------------------
