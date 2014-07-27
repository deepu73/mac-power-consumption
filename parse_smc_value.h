#ifndef PARSE_SMC_VALUE_H_
#define PARSE_SMC_VALUE_H_

float parse_smc_value(SMCVal_t* val) {
	char f_str[2] = {val->dataType[3], 0};
	UInt8 f = strtoul(f_str, NULL, 16);

	UInt16 encoded_big_endian = 0;

	memmove(&encoded_big_endian, val->bytes, sizeof(UInt16));
	UInt16 encoded_host_endian = OSSwapBigToHostInt16(encoded_big_endian);
	return (float)encoded_host_endian / (float)(1 << f);
}

#endif
