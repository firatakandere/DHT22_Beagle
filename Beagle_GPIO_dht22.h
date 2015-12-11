#ifndef BEAGLE_GPIO_DHT22_H
#define BEAGLE_GPIO_DHT22_H

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "Beagle_GPIO/Beagle_GPIO.h"

#define MAXTIMINGS 84

/**
 * @brief diff Compute diff for timespec from clock_gettime
 * @param start Starting time
 * @param end Ending time
 * @return Time difference
 */
timespec diff(timespec start, timespec end);

/**
 * @brief bbb_read_dht22 Read DHT22 Data From BeagleBone Black
 * @param pin Pin number, check Beagle_GPIO, GPIO Pins
 * @param temperature Address of the temperature variable where the temperature value to be written
 * @param humidity Address of the humidity variable where the humidity value to be written
 * @return Returns zero if successful. Returns -1 if the checksum for data is failed.
 */
int bbb_read_dht22(unsigned short pin, float *temperature, float *humidity);

#endif // BEAGLE_GPIO_DHT22_H
