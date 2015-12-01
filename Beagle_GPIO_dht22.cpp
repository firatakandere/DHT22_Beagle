#include "DHT22_Beagle/Beagle_GPIO_dht22.h"

/**
 * @brief bbb_read_dht22 Read DHT22 Data From BeagleBone Black
 * @param pin Pin number, check Beagle_GPIO, GPIO Pins
 * @param temperature Address of the temperature variable where the temperature value to be written
 * @param humidity Address of the humidity variable where the humidity value to be written
 * @return Returns zero if successful. Returns -1 if the checksum for data is failed.
 */
int bbb_read_dht22(unsigned short pin, float *temperature, float *humidity) {

    Beagle_GPIO	gpio;

    int counter = 0;
    int laststate = 1;
    int j = 0;
    int state[250], data[100] = {0};
    struct timespec timestamp[250];
    int bitidx = 0;

    clockid_t clk_id = CLOCK_REALTIME ;

    gpio.configurePin(pin, Beagle_GPIO::kOUTPUT);
    gpio.enablePinInterrupts(pin, false);

    // Set pin to HIGH for 500ms
    gpio.writePin(pin, 1);
    usleep(500000);

    // Set pin to LOW for 20ms
    gpio.writePin(pin, 0);
    usleep(20000);

    gpio.configurePin(pin, Beagle_GPIO::kINPUT);
    gpio.enablePinInterrupts(pin, false);

    // Wait for pin to drop
    while (gpio.readPin(pin) == 0)
        ;
    while (gpio.readPin(pin) == 1)
        ;

    // Read data

    for (int i = 0; i < MAXTIMINGS; ++i) {
        counter = 0;
        while (gpio.readPin(pin) == laststate) {
            if (++counter == 1000)
                break;
        }
        laststate = gpio.readPin(pin);
        counter = 0;

        state[bitidx] = laststate;
        clock_gettime(clk_id, &timestamp[bitidx]);
        ++bitidx;
    }

    // Set pin as output
    gpio.configurePin(pin, Beagle_GPIO::kOUTPUT);
    gpio.enablePinInterrupts(pin, false);

    // Finalize DHT22 sensor
    gpio.writePin(pin, 1);

    j = 0;
    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    for (int i = 0; i < bitidx; ++i) {
        if ((i > 3) && (i%2 == 0)) {
            //Shove each bit into the storage bytes
            data[j / 8] <<= 1;
            if ((diff(timestamp[i - 1], timestamp[i]).tv_nsec / 1000) > 40)
                data[j / 8] |= 1;
            ++j;
        }
    }

    // Return -1 if the checksum failed
    if ( ((data[0] + data[1] + data[2] + data[3]) & 0xFF) != data[4] )
    {
        std::cout << "Checksum failed" << std::endl;
        return -1;
    }

    // Compute the Temp & Hum from data (for RHT3 / DHT22)
    *humidity = ( data[0] * 256 + data[1] ) / 10;

    *temperature = ( (data[2] & 0x7F)* 256 + data[3] ) / 10.0;
    if (data[2] & 0x80)
        *temperature *= -1.0f;

    // Print to console
    std::cout << "Temp = " << *temperature << "°C, Hum = " << *humidity << "%\n";

    return 0;
}

/* Compute diff for timespec (from clock_gettime)*/
/**
 * @brief diff Compute diff for timespec from clock_gettime
 * @param start Starting time
 * @param end Ending time
 * @return Time difference
 */
timespec diff(timespec start, timespec end)
{
	timespec temp;
    if ((end.tv_nsec-start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
	} else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
	}
	return temp;
}
