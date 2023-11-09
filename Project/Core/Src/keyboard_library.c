/*
 * keyboard_libary.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Sergio
 */

#include "keyboard_library.h"
#include "main.h"
#include "ring_buffer.h"
/**
 * Initialize the keypad.
 * Sets the rows to a high state for column detection using interrupts.
 */

void keypad_init(void)
{
	/* Set the rows high to be detected in the columns by rising interrupt */
	ROW_1_GPIO_Port->BSRR = ROW_1_Pin;
	ROW_2_GPIO_Port->BSRR = ROW_2_Pin;
	ROW_3_GPIO_Port->BSRR = ROW_3_Pin;
	ROW_4_GPIO_Port->BSRR = ROW_4_Pin;
}
/**
 * Handle the keypad events and detect key presses based on the column being evaluated.
 * @param column_to_evaluate The column to be evaluated for key press detection.
 * @return The value of the pressed key.
 */
uint8_t keypad_handler (uint16_t column_to_evaluate)
{
	uint16_t key_pressed = 0xFF;


#define KEY_DEBOUNCE_MS 300 /*!> Minimum time required for since last press */
	static uint32_t last_pressed_tick = 0;
	if (HAL_GetTick() <= (last_pressed_tick + KEY_DEBOUNCE_MS)) {
		// less than KEY_DEBOUNCE_MS since last press. Probably noise
		return key_pressed; // return 0xFF
	}
	last_pressed_tick = HAL_GetTick();

		switch (column_to_evaluate)	{
		case COLUMN_1_Pin:
			ROW_1_GPIO_Port ->BSRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed = 0x01;

			ROW_1_GPIO_Port ->BRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BSRR = ROW_2_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed = 0x04;

			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BSRR = ROW_3_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed = 0x07;

			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BSRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_1_GPIO_Port->IDR & COLUMN_1_Pin) key_pressed = 0x0E;
			break;


		case COLUMN_2_Pin:
			ROW_1_GPIO_Port ->BSRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed = 0x02;

			ROW_1_GPIO_Port ->BRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BSRR = ROW_2_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed = 0x05;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BSRR = ROW_3_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed = 0x08;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BSRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_2_GPIO_Port->IDR & COLUMN_2_Pin) key_pressed = 0x00;
			break;

		case COLUMN_3_Pin:
			ROW_1_GPIO_Port ->BSRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin) key_pressed = 0x03;

			ROW_1_GPIO_Port ->BRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BSRR = ROW_2_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin) key_pressed = 0x06;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BSRR = ROW_3_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin) key_pressed = 0x09;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BSRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_3_GPIO_Port->IDR & COLUMN_3_Pin) key_pressed = 0x0F;
			break;
		case COLUMN_4_Pin:
			ROW_1_GPIO_Port ->BSRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed = 0x0A;

			ROW_1_GPIO_Port ->BRR = ROW_1_Pin;
			ROW_2_GPIO_Port ->BSRR = ROW_2_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed = 0x0B;
			ROW_2_GPIO_Port ->BRR = ROW_2_Pin;
			ROW_3_GPIO_Port ->BSRR = ROW_3_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed = 0x0C;
			ROW_3_GPIO_Port ->BRR = ROW_3_Pin;
			ROW_4_GPIO_Port ->BSRR = ROW_4_Pin;
			HAL_Delay(2); // wait for voltage to establish
			if (COLUMN_4_GPIO_Port->IDR & COLUMN_4_Pin) key_pressed = 0x0D;
			break;
		default:
			break;
		}
		keypad_init();
		return key_pressed;
}

/**
 * Check for keypad events triggered by the key_event received.
 * Print the key pressed if any key is detected.
 * @param key_event The event triggered by the keypad.
 * @return The value of the pressed key, if any.
 */
//	uint8_t keypad_event_check(key_event)
//	{
//	if (key_event != 0xFF) { // check if there is a event from the EXTi callback
//			  uint16_t key_pressed = keypad_handler(key_event); // call the keypad handler
//			  if (key_pressed != 0xFF) {
//				  printf("Key pressed: %x\r\n", key_pressed); // print the key pressed
//			  }
//			  key_event = 0xFF; // clean the event
//		return key_pressed;
//	}

