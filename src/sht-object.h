/* > sht-object.h */
/* Daniel F. Smith, 2019 */

#ifndef SHT_OBJECT_H
#define SHT_OBJECT_H

class sht7x {
public:
        sht7x(int scl_pin,int sda_pin,float voltage=3.3,int clock_hz=10000,
                bool scl_pushpull=true,bool sda_pushpull=false);
        ~sht7x();

        bool read(bool rh=true);
public:
        float last_degc;
        float last_rh;
        const float bad_val=-1000;
private:
        struct sht7x_port;
        sht7x_port *sensor;
};

#endif
