/*
 * pcf8574_main.c
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 *      distributed under the terms of the GPL
 *      if you dont have a copy of the GPL have a look at gnu.org
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

#include "pcf8574.h"

int i2c_bus;

int main() {
        i2c_bus = open("/dev/i2c-0", O_RDWR);
        if(i2c_bus == -1) {
                printf("cant open i2c bus!\n exit.\n");
                close(i2c_bus);
                return -1;
        }
        printf("bus opened...\n");
	
	set_pcf8574(0x27, 0xa0);		// set the PCF with address 0x27 to 0xa0
	printf("$%02x\n", get_pcf8574(0x27));	// read the PCF with address 0x27
	
        close(i2c_bus);
        return 0;
}

