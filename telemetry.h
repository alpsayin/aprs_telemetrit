
#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stdint.h>

struct telemetry_data_
{
	uint16_t seqNo;
	uint8_t analog_data[5];
	uint8_t binary_data;
};
typedef struct telemetry_data_ telemetry_data_t;

struct telemetry_coefs_
{
	uint8_t a[5];
	uint8_t b[5];
	uint8_t c[5];
};
typedef struct telemetry_coefs_ telemetry_coefs_t;


uint8_t telemetry_data(char* outbuf, char* callsign, char* receiverCallsign, telemetry_data_t* data);
uint8_t telemetry_labels(char* outbuf, char* callsign, char* receiverCallsign, char* labels[]);
uint8_t telemetry_units(char* outbuf, char* callsign, char* receiverCallsign, char* units[]);
uint8_t telemetry_coefs(char* outbuf, char* callsign, char* receiverCallsign, telemetry_coefs_t* coefs);
uint8_t telemetry_bitsense(char* outbuf, char* callsign, char* receiverCallsign, uint8_t bitsense_flag, char* projectName);

#endif