/*
 * pcf8574.h
 *
 *  Created on: 03.08.2011
 *      Author: krumeltee
 *      distributed under the terms of the GPL
 *      if you dont have a copy of the GPL have a look at gnu.org
 */

#ifndef PCF8574H_
#define PCF8574H_

void set_pcf8574(unsigned char address, unsigned char data);
unsigned char get_pcf8574(unsigned char address);

#endif /* PCF8574H_ */
