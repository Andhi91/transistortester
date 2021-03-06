/*
 * pin_defs.h
 * optiboot helper defining the default pin assignments (LED, SOFT_UART)
 * for the various chips that are supported.  This also has some ugly macros
 * for selecting among various UARTs and LED possibilities using command-line
 * defines like "UART=2 LED=B5"
 *
 * reorganized 2016 by K.-H. Kuebbeler
 * UART_TX and UART_RX can be selected with the LED style  (D0 or B5)
 * Copyright 2013-2015 by Bill Westfield.
 * Copyright 2010 by Peter Knight.
 * This software is licensed under version 2 of the Gnu Public Licence.
 * See optiboot.c for details.
 */

#define TEST_OUTPUT 0	/* test output for serial data baud rate check (1) */

#ifndef UART
 #define UART_NR 0		/* predefine 0 as default UART number */
#else
 #define UART_NR UART
#endif

#ifndef SOFT_UART
 #define SOFT_UART 0
#endif

#ifndef LED_START_FLASHES
 #define LED_START_FLASHES 0
#endif

#ifndef DATA_FLASH
 #define DATA_FLASH 0
#endif

#include <avr/io.h>
#include "short_port_codes.h"

/* First make undefined ports equal to n */
#if !defined(LED)
 #define LED n
#endif
#if !defined(UART_RX)
 #warning undefined UART_RX
 #define UART_RX n
#endif
#if !defined(UART_TX)
 #warning undefined UART_TX
 #define UART_TX n
#endif

/*------------------------------------------------------------------------ */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__)
/*------------------------------------------------------------------------ */

 /* Onboard LED is connected to pin PB5 in Arduino NG, Diecimila, and Duemilanove */ 
 #if LED == n
  #warning "LED bit is set to default B5"
  #define LEDX           nB5	/* coded Port B Bit 5 */
 #else
  #define LEDX           LED
 #endif

 /* Default "SOFT" UART Ports for ATmega8/88/168/328 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin D0 as RX"
   #define UART_RXX      nD0
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin D1 as TX"
   #define UART_TXX      nD1
  #else
   #define UART_TXX      UART_TX
  #endif
 #endif		/* SOFT_UART > 0 */
#endif		/* __AVR_ATmega168__  ... */

/* Luminet support */
/*------------------------------------------------------------------------ */
#if defined(__AVR_ATtiny84__)
/*------------------------------------------------------------------------ */
 /* Red LED is connected to pin PA4 */ 
 #if LED == n
   #define LEDX        nA4
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATtiny84 */
 /* Ports for soft UART - left port only for now. TX/RX on PA2/PA3 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #warning "SOFT_UART use Pin A3 as RX"
   #define UART_RXX	nA3
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #warning "SOFT_UART use Pin A2 as TX"
   #define UART_TXX	nA2
  #else
   #define UART_TXX      UART_TX
  #endif
 #endif		/* SOFT_UART > 0 */
#endif	/* __AVR_ATtiny84__ */

/*------------------------------------------------------------------------ */
/* Sanguino support (and other 40pin DIP cpus) */
#if defined(__AVR_ATmega644P__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega32__) || defined(__AVR_ATmega16__)
/*------------------------------------------------------------------------ */
 #if defined(__AVR_ATmega16__) || defined(__AVR_ATMEGA32__)
  /* ATmega16/32 support only one UART */
 #endif
 /* Onboard LED is connected to pin PB0 on Sanguino */ 
 #if LED == n
  #define LEDX         nB0
 #else
  #define LEDX         LED
 #endif

 /* Default "SOFT" UART Ports for ATmega644/1284/32 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #if UART_NR == 0
    #warning "SOFT_UART use Pin D0 as RX for UART 0"
    #define UART_RXX	nD0
   #else
    #warning "SOFT_UART use Pin D2 as RX for UART 1"
    #define UART_RXX	nD2
   #endif
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #if UART_NR == 0
    #warning "SOFT_UART use Pin D1 as TX for UART 0"
    #define UART_TXX	nD1
   #else
    #warning "SOFT_UART use Pin D3 as TX for UART 1"
    #define UART_TXX	nD3
   #endif
  #else
   #define UART_TXX      UART_TX
  #endif
 #endif		/* SOFT_UART > 0 */
#endif		/* __AVR_ATmega644P__  .. */

#if defined(__AVR_ATmega32__)
  #define WDCE		WDTOE
#endif

/*------------------------------------------------------------------------ */
/* Settings for all processors */
/*------------------------------------------------------------------------ */

/* Watchdog settings */
#define WATCHDOG_OFF    (0)
#define WATCHDOG_16MS   (_BV(WDE))
#define WATCHDOG_32MS   (_BV(WDP0) | _BV(WDE))
#define WATCHDOG_64MS   (_BV(WDP1) | _BV(WDE))
#define WATCHDOG_125MS  (_BV(WDP1) | _BV(WDP0) | _BV(WDE))
#define WATCHDOG_250MS  (_BV(WDP2) | _BV(WDE))
#define WATCHDOG_500MS  (_BV(WDP2) | _BV(WDP0) | _BV(WDE))
#define WATCHDOG_1S     (_BV(WDP2) | _BV(WDP1) | _BV(WDE))
#define WATCHDOG_2S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE))
#if defined(WDP3)
 #define WATCHDOG_4S     (_BV(WDP3) | _BV(WDE))
 #define WATCHDOG_8S     (_BV(WDP3) | _BV(WDP0) | _BV(WDE))
#else
 #define WATCHDOG_4S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE)) /* 2 seconds are max */
 #define WATCHDOG_8S     (_BV(WDP2) | _BV(WDP1) | _BV(WDP0) | _BV(WDE)) /* 2 seconds are max */
#endif

#if !defined(UDR0) && defined(UDR)
  //Name conversion R.Wiersma
  // Make the only UART to the UART0
  #define UCSR0A	UCSRA
  #define UCSR0B	UCSRB
  #define UDR0 		UDR
  #define UDRE0 	UDRE
  #define RXC0		RXC
  #define FE0           FE
  #define U2X0		U2X
  #define TIFR1 	TIFR
  #define WDTCSR	WDTCR
  #define RXEN0		RXEN
  #define TXEN0		TXEN
  #define UBRR0L	UBRRL
  #define UBRR0H	UBRRH
#endif		/* __AVR_ATmega8__ */


/*------------------------------------------------------------------------ */
/* Mega support */
#if defined(__AVR_ATmega1280__)
/*------------------------------------------------------------------------ */
 /* Onboard LED is connected to pin PB7 on Arduino Mega1280 */ 
 #if LED == n
  #define LEDX	nB7
 #else
  #define LEDX   LED
 #endif

 /* Default "SOFT" UART Ports for ATmega1280 */
 #if SOFT_UART > 0
  #if UART_RX == n
   #if UART_NR == 0
    #warning "ATmega use Pin E0 as RX for soft UART 0"
    #define UART_RXX	nE0
   #endif
   #if UART_NR == 1
    #warning "ATmega use Pin D2 as RX for soft UART 1"
    #define UART_RXX	nD2
   #endif
   #if UART_NR == 2
    #warning "ATmega use Pin H0 as RX for soft UART 2"
    #define UART_RXX	nH0
   #endif
   #if UART_NR == 3
    #warning "ATmega use Pin J0 as RX for soft UART 3"
    #define UART_RXX	nJ0
   #endif
  #else
   #define UART_RXX      UART_RX
  #endif
  #if UART_TX == n
   #if UART_NR == 0
    #warning "ATmega use Pin E1 as TX for soft UART 0"
    #define UART_TXX	nE1
   #endif
   #if UART_NR == 1
    #warning "ATmega use Pin D3 as TX for soft UART 1"
    #define UART_TXX	nD3
   #endif
   #if UART_NR == 2
    #warning "ATmega use Pin H1 as TX for soft UART 2"
    #define UART_TXX	nH1
   #endif
   #if UART_NR == 3
    #warning "ATmega use Pin J1 as TX for soft UART 3"
    #define UART_TXX	nJ1
   #endif
  #else
   #define UART_TXX      UART_TX
  #endif
 #endif		/* SOFT_UART > 0 */
#endif		/* __AVR_ATmega1280__ */


// The Preprocessor should have replaced LEDX with a constant now
#if (LEDX & 0xff) > 7
 #error "Unrecognized LED name. Should be like 'B5' "
 #error "probably the bit number is wrong!"
#endif
#if ((LEDX >> 8) > 12) || ((LEDX & 0xff00) == 0)
 #error "Unrecognized LED name.  Should be like 'B5' "
 #error "probably the port is wrong!"
#endif

// LEDbit must be set to the bit number of the selected Port.
// This is allways given by the lower Byte of the previous definition
#define LEDbit (LEDX & 0x07)

// setup for UART_RX
#if SOFT_UART > 0
 #if ((UART_RXX & 0xff) > 7) || ((UART_RXX >> 8) > 12) || ((UART_RXX & 0xff00) == 0)
  #error "Unrecognized UART_RX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // setup for UART_TX
 #if ((UART_TXX & 0xff) > 7) || ((UART_TXX >> 8) > 12) || ((UART_TXX & 0xff00) == 0)
  #error "Unrecognized UART_TX name.  Should be like 'B5'"
  #error "You can only select a existing port for the target processor!"
 #endif
 // UART_RX_BIT must be set to the bit number of the selected Port.
 // This is allways given by the lower Byte of the previous definition
 #define UART_RX_BIT (UART_RXX & 0x07)
 // the same must be set for the TX_BIT
 #define UART_TX_BIT (UART_TXX & 0x07)
#else		/* Hardware UART */
 /*
  * Handle devices with up to 4 uarts (eg m1280.)  Rather inelegantly.
  * Note that mega8/m32 still needs special handling, because ubrr is handled
  * differently.
  */
 #if UART_NR == 0
  #if !defined(UDR0)
   #error "UART == 0, but no UART0 on device"
  #endif
  #define UART_SRA UCSR0A
  #define UART_SRB UCSR0B
  #define UART_SRC UCSR0C
  #define UART_SRRL UBRR0L
  #define UART_SRRH UBRR0H
  #define UART_UDR UDR0
 #elif UART_NR == 1
  #if !defined(UDR1)
   #error "UART == 1, but no UART1 on device"
  #endif
  #define UART_SRA UCSR1A
  #define UART_SRB UCSR1B
  #define UART_SRC UCSR1C
  #define UART_SRRL UBRR1L
  #define UART_SRRH UBRR1H
  #define UART_UDR UDR1
 #elif UART_NR == 2
  #if !defined(UDR2)
   #error "UART == 2, but no UART2 on device"
  #endif
  #define UART_SRA UCSR2A
  #define UART_SRB UCSR2B
  #define UART_SRC UCSR2C
  #define UART_SRRL UBRR2L
  #define UART_SRRH UBRR2H
  #define UART_UDR UDR2
 #elif UART_NR == 3
  #if !defined(UDR3)
   #error "UART == 3, but no UART3 on device"
  #endif
  #define UART_SRA UCSR3A
  #define UART_SRB UCSR3B
  #define UART_SRC UCSR3C
  #define UART_SRRL UBRR3L
  #define UART_SRRH UBRR3H
  #define UART_UDR UDR3
 #else
  #error "Unknown UART number, only 0 to 3 !!!"
 #endif

#endif		/* SOFT_UART > 0 */

// setup the Port definitions for LED
#if (LEDX & 0xff00) == nB0
 #define LED_DDR     DDRB
 #define LED_PORT    PORTB
 #define LED_PIN     PINB
#elif (LEDX & 0xff00) == nC0
 #define LED_DDR     DDRC
 #define LED_PORT    PORTC
 #define LED_PIN     PINC
#elif (LEDX & 0xff00) == nD0
 #define LED_DDR     DDRD
 #define LED_PORT    PORTD
 #define LED_PIN     PIND
#elif (LEDX & 0xff00) == nE0
 #define LED_DDR     DDRE
 #define LED_PORT    PORTE
 #define LED_PIN     PINE
#elif (LEDX & 0xff00) == nF0
 #define LED_DDR     DDRF
 #define LED_PORT    PORTF
 #define LED_PIN     PINF
#elif (LEDX & 0xff00) == nG0
 #define LED_DDR     DDRG
 #define LED_PORT    PORTG
 #define LED_PIN     PING
#elif (LEDX & 0xff00) == nH0
 #define LED_DDR     DDRH
 #define LED_PORT    PORTH
 #define LED_PIN     PINH
#elif (LEDX & 0xff00) == nJ0
 #define LED_DDR     DDRJ
 #define LED_PORT    PORTJ
 #define LED_PIN     PINJ
#elif (LEDX & 0xff00) == nK0
 #define LED_DDR     DDRK
 #define LED_PORT    PORTK
 #define LED_PIN     PINK
#elif (LEDX & 0xff00) == nL0
 #define LED_DDR     DDRL
 #define LED_PORT    PORTL
 #define LED_PIN     PINL
#elif (LEDX & 0xff00) == nA0
 #define LED_DDR     DDRA
 #define LED_PORT    PORTA
 #define LED_PIN     PINA

#else
 #error "--------------------------------------------"
 #error "Unrecognized LED name.  Should be like 'B4' "
 #error "--------------------------------------------"
#endif

#if SOFT_UART > 0
 // setup the Port definitions for UART_RX
 #if (UART_RXX & 0xff00) == nB0
  #define UART_RX_DDR     DDRB
  #define UART_RX_PORT    PORTB
  #define UART_RX_PIN     PINB
 #elif (UART_RXX & 0xff00) == nC0
  #define UART_RX_DDR     DDRC
  #define UART_RX_PORT    PORTC
  #define UART_RX_PIN     PINC
 #elif (UART_RXX & 0xff00) == nD0
  #define UART_RX_DDR     DDRD
  #define UART_RX_PORT    PORTD
  #define UART_RX_PIN     PIND
 #elif (UART_RXX & 0xff00) == nE0
  #define UART_RX_DDR     DDRE
  #define UART_RX_PORT    PORTE
  #define UART_RX_PIN     PINE
 #elif (UART_RXX & 0xff00) == nF0
  #define UART_RX_DDR     DDRF
  #define UART_RX_PORT    PORTF
  #define UART_RX_PIN     PINF
 #elif (UART_RXX & 0xff00) == nG0
  #define UART_RX_DDR     DDRG
  #define UART_RX_PORT    PORTG
  #define UART_RX_PIN     PING
 #elif (UART_RXX & 0xff00) == nH0
  #define UART_RX_DDR     DDRH
  #define UART_RX_PORT    PORTH
  #define UART_RX_PIN     PINH
 #elif (UART_RXX & 0xff00) == nJ0
  #define UART_RX_DDR     DDRJ
  #define UART_RX_PORT    PORTJ
  #define UART_RX_PIN     PINJ
 #elif (UART_RXX & 0xff00) == nK0
  #define UART_RX_DDR     DDRK
  #define UART_RX_PORT    PORTK
  #define UART_RX_PIN     PINK
 #elif (UART_RXX & 0xff00) == nL0
  #define UART_RX_DDR     DDRL
  #define UART_RX_PORT    PORTL
  #define UART_RX_PIN     PINL
 #elif (UART_RXX & 0xff00) == nA0
  #define UART_RX_DDR     DDRA
  #define UART_RX_PORT    PORTA
  #define UART_RX_PIN     PINA
 
 #else
  #error -------------------------------------------
  #error Unrecognized UART_RX name.  Should be like "B5"
  #error -------------------------------------------
 #endif
#endif 		/* SOFT_UART > 0 */


#if SOFT_UART > 0
 // setup the Port definitions for UART_TX
 #if (UART_TXX & 0xff00) == nB0
  #define UART_TX_DDR     DDRB
  #define UART_TX_PORT    PORTB
  #define UART_TX_PIN     PINB
 #elif (UART_TXX & 0xff00) == nC0
  #define UART_TX_DDR     DDRC
  #define UART_TX_PORT    PORTC
  #define UART_TX_PIN     PINC
 #elif (UART_TXX & 0xff00) == nD0
  #define UART_TX_DDR     DDRD
  #define UART_TX_PORT    PORTD
  #define UART_TX_PIN     PIND
 #elif (UART_TXX & 0xff00) == nE0
  #define UART_TX_DDR     DDRE
  #define UART_TX_PORT    PORTE
  #define UART_TX_PIN     PINE
 #elif (UART_TXX & 0xff00) == nF0
  #define UART_TX_DDR     DDRF
  #define UART_TX_PORT    PORTF
  #define UART_TX_PIN     PINF
 #elif (UART_TXX & 0xff00) == nG0
  #define UART_TX_DDR     DDRG
  #define UART_TX_PORT    PORTG
  #define UART_TX_PIN     PING
 #elif (UART_TXX & 0xff00) == nH0
  #define UART_TX_DDR     DDRH
  #define UART_TX_PORT    PORTH
  #define UART_TX_PIN     PINH
 #elif (UART_TXX & 0xff00) == nJ0
  #define UART_TX_DDR     DDRJ
  #define UART_TX_PORT    PORTJ
  #define UART_TX_PIN     PINJ
 #elif (UART_TXX & 0xff00) == nK0
  #define UART_TX_DDR     DDRK
  #define UART_TX_PORT    PORTK
  #define UART_TX_PIN     PINK
 #elif (UART_TXX & 0xff00) == nL0
  #define UART_TX_DDR     DDRL
  #define UART_TX_PORT    PORTL
  #define UART_TX_PIN     PINL
 #elif (UART_TXX & 0xff00) == nA0
  #define UART_TX_DDR     DDRA
  #define UART_TX_PORT    PORTA
  #define UART_TX_PIN     PINA
 
 #else
  #error -------------------------------------------
  #error Unrecognized UART_TX name.  Should be like "B5"
  #error -------------------------------------------
 #endif
#endif 		/* SOFT_UART > 0 */

// setup some Macros for Assembly language use to simplify the port access
#ifdef __ASSEMBLER__

/* define AOUT macro */
/* AOUT select automatically the right instruction "out" or "sts" depending on argument. */
	.macro	AOUT adr, reg
	.if	_SFR_IO_REG_P(\adr)
	out	_SFR_IO_ADDR(\adr), \reg
	.else
	sts	_SFR_MEM_ADDR(\adr), \reg
	.endif
	.endm
/* define AIN macro */
/* AIN select automatically the right instruction "in" or "lds" depending on argument. */
	.macro	AIN reg, adr
	.if	_SFR_IO_REG_P(\adr)
	in	\reg, _SFR_IO_ADDR(\adr)
	.else
	lds	\reg, _SFR_MEM_ADDR(\adr)
	.endif
	.endm
/* define ASBIC macro */
/* AIN select automatically the right instruction "sbic" or "lds; sbrc" depending on argument. */
	.macro	ASBIC adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbic	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r0, _SFR_MEM_ADDR(\adr)
	sbrc	r0, \bit
	.endif
	.endm
/* define ASBIS macro */
/* AIN select automatically the right instruction "sbis" or "lds; sbrs" depending on argument. */
	.macro	ASBIS adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbis	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r0, _SFR_MEM_ADDR(\adr)
	sbrs	r0, \bit
	.endif
	.endm
/* define ASBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; sbr; sts" depending on argument. */
	.macro	ASBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	sbi	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r25, _SFR_MEM_ADDR(\adr)
	sbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	.endif
	.endm
/* define ACBI macro */
/* AIN select automatically the right instruction "sbi" or "lds; cbr; sts" depending on argument. */
	.macro	ACBI adr, bit
	.if	((\adr) < 0x20 + __SFR_OFFSET)
	cbi	_SFR_IO_ADDR(\adr), \bit
	.else
	lds	r25, _SFR_MEM_ADDR(\adr)
	cbr	r25, \bit
	sts	_SFR_MEM_ADDR(\adr), r25
	.endif
	.endm
#endif
