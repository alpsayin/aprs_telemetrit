
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "telemetry.h"
#include "util.h"

uint8_t telemetry_data(char* outbuf, char* callsign, char* receiverCallsign, telemetry_data_t* data)
{
	uint8_t index=0, i, tmp;
	if(!outbuf)
		return 0;

	index+=sprintf(outbuf+index, "%s>%s:", callsign, receiverCallsign);
	outbuf[index++] = 'T';
	index+=sprintf(outbuf+index, "#%d,", data->seqNo);
	for(i=0; i<5; i++)
	{
		index+=sprintf(outbuf+index, "%d,", data->analog_data[i]);
	}

	tmp=data->binary_data;
	for(i=0; i<8; i++)
	{
		if(tmp & 0x80)
			outbuf[index++] = '1';
		else
			outbuf[index++] = '0';
		tmp = tmp << 1;
	}

	outbuf[index]=0;
	return index;
}
uint8_t telemetry_labels(char* outbuf, char* callsign, char* receiverCallsign, char* labels[])
{
	uint8_t index=0, i;
	if(!outbuf)
		return 0;

	index+=sprintf(outbuf+index, "%s>%s:", callsign, receiverCallsign);
	index+=sprintf(outbuf+index, ":%s :", callsign);
	index+=sprintf(outbuf+index, "PARM.%s", labels[0]);
	for(i=1; i<5+8; i++)
	{
		index+=sprintf(outbuf+index, ",%s", labels[i]);
	}

	outbuf[index]=0;
	return index;
}
uint8_t telemetry_units(char* outbuf, char* callsign, char* receiverCallsign, char* units[])
{
	uint8_t index=0, i;
	if(!outbuf)
		return 0;

	index+=sprintf(outbuf+index, "%s>%s:", callsign, receiverCallsign);
	index+=sprintf(outbuf+index, ":%s :", callsign);
	index+=sprintf(outbuf+index, "UNIT.%s", units[0]);
	for(i=1; i<5+8; i++)
	{
		index+=sprintf(outbuf+index, ",%s", units[i]);
	}

	outbuf[index]=0;
	return index;
}

uint8_t telemetry_coefs(char* outbuf, char* callsign, char* receiverCallsign, telemetry_coefs_t* coefs)
{
	uint8_t index=0, i;
	if(!outbuf)
		return 0;

	index+=sprintf(outbuf+index, "%s>%s:", callsign, receiverCallsign);
	index+=sprintf(outbuf+index, ":%s :", callsign);
	index+=sprintf(outbuf+index, "EQNS.");
	for(i=0; i<5; i++)
	{
		if(i==0)
			index+=sprintf(outbuf+index, "%d", coefs->a[i]);
		else
			index+=sprintf(outbuf+index, ",%d", coefs->a[i]);

		index+=sprintf(outbuf+index, ",%d", coefs->b[i]);
		index+=sprintf(outbuf+index, ",%d", coefs->c[i]);
	}

	outbuf[index]=0;
	return index;

}

uint8_t telemetry_bitsense(char* outbuf, char* callsign, char* receiverCallsign, uint8_t bitsense_flag, char* projectName)
{
	uint8_t index=0, i, tmp;
	if(!outbuf)
		return 0;

	index+=sprintf(outbuf+index, "%s>%s:", callsign, receiverCallsign);
	index+=sprintf(outbuf+index, ":%s :", callsign);
	index+=sprintf(outbuf+index, "BITS.");

	tmp = bitsense_flag;
	for(i=0; i<8; i++)
	{
		if(tmp & 0x80)
			outbuf[index++] = '1';
		else
			outbuf[index++] = '0';
		tmp = tmp << 1;
	}

	index+=sprintf(outbuf+index, ",%s", projectName);

	outbuf[index]=0;
	return index;
}