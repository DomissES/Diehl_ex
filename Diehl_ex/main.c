

#include<stdio.h>
#include<stdlib.h>

#include"mytime.h"

#include <time.h>

#define ONE_DAYY 86400
uint8_t dayInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


bool foo(uint32_t timestamp, date_t *date)
{
    uint32_t secondsToSubstract;

    //year
    uint16_t year = 1970;

    while(timestamp > (365 * ONE_DAYY)) //is enough seconds for one year
    {
        secondsToSubstract = 365 * ONE_DAYY;

        if(((year % 4) == 0) && !((year % 100) == 0)) //divided by 4 and no divided by 100
        {
            secondsToSubstract += ONE_DAYY;
        }
        if((year % 400) == 0) //divided by 400
        {
            secondsToSubstract += ONE_DAYY;
        }

        timestamp -= secondsToSubstract;
        year++;
    }

    date->Year = year - 1970;
    
   //month
    uint8_t i = 0;
    uint8_t month = 0;
   while(timestamp > (31 * ONE_DAYY))
   {
        secondsToSubstract = dayInMonth[i] * ONE_DAYY;
        month++;
        timestamp -= secondsToSubstract;
   }

   //day
   
    uint8_t day = timestamp / ONE_DAYY;
    date->Day = day;
    timestamp -= day * ONE_DAYY;

    //hour
    uint8_t hour = timestamp / 3600;
    date->Hour = hour;
    timestamp -= hour * 3600;

    //minute
    uint8_t minute = timestamp / 60;
    date->Minutes = minute;
    timestamp -= minute * 60;

    //seconds
    date->Seconds = timestamp;
   
}

int main(void)
{
    char c[10];
    const char *c_ptr = &c;

    date_t today;
    
    struct tm *timeinfo;

   uint8_t lastSecond;

   while(1)
   {
    time_t actual = time(0) + 3600;

    foo(actual, &today);
    if(today.Seconds != lastSecond)
    {
        printf("this year is %d\n", (uint16_t)(1970 + today.Year));
        printf("this month is %d\n", today.Month + 1);
        printf("this day is %d\n", today.Day + 1);
        printf("this hour is %d\n", today.Hour);
        printf("this minute is %d\n", today.Minutes);
        printf("this second is %d\n\n\n\n", today.Seconds);

        lastSecond = today.Seconds; 
    }
    for(uint32_t i = 0; i < 32000000; i++)
        ;
   }

    

    int a = scanf("%s", (char*)&c);
}