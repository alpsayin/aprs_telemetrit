
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "telemetry.h"
#include "util.h"

telemetry_data_t mydata;
telemetry_coefs_t mycoefs;

char* labels[13];// = {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};
char* units[13];// =  {" ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " "};

int main(int argc, char* argv[])
{
	uint8_t i, tmp;
	char outbuf[256];
	char callsign[10];
	char receiverCallsign[10];
	char projectName[23];

	if(argc<4)
	{
		usage();
		return 0;
	}

	strcpy(callsign, argv[2]);
	strcpy(receiverCallsign, argv[3]);

	if(!strcmp(argv[1], "data"))
	{
		if(4 < argc)
			mydata.seqNo=atoi(argv[4]);
		else
			mydata.seqNo=0;
		for(i=0; i<5; i++)
		{
			if(5+i < argc)
				mydata.analog_data[i]=atoi(argv[5+i]);
		}
		for(i=0; i<8; i++)
		{
			if(10+i < argc)
				mydata.binary_data|= (atoi(argv[10+i])&0x1)<<(7-i);
		}
		telemetry_data(outbuf, callsign, receiverCallsign, &mydata);
		printf("%s\n", outbuf);
	}
	else if(!strcmp(argv[1], "label"))
	{
		for(i=0; i<13; i++)
		{
			if(4+i < argc)
			{
				labels[i] = malloc(strlen(argv[4+i]));
				strcpy(labels[i], argv[4+i]);
			}
			else
			{
				labels[i] = malloc(1);
				strcpy(labels[i], " ");
			}
		}
		telemetry_labels(outbuf, callsign, receiverCallsign, labels);
		printf("%s\n", outbuf);
	}
	else if(!strcmp(argv[1], "unit"))
	{
		for(i=0; i<13; i++)
		{
			if(4+i < argc)
			{
				labels[i] = malloc(strlen(argv[4+i]));
				strcpy(labels[i], argv[4+i]);
			}
			else
			{
				labels[i] = malloc(1);
				strcpy(labels[i], " ");
			}
		}
		telemetry_units(outbuf, callsign, receiverCallsign, labels);
		printf("%s\n", outbuf);
	}
	else if(!strcmp(argv[1], "coef"))
	{
		for(i=0; i<5; i++)
		{
			if(4+(i*3) < argc)
				mycoefs.a[i]=atoi(argv[4+(i*3)]);
			if(5+(i*3) < argc)
				mycoefs.b[i]=atoi(argv[5+(i*3)]);
			if(6+(i*3) < argc)
				mycoefs.c[i]=atoi(argv[6+(i*3)]);
		}
		telemetry_coefs(outbuf, callsign, receiverCallsign, &mycoefs);
		printf("%s\n", outbuf);
	}
	else if(!strcmp(argv[1], "bitsense"))
	{
		tmp=0;
		if(4 < argc)
			strcpy(projectName, argv[4]);
		else
			strcpy(projectName, " ");
		for(i=0; i<8; i++)
		{
			if(5+i < argc)
				tmp |= (atoi(argv[5+i])&0x1)<<(7-i);
		}
		telemetry_bitsense(outbuf, callsign, receiverCallsign, tmp, projectName);
		printf("%s\n", outbuf);
	}
	else
	{
		usage();
		return 0;
	}
	return 0;
}