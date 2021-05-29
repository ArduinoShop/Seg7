#include "Seg7.h"

Seg7::Seg7( uint8_t b, uint8_t CSpin, uint8_t DINpin, uint8_t CLKpin, uint8_t digs )	{ // Constructor / init

CS = CSpin;  DIN = DINpin;  CLK = CLKpin;

  pinMode( DINpin, OUTPUT);
  pinMode( CSpin,  OUTPUT);
  pinMode( CLKpin, OUTPUT);
  digitalWrite( CSpin, HIGH);

  output(DisplayTEST_REG, 0x0);  //  TEST mode - all OFF
  output(ShutDown_REG,    0x1);  //  Clear
  output(BrightNESS_REG,   b );  //  Brightness
  output(DecodeMODE_REG,  0xFF); //  all digits to BCD mode
  output(ScanlIMIT_REG,   digs-1); //  Display all digits
  
  clear();

}

void Seg7::seq( const char *stg, uint8_t dly, uint8_t p, bool clr ) {
  byte x = 0;
#ifdef DEBUG  
  printf("stg = %s, p = %d, clr = %d\n", stg, p, clr );
#endif  
  if( clr ) { clear( ); }
  while( stg[x] ) {
#ifdef DEBUG	  
    printf("stg[%d] = 0x%X\n", x, stg[x] & 0xF );
#endif    
    output( 8-p-x, (stg[x]&0x40) ? stg[x]|0x80 : stg[x]&0xF );
    DELAY( dly * 100 );
		x++;
				}
	}

void Seg7::stg( const char *stg, uint8_t p, bool clr ) {
  uint8_t x = 0, dc = 0xFF;
#ifdef DEBUG
  printf("stg = %s, p = %d, clr = %d\n", stg, p, clr );
#endif  
  if( clr ) { clear( ); output(DecodeMODE_REG, 0xFF ); }
  while( stg[x] && x<8-p ) {
	  if( ( stg[x] & 0x60 ) == 0x60 ) { output( 8-p-x, stg[x] | 0x80); }
	  if( ( stg[x] & 0x60 ) == 0x40 ) {
		  dc &= ~( 0x80>>(x+p)); output(DecodeMODE_REG, dc ); output( 8-p-x, Seg7font[ stg[x] & 0x1F ] ); } 
      if( ( stg[x] & 0x60 ) == 0x20 ) { output( 8-p-x, stg[x] ); }
#ifdef DEBUG
    printf("stg[%d] = 0x%X, && = 0x%X, ~BV = 0x%X\n", x, stg[x], ( stg[x] & 0x60 ), ~( 0x80>>x ) );
#endif    
    if( x < 8-p ) x++;
				}
	}

void Seg7::num( uint32_t nm, uint8_t p, bool clr )  {
  output(DecodeMODE_REG, 0xFF );
  uint8_t x = 0;
  char    stg[12];
  sprintf( stg, "%d", nm );
#ifdef DEBUG
  printf("num = %d, stg = %s, p = %d, clr = %d\n", nm, stg, p, clr );
#endif
  if( clr ) { clear( ); }
  while( stg[x] && x<8-p ) {
	if( stg[x] == 0x2D ) { stg[x] = 'J'; }
#ifdef DEBUG	
    printf("stg[%d] = 0x%d\n", x, stg[x] & 0xF );
#endif    
    output( 8-p-x, (stg[x]&0x60) ? stg[x]&0xF : stg[x]|0x80 );
    if( x < 8-p ) x++;
				}
	}
	
void Seg7::hex( uint32_t nm, uint8_t p, bool clr )  {
  uint8_t x = 0, dc = 0xFF;
  output(DecodeMODE_REG, 0xFF );
  char    stg[12];
  sprintf( stg, "%X", nm );
#ifdef DEBUG
  printf("nm = %X, stg = %s, p = %d, clr = %d\n", nm, stg, p, clr );
#endif  
  if( clr ) { clear( ); }
  while( stg[x] && x<8-p ) {
		  if( ( stg[x] & 0x60 ) == 0x40 ) {
		  dc &= ~( 0x80>>x+p); output(DecodeMODE_REG, dc ); output( 8-p-x, Seg7font[ stg[x] & 0x1F ] ); }
		  else { output( 8-p-x, stg[x]&0xF ); }
#ifdef DEBUG		   
    printf("stg[%d] = 0x%X\n", x, stg[x] );
#endif   
    if( x < 8-p ) x++;
				}
	}
	
int  Seg7::setchar( char in, uint8_t out ) {
	if( ( in < 0x40 ) || ( in > 0x5f ) ) { printf("Invalid Character %c : must be between @ and ~\n", in ); return 1; }
	Seg7font[ in - 0x40 ] = out;
#ifdef DEBUG	
		printf("char %c set to 0x%X\n", in, Seg7font[ in - 0x40 ] );
#endif		
							}	
	
void Seg7::clear( uint8_t p ) {
#ifdef DEBUG
	 printf("Clearing from %d\n", p );
#endif
	int x;
	output(DecodeMODE_REG, 0xFF );
	for( x=8-p; x>0; x-- ) { output( x, 0xF ); }
		}

void Seg7::brightness( uint8_t b ) {
	output( BrightNESS_REG, b );
								}
	
void Seg7::output(byte address, byte data) {
#ifdef DEBUG
  printf( "output 0x%X, 0x%X\n", address, data );
#endif
  digitalWrite( getCS(), LOW);
  shiftOut( getDIN(), getCLK(), MSBFIRST, address);
  shiftOut( getDIN(), getCLK(), MSBFIRST, data);
  digitalWrite( getCS(), HIGH);
}

uint8_t Seg7::getCS(  void ) { return CS;  }
uint8_t Seg7::getDIN( void ) { return DIN; }
uint8_t Seg7::getCLK( void ) { return CLK; }
	
	
