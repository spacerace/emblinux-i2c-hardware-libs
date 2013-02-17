/*
 * pcf8574.c
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 *      distributed under the terms of the GPL
 *      if you dont have a copy of the GPL have a look at gnu.org
 */

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "pcf8574.h"

extern int i2c_bus;

void set_pcf8574(unsigned char address, unsigned char data) {
	char buffer[2] = { data, 0x00 };
	ioctl(i2c_bus, I2C_SLAVE, address);
	write(i2c_bus, buffer, 1);	
	return;
}

unsigned char get_pcf8574(unsigned char address) {
	char buffer[2];
	ioctl(i2c_bus, I2C_SLAVE, address);
	read(i2c_bus, buffer, 1);
	return buffer[0];
}


