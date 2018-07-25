#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "acarsdec.h"

#define BUFFER_SAMPLE_COUNT 4096

int initRaw(char **argv, int optind)
{
	nbch = 1;
	channel[0].dm_buffer=malloc(sizeof(float)*BUFFER_SAMPLE_COUNT);
	return 0;
}

int runRawSample(void)
{
	int byte_count;
	unsigned char remaining_bytes = 0;
	char* buffer = (char*)channel[0].dm_buffer;

	while ((byte_count = read(0, buffer+remaining_bytes, sizeof(float)*BUFFER_SAMPLE_COUNT - remaining_bytes))>0)
	{
		unsigned samples = (remaining_bytes+byte_count)/sizeof(float);
		remaining_bytes = byte_count-samples*sizeof(float);
		demodMSK(&(channel[0]), samples);
		memcpy(buffer, buffer+samples*sizeof(float), remaining_bytes);
	};
	return 0;
}
