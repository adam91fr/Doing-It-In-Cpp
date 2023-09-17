/***********
*
*   File:       date.cpp
*
*   Function:   Functions relating to dates
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Description:
*
*       The date class provides a uniform way of dealing with dates.  It currently
*       includes functions to read and write these standard dates to files.  In the
*       future it can be expanded to perform other date-related functions such as
*       increasing a date by a given number of days, converting it to other forms, etc.
*
**********/

#include "date.h"

/**********
*
*   Module:     Set
*
*   Function:   Sets the current value of the date
*
*   Note:       If the specified date isn't valid, an expection will be thrown.
*
*   Input:
*
*       year    -   The year.  BE SURE IT'S LIKE 2010, NOT LIKE 10
*
*       month   -   The month.
*
*       day     -   The day.
*
**********/

void Date::Set(int year,int month,int day)
{
    int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ( (year < 1901) || (year > 2099) ) {
        throw YearOutOfRange();
    }
    this->year = year;

    if (year%4 == 0) {
        months[1] = 29;
    }

    if ( (month < 1) || (month > 12) ) {
        throw MonthOutOfRange();
    }
    this->month = month;

    if ( (day < 1) || (day > months[month-1]) ) {
        throw DayOutOfRange();
    }
    this->day = day;
}

/**********
*
*   Module:     Read
*
*   Function:   Read a date from a C-standard stream file
*
*   Note:       The file is presumed to already be properly positioned, and the
*               data being read is presumed to have been written by Date::Write().
*
**********/

void Date::Read(FILE *file)
{
    short int sint;
    //if (fread(&year,sizeof(year),1,file) != 1) {
    if (fread(&sint, sizeof(sint), 1, file) != 1) {
        throw EndOfFile();
    }
    year = sint;
    //if (fread(&month,sizeof(month),1,file) != 1) {
    if (fread(&sint, sizeof(sint), 1, file) != 1) {
        throw EndOfFile();
    }
    month = sint;
    //if (fread(&day,sizeof(day),1,file) != 1) {
    if (fread(&sint, sizeof(sint), 1, file) != 1) {
        throw EndOfFile();
    }
    day = sint;
}

/**********
*
*   Module:     Write
*
*   Function:   Write a Date object to a C-style stream file
*
*   Note:       You can read it later with Date::Read().
*
**********/

void Date::Write(FILE *file)
{
    if (fwrite(&year,sizeof(year),1,file) != 1) {
        throw DiskFull();
    }
    if (fwrite(&month,sizeof(month),1,file) != 1) {
        throw DiskFull();
    }
    if (fwrite(&day,sizeof(day),1,file) != 1) {
        throw DiskFull();
    }
}
