/***********
*
*   File:       emptrans.h
*
*   Function:   Structures relating to employee file transactions
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Description:
*
*       Each object of the "EmpTrans" class (and it's sub-classes) represents a single
*       record in the employee transaction file.
*
**********/

#ifndef EMPTRANS_DEF

#define EMPTRANS_DEF

#include "modifstm.h"
using namespace std;
class Employee;

class EmpTrans {

public:
    int         number;             // These fields match those in an Employee object
    char        name[EmpNameMax];
    SalaryType  salaryType;
    long        salary;
    Date        hireDate;

protected:
    static modifstream *stream;     // The stream used to access the transaction file

public:
    class       EmpTransErrors { };
    class       EmployeeNotAuthorized: public EmpTransErrors { };
    class       InvalidType: public EmpTransErrors { };
    class       InvalidContent: public EmpTransErrors { };
    class       NoMore: public EmpTransErrors { };
    class       CantOpenFile: public EmpTransErrors { };

public:
    void        ReadBody();         // Read employee data fields from a transaction record
    static EmpTrans *ReadNext();    // Read the next transaction record from the file
    static void Open();             // Prepare the file for a series of "ReadNext()" calls
    static void Close();            // Close the file after use
    virtual void Apply(Employee &employee); // Apply a transaction to an Employee object
};

class EmpTransAdd: public EmpTrans {

public:
    void        Apply(Employee &employee); // Apply an "add" transaction to an Employee object
};

class EmpTransChange: public EmpTrans {

public:
    void        Apply(Employee &employee); // Apply a "change" transaction to an Employee object
};

class EmpTransDelete: public EmpTrans {

public:
    void        Apply(Employee &employee);
};

#endif
