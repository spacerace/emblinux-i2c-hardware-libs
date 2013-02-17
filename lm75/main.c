/*
 * main.c
 *
 *  Created on: 03.08.2011
 *      Author: bazi
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

int i2c_bus;

unsigned short get_lm75(unsigned char address) {
	char buffer[4];
	unsigned short return_value;
	ioctl(i2c_bus, I2C_SLAVE, address);
	buffer[0] = 0x00;
	write(i2c_bus, buffer, 1);
	read(i2c_bus, buffer, 2);
	return_value = (buffer[0]<<8);
	return_value |= (buffer[1]);
	return (return_value>>7);	
}

double get_lm75_celsius(unsigned short lm75val) {
	float ret = (int)(lm75val&~0x80);
	ret /= 2;
	if (lm75val&0x80) ret *= -1;
 	return ret;
}

int main() {
	unsigned short lm75;
	double temp;

        i2c_bus = open("/dev/i2c-0", O_RDWR);
        if(i2c_bus == -1) {
                printf("cant open i2c bus!\n exit.\n");
                close(i2c_bus);
                return -1;
        }
        printf("bus opened\n");

	lm75 = get_lm75(0x49);
	temp = get_lm75_celsius(lm75);
	printf("%4.01f°C\n", temp);
		
        close(i2c_bus);
        return 0;
}

