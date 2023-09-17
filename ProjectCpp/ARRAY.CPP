/***********
*
*   File:       array.cpp
*
*   Function:   Functions relating to arrays
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Also:       Do NOT include this as one of the files in your project.  It will
*               be compiled automatically because it is #include'd by array.h.
*
**********/
#ifndef ARRAY_CPP

#define ARRAY_CPP

#include "array.h"
/**********
*
*   Module:     Array
*
*   Function:   Constructor
*
**********/

template<class T>
Array<T>::Array(int size)
{
    storage = new T[size];
    storageCount = size;
}

/**********
*
*   Module:     ~Array
*
*   Function:   Destructor
*
**********/

template<class T>
Array<T>::~Array()
{
    delete [] storage;
}

/**********
*
*   Module:     operator []
*
*   Function:   Locate an element of the array
*
*   Note:       If the requested element is outside the current bounds of the array,
*               the size of the array is expanded to include the index (plus some
*               growing space).
*
**********/

template<class T>
T &Array<T>::operator [](int index)
{
    if (index < 0) {
        throw IndexOutOfRange();
    }
    if (index < storageCount) {
        return storage[index];
    }

    int newStorageCount = (index+1) + storageCount/2;
    T *newStorage = new T[newStorageCount];
    memmove(newStorage,storage,sizeof(T)*storageCount);
    delete [] storage;
    storage = newStorage;
    storageCount = newStorageCount;
    return storage[index];
}

#endif