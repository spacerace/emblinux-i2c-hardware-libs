#ifndef __SAA1064_AVR32_H_
#define __SAA1064_AVR32_H_

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

#define SEG_A   0x01
#define SEG_B	0x02
#define SEG_C	0x04
#define SEG_D	0x08
#define SEG_E	0x10
#define SEG_F	0x20
#define SEG_G	0x40
#define SEG_DP	0x80

#define CURRENT_3MA	0x10
#define CURRENT_6MA	0x20
#define CURRENT_9MA	0x30
#define CURRENT_12MA	0x40
#define CURRENT_15MA	0x50
#define CURRENT_18MA	0x60
#define CURRENT_21MA	0x70

void saa1064_test(unsigned char address, unsigned char current);
void saa1064_setup(unsigned char address, unsigned char current);
void saa1064_dig(unsigned char address, unsigned char digit, unsigned char value, unsigned char dp);
void saa1064_number(unsigned char address, unsigned short number);


#endif //__SAA1064_AVR32_H_
