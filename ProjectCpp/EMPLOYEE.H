/***********
*
*   File:       employee.h
*
*   Function:   Structures relating to employees
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
*   Description:
*
*       Each object of the "Employee" class represents one record in the employee file.
*       These records are automatically located and read for you when you create an
*       object of this class.  New employee records can also be added to the file
*       by creating an object of this class.
*
**********/

#ifndef EMPLOYEE_DEF

#define EMPLOYEE_DEF
#include "ARRAY.H"
using namespace std;

const int EmpNameMax=32;

enum SalaryType {
    SalTypeEmpty=-1,
    SalTypeSalary=0,
    SalTypeHourly=1
};

enum EmpStatus {
    EmpStatusActive=0,
    EmpStatusInactive=1
};

#include <windows.h>
#include <iostream>
#include <fstream>

#include "date.h"
#include "emptrans.h"
#include <stdio.h>
#include <string.h>
#include "array.h"

class Employee {

struct Location {               // Each such structure keeps track of the location in
                                // the employee file of a single employee record.
    int         number;
    long        location;
};

protected:
    static FILE *file;          // The employee file (or NULL if it's closed)
    static Array<Location> locationList; // A list of the locations of each employee record
    static int  locationCount;  // The number of elements in "locationList[]".
    static int  highestNumber;  // The highest employee number assigned so far
    static long highestLocation;// The location to place the next employee record added to the file

protected:
    char        name[EmpNameMax];
    long        location;       // The offset from the start of the file of employee's record
    int         number;         // Unique ID number
    long        salary;         // annual salary in dollars or hourly wage in cents
    SalaryType  salaryType;
    Date        hireDate;
    EmpStatus   status;         // Is this an active employee?

public:
    class       EmployeeError { };
	class       NoSuch: public EmployeeError { };		// Employee with that number not found
    class       CantOpenFile: public EmployeeError { }; // Can't find the employee file
    class       EndOfFile { };           // End of file on call to Read()

public:
                Employee();
    void        Read(int number);	    // Find employee in employee master file
    void        Add();                  // Add the employee to the file
	static void	List();					// List all the employees (used for debugging)
    void        Remove();               // Remove the employee from the file
    void        Update();               // Save changes made to the employee in the file
    static void Open();                 // Prepare to process the employee master file
    static void Close();                // End processing of employee master file

    friend void EmpTransAdd::Apply(Employee &employee);
    friend void EmpTransChange::Apply(Employee &employee);
    friend void EmpTransDelete::Apply(Employee &employee);

protected:
    void        Read();                 // Read employee record from file
};

#endif
