/* File: main.cpp
 * Contains base main function and usually all the other stuff that avr does...
 */
/* Copyright (c) 2012-2013 Domen Ipavec (domen.ipavec@z-v.si)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//#include <util/delay.h>

#include <avr/io.h>
//#include <avr/interrupt.h>
//#include <avr/pgmspace.h>
//#include <avr/eeprom.h> 

#include <stdint.h>

#include "bitop.h"

int main() {
	// init
	
    SETBIT(TCCR0A, COM0A1);
    SETBIT(TCCR0A, WGM01);
    SETBIT(TCCR0A, WGM00);
    SETBIT(TCCR0B, CS00);
    
    SETBIT(DDRB, PB2);
	
	// enable interrupts
	//sei();

    uint16_t value = 0;


	for (;;) {
        value = 0;
        while(!BITSET(PINA, PA0));
        while(BITSET(PINA, PA0)) {
            value++;
        }
        if (value < 200) {
            CLEARBIT(DDRB, PB2);
            CLEARBIT(PORTB, PB2);
            value = 0;
        } else {
            SETBIT(DDRB, PB2);
            value -= 200;
        }
        OCR0A = value;
    }
}
