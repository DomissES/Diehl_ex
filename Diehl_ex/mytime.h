#ifndef __MYTIME_H__
#define __MYTIME_H__


#include <stdbool.h>
#include <stdint.h>

typedef uint32_t timestamp_t;

typedef enum
{
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
}weekday_t;

typedef struct 
{
    uint8_t Hour;
    uint8_t Minutes;
    uint8_t Seconds;
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
}date_t;

bool timeToDate(timestamp_t timestamp, const char *date);
bool timeToWeekday(timestamp_t timestamp, const weekday_t *day);
bool dateToTime(const char *date, timestamp_t *timestamp);
bool dayBetweenTimes(timestamp_t time_A, timestamp_t time_B);



#endif
