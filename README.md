DHT22 Library for BeagleBone
=======================
DHT22 Library for BeagleBone written in C++

Required GPIO Library: [https://github.com/firatakandere/Beagle_GPIO](https://github.com/firatakandere/Beagle_GPIO)

Forked from: [https://github.com/NunoValverde/DHT22_Beagle](https://github.com/NunoValverde/DHT22_Beagle)

Usage
-----

```
#include "Beagle_GPIO/Beagle_GPIO.h"
#include "DHT22_Beagle/Beagle_GPIO_dht22.h"
int main()
{
    float temperature, humidity;
    while (bbb_read_dht22(Beagle_GPIO::P8_11, &temperature, &humidity))
        ;
    std::cout << "Temperature: " << temperature << " celcius degree" << std::endl;
    std::cout << "Humidity: " << humidity << "%" << std::endl;
    return 0;
}
```
