#include "saa1064_avr32.h"

#include <stdlib.h>

extern int i2c_bus;

unsigned char digit_defs[10] = { SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F,		// 0
				 SEG_B|SEG_C,					// 1
				 SEG_A|SEG_B|SEG_D|SEG_E|SEG_G,			// 2
				 SEG_A|SEG_B|SEG_C|SEG_D|SEG_G,			// 3
				 SEG_B|SEG_C|SEG_F|SEG_G,			// 4
				 SEG_A|SEG_C|SEG_D|SEG_F|SEG_G,			// 5
				 SEG_A|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,		// 6
				 SEG_A|SEG_B|SEG_C,				// 7
				 SEG_A|SEG_B|SEG_C|SEG_D|SEG_E|SEG_F|SEG_G,	// 8
				 SEG_A|SEG_B|SEG_C|SEG_D|SEG_F|SEG_G		// 0
};

void saa1064_test(unsigned char address, unsigned char current) {
	char buffer[2];
	
	buffer[0] = 0x00;
	buffer[1] = current | 0x0f;
	
	ioctl(i2c_bus, I2C_SLAVE, address);
	write(i2c_bus, buffer, 2);
	return;
}

void saa1064_setup(unsigned char address, unsigned char current) {
	char buffer[2];
	
	buffer[0] = 0x00;
	buffer[1] = current | 0x07;
	ioctl(i2c_bus, I2C_SLAVE, address);
	write(i2c_bus, buffer, 2);
}

void saa1064_dig(unsigned char address, unsigned char digit, unsigned char value, unsigned char dp) {
	char buffer[2];
	ioctl(i2c_bus, I2C_SLAVE, address);
	switch(digit) {
		case 0:
			buffer[0] = 0x01;
			break;
		case 1:
			buffer[0] = 0x02;
			break;
		case 2:
			buffer[0] = 0x03;
			break;
		case 3:
			buffer[0] = 0x04;
			break;
	}
	if((value > 9)) return;
	
	buffer[1] = digit_defs[value];
	if(dp) buffer[1] |= SEG_DP;
	
	write(i2c_bus, buffer, 2);
	return;
}

void saa1064_number(unsigned char address, unsigned short number) {
	if((number > 9999)) return;
	char buffer[5];
	sprintf(buffer, "%04d", number);

	
	saa1064_dig(address, 0, buffer[0]-48, 0);
	saa1064_dig(address, 1, buffer[1]-48, 0);
	saa1064_dig(address, 2, buffer[2]-48, 0);
	saa1064_dig(address, 3, buffer[3]-48, 0);
	
	return;
}
