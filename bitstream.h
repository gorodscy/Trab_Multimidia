#ifndef _MULTIMEDIA_BITSTREAM_H_
#define _MULTIMEDIA_BITSTREAM_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define BS_MODE_READ	1
#define BS_MODE_WRITE	2

typedef struct {
	FILE *device;
	unsigned char data;
	unsigned char mask;
} bitstream_t;

bitstream_t* bs_create(FILE *dev, int mode) {
	bitstream_t *stream = (bitstream_t*)malloc(sizeof(bitstream_t));
	stream->device = dev;
	stream->data = 0;
	if ( mode == BS_MODE_READ ) {
		stream->mask = 0x00;
	} else {
		stream->mask = 0x80;
	}
	return stream;
}

void bs_flush(bitstream_t *stream) {
	if ( !stream->mask ) {
		// nothing to flush.
		return;
	}
	// write bit to file.
	fwrite(&stream->data, 1, 1, stream->device);
	// clean up.
	stream->data = 0;
	stream->mask = 0x80;
}

void bs_destroy(bitstream_t *stream) {
	bs_flush(stream);
	free(stream);
}

bool bs_read(bitstream_t *stream, unsigned char *bit) {
	if ( feof(stream->device) ) {
		return false;
	}
	if ( !stream->mask ) {
		fread(&stream->data, 1, 1, stream->device);
		stream->mask = 0x80;
	}
	*bit = ( (stream->data & stream->mask) != 0 );
	stream->mask = stream->mask >> 1;
	return true;
}

bool bs_read_bool(bitstream_t *stream, bool *bit) {
	unsigned char ubit = 0;
	bool res = bs_read(stream, &ubit);
	*bit = (ubit != 0);
	return res;
}

bool bs_write(bitstream_t *stream, unsigned char bit) {
	if ( bit ) {
		stream->data = stream->data | stream->mask;
	} else {
		stream->data = stream->data & ~stream->mask;
	}
	stream->mask = stream->mask >> 1;
	if ( stream->mask == 0x00 ) {
		fwrite(&stream->data, 1, 1, stream->device);
		stream->data = 0;
		stream->mask = 0x80;
	}
	return true;
}

bool bs_write_bool(bitstream_t *stream, bool bit) {
	return bs_write(stream, (unsigned char)(bit ? 1 : 0));
}

#endif
