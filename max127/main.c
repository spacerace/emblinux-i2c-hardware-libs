/*
 * main.c
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 *      distributed under the terms of GPL
 *      if you don't have a copy of the GPL have a look at gnu.org
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "max127.h"

int i2c_bus;

int main() {
	unsigned short adc_channels[8];
	int i;
        i2c_bus = open("/dev/i2c-0", O_RDWR);
        if(i2c_bus == -1) {
                printf("cant open i2c bus!\n exit.\n");
                close(i2c_bus);
                return -1;
        }

	for(i = 0; i < 8; i++) {
		adc_channels[i] = get_max127(0x28, i, 0);	// read the max127 ADC at address 0x28 (7 bit addres, 8 bit addres with R/W included = 0x50
								// get channel i, 0-5V range 
								//	for information about arguments see max127.c and max127.h, it's well commented
		printf("channel %d: $%03x\n", i, adc_channels[i]);
	}
        close(i2c_bus);
        return 0;
}

