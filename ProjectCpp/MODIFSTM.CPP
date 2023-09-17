/***********
*
*   File:       modifstm.cpp
*
*   Function:   Functions relating to the "modified" iostream class
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
**********/

#include "modifstm.h"
#include <ctype.h>

/**********
*
*   Module:     getquotedstr
*
*   Function:   Get a "quoted" string from a stream
*
*   Input:
*
*       str     -   The location to place the string
*
*       maxlen  -   The maximum number of characters that can be stored at "str"
*
*       delimit -   The delimiter that surrounds the string in the file (normally '\"')
*
*   Output:
*
*       str     -   This will be the string, without the delimiters, and with a null
*                   terminator.
*
**********/

char *modifstream::getquotedstr(char *str,int maxlen,char delimit)
{
    char a;

    /*** discard leading white space ***/
    (*this) >> a;
    
    /*** check for leading " ***/
    if (a != delimit) {
        throw InvalidQuotedString();
    }

    /*** Read the string ***/
    char *to = str;
    for ( ; maxlen > 0; --maxlen){
        this->get(*to);
        if (this->eof()) {
            break;
        }
        if (*to == delimit) {
            *to = 0;
            return str;
        }
        if (*to == '\n') {
            throw InvalidQuotedString();
        }
        to++;
    }
    throw MaxLenExceeded();
	return NULL;  // This return is never executed, but is required by
				  // some compilers.
}

/**********
*
*   Module:     getdate
*
*   Function:   Read a date from the stream
*
*   Description:
*
*       The date must be stored in the stream in "YYYY/MM/DD" form.  (Leading zeros
*       for "MM" and "DD" are not necessary, but "YYYY" must include the century.)
*
**********/

Date modifstream::getdate()
{
    char a;
    int year,month,day;

    (*this) >> year;
    (*this) >> a;
    if (a != '/') {
        throw InvalidDate();
    }
    (*this) >> month;
    (*this) >> a;
    if (a != '/') {
        throw InvalidDate();
    }
    (*this) >> day;
    return Date(year,month,day);
}
