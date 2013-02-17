/*
 * saa1064 avr32
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 * 
 *    (c) 2011 krumeltee, email: <nils.stec@googlemail.com>
 * 
 *    this code is free software. you can use it and with it whatever you like.
 *    if you redistribute this code or parts of it, please let there be a note
 *    with a link to the source of the code and the author.
 * 
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

#include "saa1064_avr32.h"

int i2c_bus;

int main() {
        i2c_bus = open("/dev/i2c-0", O_RDWR);
        if(i2c_bus == -1) {
                printf("cant open i2c bus!\n exit.\n");
                close(i2c_bus);
                return -1;
        }
        printf("bus opened\n");

	saa1064_setup(0x38, CURRENT_21MA);
	

	int i;
	for(;;) {
		for(i = 0; i < 10000; i++) {
			saa1064_number(0x38, i);
			usleep(50000);
		}
	}
		
        close(i2c_bus);
        return 0;
}

