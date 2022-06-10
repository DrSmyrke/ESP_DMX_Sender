//-----------------------------------------------------------------------------
var app = {
	"debug": false,
	'saving': false,
	'outChange': false,
};

//-----------------------------------------------------------------------------
function makeHttpObject()
{
	try {return new XMLHttpRequest();}
	catch (error) {}
	try {return new ActiveXObject("Msxml2.XMLHTTP");}
	catch (error) {}
	try {return new ActiveXObject("Microsoft.XMLHTTP");}
	catch (error) {}
	throw new Error("Could not create HTTP request object.");
}

//-----------------------------------------------------------------------------
window.onload = function(){
	if( document.location.pathname == "/" ){
		buildUI();
	}
};



//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function buildUI()
{
	let obj = document.getElementById( 'contentBox' );
	if( obj == undefined ){
		console.error( "contentBox is undefined" );
		return;
	}

	obj.innerHTML = '';

	var request = makeHttpObject();
	request.open( "GET", "/get", true );
	request.send( null );

	request.onreadystatechange = function(){
		if( request.readyState == 4 ){
			if( request.status == 200 ){
				if( app.debug ) console.log( "buildUI >:", request.responseText );
				let dataObject = JSON.parse( request.responseText );

				if( dataObject.hasOwnProperty( "chans" ) ){
					let div			= document.createElement( "div", );
					obj.appendChild( div );
					for( let num in dataObject.chans ){
						let value			= Number( dataObject.chans[ num ] ).toFixed();
						let divCH			= document.createElement( "div", );
						let ch				= Number( num ) + Number( 1 );
						divCH.innerHTML		= '<span>Out' + ch + ':</span> <input type="range" min="0" max="255" step="1" value="' + value + '" oninput="changeChannel( ' + ch + ', this.value );">';
						div.appendChild( divCH );
					}
				}
			}
		}
	};
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function CheckBit( reg, bit ) 
{
	reg = Number( reg ).toFixed();
	bit = Number( bit ).toFixed();
	return ( ( reg & (1<<bit ) ) != 0 ) ? 1 : 0;
}

//-----------------------------------------------------------------------------
function changeChannel( channel = 0, value = 0 )
{
	if( app.debug ) console.log( "changeChannel >:", channel, value, app.outChange );
	channel = Number( channel ).toFixed();
	value = Number( value ).toFixed();

	if( app.outChange ) return;

	if( value > 255 ) value = 255;

	var request = makeHttpObject();
	var sendForm = new FormData();
	request.open( "POST", "/set", true );
	sendForm.append( 'channel', channel );
	sendForm.append( 'value', value );
	app.outChange = true;

	request.onreadystatechange = function(){
		if( request.readyState == 4 ){
			if( request.status == 200 ){
				app.outChange = false;
			}
		}
	};

	request.send( sendForm );
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
