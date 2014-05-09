#ifndef _MULTIMEDIA_BITSTREAM_H_
#define _MULTIMEDIA_BITSTREAM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BS_MODE_READ	1
#define BS_MODE_WRITE	2

typedef struct {
	FILE *device;
	uint8_t data;
	uint8_t mask;
} bitstream_t;

bitstream_t* bs_create(FILE *dev, int mode);
void bs_destroy(bitstream_t *stream);
void bs_flush(bitstream_t *stream);
bool bs_read(bitstream_t *stream, uint8_t *bit);
bool bs_read_bool(bitstream_t *stream, bool *bit);
bool bs_write(bitstream_t *stream, uint8_t bit);
bool bs_write_bool(bitstream_t *stream, bool bit);

#endif
