#ifndef RTCTIME_H
#define RTCTIME_H

#include <stdint.h>

typedef enum{
    HOURS = 0X04,
    MINUTES = 0X02,
    SECONDS = 0X00
}time_type;

uint8_t getTime(time_type descriptor); //descriptor is for hours, minutes or seconds

uint8_t getRTC(uint64_t descriptor);

#endif