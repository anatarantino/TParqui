#ifndef TIMERTC_H
#define TIMERTC_H

#include <stdint.h>

typedef enum{
    HOURS = 4,
    MINUTES = 2,
    SECONDS = 0
}time_type;

uint8_t getTime(time_type descriptor);

#endif