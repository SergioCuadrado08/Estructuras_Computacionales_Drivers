/*
 * ring_buffer.c
 *
 *  Created on: Oct 23, 2023
 *      Author: Sergio
 */

#include "ring_buffer.h"

void ring_buffer_init (ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity){

	ring_buffer->buffer = buffer;
	ring_buffer->capacity = capacity;

	ring_buffer->head=0;
	ring_buffer->tail=0;
	ring_buffer->is_full=0;


}

uint8_t ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data){
	ring_buffer->buffer[ring_buffer-> head]=data;
	ring_buffer->head = (ring_buffer-> head + 1) % ring_buffer->capacity;

	if (ring_buffer->is_full !=0){
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
	}
	if (ring_buffer->head==ring_buffer->tail){
		ring_buffer->is_full=1;
		return 0;
	}
	return 1;
}

uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data)
{
	if (ring_buffer_empty(ring_buffer) == 0){

	*data = ring_buffer->buffer[ring_buffer->tail];
	ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity;
	ring_buffer->is_full=0;
	return 1;
	}
	return 0;
}

uint16_t ring_buffer_size (ring_buffer_t  *ring_buffer)
{

	uint16_t size = 0;

	if (ring_buffer->is_full ==0 && (ring_buffer->tail < ring_buffer->head)){
		size = ring_buffer->head - ring_buffer->tail;
	} else{
		size = ring_buffer->head + (ring_buffer->capacity -ring_buffer->tail);
	}
	return size;
}


/**
 *@brief this function checks is ring buffer is empty
 */
uint8_t ring_buffer_empty(ring_buffer_t *ring_buffer){
	return (ring_buffer->is_full == 0) && (ring_buffer->tail == ring_buffer->head);

}
/**
 *@brief this function checks is ring buffer is full
 */
uint8_t ring_buffer_full(ring_buffer_t *ring_buffer){
	return ring_buffer->is_full;
}

void ring_buffer_reset(ring_buffer_t *ring_buffer){
	ring_buffer->tail = 0;
	ring_buffer->head = 0;
	ring_buffer->is_full = 0;
}
