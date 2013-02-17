/*
 * max127.c
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 *      distributed under the terms of GPL
 *      if you don't have a copy of the GPL have a look at gnu.org
 */

#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "max127.h"

extern int i2c_bus;

/* get_max127()
*
* address - I2C Bus Addresse des Chips
* channel - Der Kanal, von 0 bis 7
* mode - 0 = 0-5V messung, 1 = 0-10V messung
* 2 = +-5V messung, 3 = +-10V messung
*
*/
unsigned short get_max127(unsigned char address, unsigned char channel, unsigned char mode) {
        unsigned char high, low, config_byte;
        unsigned short value;
        char buffer[2];

        if(channel > 7) return 0;

        ioctl(i2c_bus, I2C_SLAVE, address);     // give the slave address to the linux i2c framework

        switch(mode) {
                case 3:
                        config_byte = (0x8c | (channel<<4));
                        break;
                case 2:
                        config_byte = (0x84 | (channel<<4));
                        break;
                case 1:
                        config_byte = (0x88 | (channel<<4));
                        break;
                default:
                case 0:
                        config_byte = (0x80 | (channel<<4));
                        break;
        }

        buffer[0] = config_byte;        // write the config byte to max127
        write(i2c_bus, buffer, 1);

        read(i2c_bus, buffer, 2);       // read 2 bytes (ad conv. result) from max127

        high = buffer[0];               // place the two bytes in one short
        low = buffer[1];
        value = ((high<<8)|low);
        value >>= 4;                    // shift it 4 bytes to the right, we need a usable result

        return value;
}



