#include <inttypes.h>
/*
	RCReceive.h - Auslesen eine RC Empfängers - Version 0.2
	Copyright (c) 2012 Wilfried Klaas.  All right reserved.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef RCRECEIVE_H_
#define RCRECEIVE_H_


// This switch only has an effect on an ATTinyx5 target.
// This means that timer 1 is used instead of the internal micros.
//#define USE_TIMER_1

// This switch only has an effect on an Arduino Mega (Mega128 or Mega256) target.
// This means that timer 5 is used instead of timer 1.
//#define USE_TIMER_5

// here are the different definitions for the different targets
// The Arduino type can then be queried using #if defined(xxx).
// Possible values:
// _RC_UNO_ : stands for all 328 based Arduinos, i.e. Uno, Duemillanove, Mini, Micro, Nano
// _RC_LEONARDO: stands for all 32U4 based Arduinos, such as Leonardo, or the 32U4 derivatives from other manufacturers
// _RC_MEGA_ : stands for the Arduinos Megas, i.e. based on dme ATMega128 or ATMega256
// _RC_TINY_14_ : stands for the ATTinyx4 series
// _RC_TINY_8_ : stands for the ATTinyx5 series
#if defined(__AVR_ATmega328P__)
#define _RC_UNO_
#endif

#if defined(__AVR_ATmega32U4__)
#define _RC_LEONARDO_
#endif

#if (defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__))
#define _RC_MEGA_
#endif

#if (defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__))
#define _RC_TINY_14_
#endif

#if (defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__))
#define _RC_TINY_8_
#endif



// Constants for RC detection
const uint16_t MIN_RC_VALUE = 900;	// minimum pulse that is still recognized as valid
const uint16_t MAX_RC_VALUE = 2100;	// maximum impulse, which is now recognized as valid
const uint8_t MAX_ERROR_COUNT = 3;

// Buffer memory size
const uint8_t stackSize = 10;


typedef struct  {
	volatile uint16_t stack[stackSize];
	// Running variable of the ring buffer
	uint8_t index;
} sStack;


// The class for the receiver
class RCReceive {
public:
	static void initInt();

	RCReceive();

	// Connect receiver class to pin
	void attach(uint8_t pin);

	// get current average value
	uint8_t getValue();

	// query new value from recipient
	uint8_t poll();

	// Get zero point
	uint8_t getNP();

	// get zero point (in us)
	uint16_t getMSNP();

	// Error status, becomes 1 if more than 3 incorrect pulses have been detected by the receiver.
	uint8_t hasError();

	// Zero point has been determined
	uint8_t hasNP();

	// Output last read value
	unsigned int getLastRCValue();

	// simplification for the interrupt routine
	void handleInterrupt();

	// Assign interrupt operation with internal iterrupt routine
	void attachInt(uint8_t pin);

	// assign your own interrupt routine
	void attachInt(void (*handler)(void));

	// Assign pin and own interrupt routine
	void attachInt(uint8_t pin, void (*handler)(void));

	// solve assigned interrupt routine
	void detachInt();

	// get current average value in us
	uint16_t getMsValue();

	// Map us value into byte value range
	uint8_t mapMsValue(uint16_t value);

protected:
	volatile unsigned int lastValue;
	sStack myStack;
	uint8_t myPin;
	uint8_t nullpoint;
	uint16_t msNullpoint;
	// the lower 4 bits indicate the number of errors, the top bit indicates
	// whether the zero point was determined.
	volatile uint8_t state;
	volatile uint16_t RcTemp;
	bool hasValue;
	bool isIntMode;
	unsigned long lastValueTime;
};


#endif	/* !RCRECEIVE_H_ */
