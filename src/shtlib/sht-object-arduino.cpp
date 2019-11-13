/* > sht-object.cpp */
/* Daniel F. Smith, 2019 */

#include "sht-object.h"

#include "shtlib/i2c-arduino.h"
#define i2c_io i2c_arduino_io
#include "shtlib/sht.h"

struct sht7x::sht7x_port {
        i2c_io io;
        shtport *port;
};

sht7x::sht7x(int scl_pin,int sda_pin,
        float voltage,int clock_hz,
        bool scl_pushpull,bool sda_pushpull):
        last_degc{sht_badtemp},
        last_rh{sht_badrh}
{
        int err;

        sensor=new sht7x_port;
        sensor->io.c=scl_pin;
        sensor->io.d=sda_pin;
        sensor->io.half_clock=500000/clock_hz;
        sensor->io.ppc=scl_pushpull?1:0;
        sensor->io.ppd=sda_pushpull?1:0;

        sensor->port=sht_open(&sensor->io,voltage,&err);
}

sht7x::~sht7x() {
        if (sensor->port) sht_close(sensor->port);
        delete sensor;
}

bool sht7x::read(bool rh) {
        last_degc=sht_badtemp;
        last_rh=sht_badrh;
        if (!sensor->port) return false;
        if (!rh) {
                last_degc=sht_gettemp(sensor->port);
        }
        else {
                if (sht_readmany(sensor->port,NULL)==0) {
                        last_degc=sht_getlasttemp(sensor->port);
                        last_rh=sht_getlastrh(sensor->port);
                }
        }
        return (last_degc!=sht_badtemp);
}
