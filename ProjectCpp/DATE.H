/***********
*
*   File:       date.h
*
*   Function:   Structures relating to dates
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
**********/

#ifndef DATE_DEF

#define DATE_DEF

#include <stdio.h>

class Date {

protected:
    int         year;
    int         month;
    int         day;

public:
	class		DateError { };
    class       OutOfRange: public DateError { }; 
    class       YearOutOfRange: public OutOfRange { };
    class       MonthOutOfRange: public OutOfRange { };
    class       DayOutOfRange: public OutOfRange { };
    class       EndOfFile { };
    class       DiskFull { };

public:
                Date(int year,int month=1,int day=1)
                    { Set(year,month,day); }
                Date()
                    { year=1900; month=1; day=1; }
    int         Year()
                    { return year; }
    int         Month()
                    { return month; }
    int         Day()
                    { return day; }
    void        Set(int year,int month=1,int day=1);
    void        Read(FILE *file);
    void        Write(FILE *file);
};

#endif
