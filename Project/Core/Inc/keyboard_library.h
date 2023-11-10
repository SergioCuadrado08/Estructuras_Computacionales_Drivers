/*
 * keyboad_library.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Sergio
 */

#ifndef INC_KEYBOARD_LIBRARY_H_
#define INC_KEYBOARD_LIBRARY_H_
#include "main.h"
#include <stdint.h>


void keypad_init (void);

uint8_t  keypad_handler (uint16_t column_to_evaluate);


#endif /* INC_KEYBOARD_LIBRARY_H_ */
