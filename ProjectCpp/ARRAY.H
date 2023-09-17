/***********
*
*   File:       array.h
*
*   Function:   Structures relating to arrays
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Description:
*
*       The "array" class provides the functionality of standard C++ arrays, but in a way
*       that allows them to expand as necessary.  If you reference an index of the array
*       that is outside its bounds, the array is automatically increased in size to
*       include that index.
*
**********/
#ifndef ARRAY_DEF

#define ARRAY_DEF

template<class T>
class Array {

public:
    class InsufficientMemory { };
    class IndexOutOfRange { };

protected:
    T           *storage;
    int         storageCount;

public:
                Array(int size);
                ~Array();
    T           &operator [](int index);
};

#include "array.cpp"

#endif
