

#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#include"mytime.h"


#define TEST_TIMESTAMP 	 	1704067195 // 31.12.2023 23:59:55 at GMT = 0
#define TEST_TIMESTAMP2		1705924410
//#define TEST_TIMESTAMP		0

bool convertDateTypes(date_t *myDate, const struct tm *libDate) //convert from struct tm to date_t
{
    myDate->Year = (uint8_t)libDate->tm_year - 70;
    myDate->Month = (uint8_t)libDate->tm_mon;
    myDate->Day = (uint8_t)libDate->tm_mday;

    myDate->Hour = (uint8_t)libDate->tm_hour;
    myDate->Minutes = (uint8_t)libDate->tm_min;
    myDate->Seconds = (uint8_t)libDate->tm_sec;

    return true;

}

int main(void)
{
   char uartStr[64];
   char *uartStr_ptr = &uartStr;
   char tempStr[64];
   char *tempStr_ptr = &tempStr;

   date_t myDate;
   struct tm *libDate;

   timestamp_t lastTimestamp;
   timestamp_t myTimestampA = TEST_TIMESTAMP;
   timestamp_t myTimestampB = TEST_TIMESTAMP2;
   timestamp_t myTimestampC;


   weekday_t day;
   uint16_t elapsedDays;

   bool ReturnValue;
   bool isOk = true;

   //test sending NULLs
   ReturnValue = timeToDate(myTimestampA, NULL);
   if(ReturnValue != 0) isOk = false;

   ReturnValue = dateToTime(NULL, NULL);
   if(ReturnValue != 0) isOk = false;

   ReturnValue = dateToTime(&myDate, NULL);
   if(ReturnValue != 0) isOk = false;

   ReturnValue = dateToTime(NULL, myTimestampA);
   if(ReturnValue != 0) isOk = false;

   ReturnValue = timeToWeekday(myTimestampA, NULL);
   if(ReturnValue != 0) isOk = false;

   ReturnValue = dayBetweenTimes(myTimestampA, myTimestampB, NULL);
   if(ReturnValue != 0) isOk = false;

   sprintf(uartStr_ptr, "isOk value for NULL tests: %d\n", (uint8_t)isOk);
   puts(uartStr);

   while(1)
   {
        //test sending TIMESTAMP

        if(myTimestampA != lastTimestamp)
        {
            myTimestampB = (timestamp_t)time(0);
            
            //time to date
            ReturnValue = timeToDate(myTimestampA, tempStr_ptr);
            sprintf(uartStr_ptr, "timestamp A time is: %s\n", tempStr_ptr);
            puts(uartStr);
            if(ReturnValue == 0) isOk = false;

            ReturnValue = timeToDate(myTimestampB, tempStr_ptr);
            sprintf(uartStr_ptr, "timestamp B time is: %s\n", tempStr_ptr);
            puts(uartStr);
            if(ReturnValue == 0) isOk = false;


            //date to time
            time_t temp = (time_t)myTimestampA;
            libDate = localtime(&temp); //convert from timestamp to struct tm
            convertDateTypes(&myDate, libDate); //convert from struct tm to  date_t

            sprintf(uartStr_ptr, "timestamp A value is: %d\n", myTimestampA);
            puts(uartStr);

            ReturnValue = dateToTime(&myDate, &myTimestampC);
            sprintf(uartStr_ptr, "dateToTime value is: %d\n", myTimestampC);
            puts(uartStr);

            if((ReturnValue == 0) || ((myTimestampC - myTimestampA) != 0)) isOk = false;

            //time to weekday
            ReturnValue = timeToWeekday(myTimestampA, &day);
            sprintf(uartStr_ptr, "for timestamp A date current day is %d\n", (uint8_t)day);
            puts(uartStr);
            if(ReturnValue == 0) isOk = false;

            //days between times
            ReturnValue = dayBetweenTimes(myTimestampA, myTimestampB, &elapsedDays);
            sprintf(uartStr_ptr, "elapsed days between timestamp A and B are: %d\n", elapsedDays);
            puts(uartStr);
            if(ReturnValue == 0) isOk = false;

            sprintf(uartStr_ptr, "isOk value for upper tests is: %d\n\n", (uint8_t)isOk);
            puts(uartStr);

            lastTimestamp = myTimestampA;
        }

	    myTimestampA += 86000; //not whole day

        for(uint32_t i = 0; i < 640000000; i++)
            ;
    }

    

    int a = scanf("%s", &uartStr_ptr);
}