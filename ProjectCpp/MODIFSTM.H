/***********
*
*   File:       modifstm.h
*
*   Function:   Structures relating to the "modified" iostream class
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Description:
*
*       The "modifstream" class is a modified version (i.e., a sub-class) of the
*       "ifstream" class.  This sub-class provides some additional capabilities
*       (reading a quoted string and reading a date).
*
**********/

#ifndef MODIFSTREAM_DEF

#define MODIFSTREAM_DEF

#include <fstream>
#include "date.h"

//using namespace std;

class modifstream: public std::ifstream {

public:
    class MaxLenExceeded { };
    class InvalidQuotedString { };
    class InvalidDate { };

public:
    modifstream(char *name): std::ifstream(name) { };
    char *getquotedstr(char *str,int maxlen,char delimit='\"');
    Date getdate();
};

#endif
