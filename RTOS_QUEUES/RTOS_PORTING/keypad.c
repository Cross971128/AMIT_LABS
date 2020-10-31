/*
 * keypad.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Joseph Hanna
 */


#include "keypad.h"

/***** Function Prototypes for keypad internal (private) functions *****/

/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number);


/************************** Functions Definitions **********************/
unsigned char KeyPad_getPressedKey(void){
	unsigned char col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/*
			 * each time only one of the column pins will be output and
			 * the rest will be input pins include the row pins
			 */
			DDRA = (0b00010000<<col);
			/*
			 * clear the output pin column in this trace and enable the internal
			 * pull up resistors for the rows pins
			 */
			PORTA = (~(0b00010000<<col)); //11101111

			for(row=0;row<N_row;row++) /* loop for rows */
			{
				if(!(PINA & (1<<row))) /* if the switch is press in this row */
				{
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
				}
			}
		}
	}
}


static unsigned char KeyPad_4x3_adjustKeyNumber(unsigned char button_number)
{
	switch(button_number)
	{
		case 10: return '*';
				 break;
		case 11: return 0;
				 break;
		case 12: return '#';
				 break;
		default: return button_number;
	}
}

