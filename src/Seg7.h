#ifndef __Seg_7_H__
#define __Seg_7_H__

#include <inttypes.h>
#include <Arduino.h>

#define DELAY( x ) delay( x )
#define BD_FAMILY " !! UNKNOWN BOARD !! "
 	
#ifdef ESP32
	#define MAX7219_DIN	18
	#define MAX7219_CS	23
	#define MAX7219_CLK	5
	#define BD_FAMILY "ESP32"
	#define DELAY( x ) vTaskDelay( x )
#endif

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined( LGT8F328 )
	#define MAX7219_DIN	11
	#define MAX7219_CS	10
	#define MAX7219_CLK	13
	#define BD_FAMILY "ATmega328/168/LGT8F328"

#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	#define MAX7219_DIN	51
	#define MAX7219_CS	53
	#define MAX7219_CLK	52
	#define BD_FAMILY "ATmega2560 / ATmega1280"
#endif

#ifdef ESP8266
	#define MAX7219_DIN	13 	// D7
	#define MAX7219_CS	15  // D8
	#define MAX7219_CLK	14  // D5                                                                                                                                                                         
	#define BD_FAMILY "ESP8266"
#endif

#define DecodeMODE_REG	0x09
#define BrightNESS_REG	0x0A
#define ScanlIMIT_REG	0x0B
#define ShutDown_REG	0x0C
#define DisplayTEST_REG	0x0F

// #define DEBUG  //  uncomment to see Debug Output in the Serial Monitor
	
class Seg7 {

public:

	Seg7( uint8_t brt, uint8_t CS = MAX7219_CS, uint8_t DIN = MAX7219_DIN, uint8_t CLK = MAX7219_CLK, uint8_t digs = 8 );
	void stg( const char *stg, uint8_t off = 0, bool clr = true  );
	void seq( const char *stg, uint8_t dly = 4, uint8_t off = 0, bool clr = true );
	void num( uint32_t nm, uint8_t off = 0, bool clr = true );
	void hex( uint32_t nm, uint8_t off = 0, bool clr = true );
	void clear( uint8_t off = 0 );
	void brightness( uint8_t b = 2 );
	uint8_t getCS( void );
	uint8_t getDIN( void );
	uint8_t getCLK( void );
	int  setchar( char in, uint8_t out );
	
	
private:
	void output( uint8_t adr, uint8_t data );
	uint8_t Seg7font[32] = { 0xBB, 0x77, 0x1F, 0x4E, 0x3D, 0x4F, 0x47,1,2,4,8,16,32,64,128 };
	uint8_t CS, DIN, CLK;
};	//  end of Seg 7 class

#endif
