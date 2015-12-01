/*
  DHT22 reader for Beaglebone

  Inspired by adafruit code :
    https://github.com/adafruit/Adafruit-Raspberry-Pi-Python-Code/tree/master/Adafruit_DHT_Driver
  Library used for GPIO access :
    https://github.com/firatakandere/Beagle_GPIO
*/

#ifndef BEAGLE_GPIO_DHT22_H
#define BEAGLE_GPIO_DHT22_H

#include "Beagle_GPIO/Beagle_GPIO.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#define MAXTIMINGS 84

timespec diff(timespec start, timespec end);
int bbb_read_dht22(unsigned short pin, float *temperature, float *humidity);

#endif // BEAGLE_GPIO_DHT22_H
