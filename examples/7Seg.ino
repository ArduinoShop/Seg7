#include <Seg7.h>

/*********** Seg7 Library for 7 Segmenet Displays ***********/
/*********** using the MAX 7219 controller chip   ***********/
/*********** Compatible with UNO, ESP8266, ESP32, etc.*******/
/*********** See https://github.com/ArduinoShop   ***********/

/**** Instantiate the Seg7 class as variable dsp  ************/
/**** dsp( brightness, [ CS pin ], [ DIN pin ], [ CLK pin ] ); 
 **** brightness may be 0 - 15                    ************/
/**** Default pins correspond to the default SPI pins ********/

Seg7 dsp( 2 ); // Invoke class with brightness at 2 and # of didgits at 8

void setup() {

Serial.begin( 115200 );

#ifndef BD_FAMILY
 #define BD_FAMILY "UNKNOWN"
#endif
Serial.print("\n7 Segment "); Serial.print( BD_FAMILY ); Serial.println(" Demo.");
Serial.print( "CS on pin " ); Serial.print( dsp.getCS() );
Serial.print( " : DIN -> ");  Serial.print( dsp.getDIN() );
Serial.print( " : CLK -> ");  Serial.println( dsp.getCLK() );

Serial.println("\nDisplay a string offset by 1 digit\n");
 dsp.stg( "4A6D69", 1 );
 DELAY( 3000 );

Serial.println("Display a number - no offset\n");
 dsp.num( -84254 );
 DELAY( 3000 );

Serial.println("Display a HEX number offset by 2\n");
 dsp.hex( 0x82ACE, 2 );
 DELAY( 3000 );

Serial.println("Display Sequenced String delay = 5, offset by 2\n");
 dsp.seq( "12c45", 5, 2 );
 DELAY( 3000 );
Serial.println("Set up some Custom Characters\n");
 dsp.setchar( 'V', 0x19 );
 dsp.setchar( 'W', 0x61 );
 dsp.setchar( 'X', 0x78 );
 dsp.setchar( 'Y', 0x0D );
 dsp.setchar( 'Z', 0x43 );
 dsp.setchar( '[', 0x4E );

Serial.println("Endless Loop using the Custom Characters");

Serial.println("using stg and changing brightness\n");
}

void loop() {
 
int x;  
for( x=0; x<1; x++ ) {
  dsp.clear(); DELAY( 800 );

  dsp.brightness( 0 );
  dsp.stg("??V",0,0); DELAY( 200 );
  dsp.brightness( 5 );
  dsp.stg("?WV",0,0); DELAY( 400 );
  dsp.brightness( 10 );
  dsp.stg("XWV",0,0); DELAY( 600 );
}

for( x=0; x<1; x++ ) {
  dsp.clear(); DELAY( 800 );
  dsp.brightness( 0 );
  dsp.stg("Y??",5,0); DELAY( 200 );
  dsp.brightness( 7 );
  dsp.stg("YZ?",5,0); DELAY( 400 );
  dsp.brightness( 14 );
  dsp.stg("YZ[",5,0); DELAY( 600 );
          }
}
