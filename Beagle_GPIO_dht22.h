#ifndef BEAGLE_GPIO_DHT22_H
#define BEAGLE_GPIO_DHT22_H

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "Beagle_GPIO/Beagle_GPIO.h"

#define MAXTIMINGS 84

timespec diff(timespec start, timespec end);
int bbb_read_dht22(unsigned short pin, float *temperature, float *humidity);

#endif // BEAGLE_GPIO_DHT22_H
