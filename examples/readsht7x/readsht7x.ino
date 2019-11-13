#include <sht-object.h>

#define clk_pin 26
#define data_pin 25
#if defined(ARDUINO_ARCH_AVR)
#define voltage ,5.0
#elif defined(ARDUINO_ARCH_ESP32)
#define voltage ,3.3
#else
#define voltage /* default is 3.3V */
#endif

sht7x sht(clk_pin,data_pin voltage);

void setup() {
        Serial.begin(115200);
}

void loop() {
        sht.read();
        Serial.printf("Temperature %.2f humidity %.1f%%\n",
                sht.last_degc,sht.last_rh);
        delay(5000);
}
