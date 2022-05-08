#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

#include "rom.h"

// Pin Definitions.
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7
#define A8 8
#define A9 9
#define A10 10
#define A11 11
#define A12 12
#define A13 13
#define A14 14
#define A15 15
#define A16 16
#define D0 27
#define D1 26
#define D2 22
#define D3 21
#define D4 20
#define D5 19
#define D6 18
#define D7 17
#define NWR 28

#define DATAOFFSETLOW 17
#define DATAOFFSETHIGH 20

// Bit masks
#define DATAMASK 0b01100011111100000000000000000
#define READMASK 0b10000000000000000000000000000

void initGPIO() {
  // Set pin directions.
  gpio_init( A0 );
  gpio_set_dir( A0, GPIO_IN );
  gpio_init( A1 );
  gpio_set_dir( A1, GPIO_IN );
  gpio_init( A2 );
  gpio_set_dir( A2, GPIO_IN );
  gpio_init( A3 );
  gpio_set_dir( A3, GPIO_IN );
  gpio_init( A4 );
  gpio_set_dir( A4, GPIO_IN );
  gpio_init( A5 );
  gpio_set_dir( A5, GPIO_IN );
  gpio_init( A6 );
  gpio_set_dir( A6, GPIO_IN );
  gpio_init( A7 );
  gpio_set_dir( A7, GPIO_IN );
  gpio_init( A8 );
  gpio_set_dir( A8, GPIO_IN );
  gpio_init( A9 );
  gpio_set_dir( A9, GPIO_IN );
  gpio_init( A10 );
  gpio_set_dir( A10, GPIO_IN );
  gpio_init( A11 );
  gpio_set_dir( A11, GPIO_IN );
  gpio_init( A12 );
  gpio_set_dir( A12, GPIO_IN );
  gpio_init( A13 );
  gpio_set_dir( A13, GPIO_IN );
  gpio_init( A14 );
  gpio_set_dir( A14, GPIO_IN );
  gpio_init( A15 );
  gpio_set_dir( A15, GPIO_IN );
  gpio_init( A16 );
  gpio_set_dir( A16, GPIO_IN );
  
  gpio_init( NWR );
  gpio_set_dir( NWR, GPIO_IN );

  // Initially, set the pins to IN
  gpio_init( D0 );
  gpio_set_dir( D0, GPIO_IN );
  gpio_init( D1 );
  gpio_set_dir( D1, GPIO_IN );
  gpio_init( D2 );
  gpio_set_dir( D2, GPIO_IN );
  gpio_init( D3 );
  gpio_set_dir( D3, GPIO_IN );
  gpio_init( D4 );
  gpio_set_dir( D4, GPIO_IN );
  gpio_init( D5 );
  gpio_set_dir( D5, GPIO_IN );
  gpio_init( D6 );
  gpio_set_dir( D6, GPIO_IN );
  gpio_init( D7 );
  gpio_set_dir( D7, GPIO_IN );
  
}

int main() {
  set_sys_clock_khz(250000, false);
  
  initGPIO();
  
  // Read.
  while ( 1 ) {
    unsigned int data = gpio_get_all();
    unsigned int oe = !( data & READMASK );
    (oe ? gpio_set_dir_out_masked( DATAMASK ) : gpio_set_dir_in_masked( DATAMASK ) );
    
    unsigned int address = data & ADDRMASK;
    uint8_t romByte = rom[ address ];
    unsigned int gpioByte = ( ( romByte & 0b00111111 ) << DATAOFFSETLOW ) |
						  ( ( romByte & 0b11000000 ) << DATAOFFSETHIGH );
				 
    gpio_put_all( gpioByte );
  }
  
  return 0;
}
