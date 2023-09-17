/***********
*
*   File:       emptrans.cpp
*
*   Function:   Functions relating to employee transactions
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
**********/

#include "employee.h"
#include "modifstm.h"
#include "string.h"

#include "emptrans.h"

#pragma warning(disable : 4996)

modifstream *EmpTrans::stream = NULL;

/**********
*
*   Module:     ReadNext
*
*   Function:   Read the next transaction record in the file
*
*   Output:
*
*       return  -   This will be a pointer to an EmpTrans object.  (Actually, it will be
*                   an EmpTransAdd, EmpTransChange, or EmpTransDelete object.)
*
**********/

EmpTrans *EmpTrans::ReadNext()
{
    EmpTrans *empTrans;
    char transactionType;
    char a;

    (*stream) >> transactionType;
    if (stream->eof()) {
        throw NoMore();
    }
    if (transactionType == 'A') {
        empTrans = new EmpTransAdd;
        empTrans->ReadBody();
        empTrans->number = -1;
    } else if (transactionType == 'C') {
        empTrans = new EmpTransChange;
        (*stream) >> empTrans->number;
        empTrans->ReadBody();
    } else if (transactionType == 'D') {
        empTrans = new EmpTransDelete;
        (*stream) >> empTrans->number;
    } else {
        throw InvalidType();
    }
    do {
        stream->get(a);
    } while ( (!stream->eof()) && (a != '\n') );
    return empTrans;
}

/**********
*
*   Module:     Apply
*
*   Function:   Apply a transaction to an employee
*
*   Description:
*
*       This isn't a real function.  Calling it will normally cause the Apply() function
*       in one of the sub-classes to be called.
*
**********/

void EmpTrans::Apply(Employee &employee)
{

}

/**********
*
*   Module:     ReadBody
*
*   Function:   Read the data fields of an employee record from a transaction file
*
*   Description:
*
*       Both "Add" and "Change" transaction records have a series of fields that
*       correspond to the fields in an Employee file record.  (In fact, these fields
*       make up most of an "add" or "change" transaction record.)  This function reads
*       this series of fields.
*
**********/

void EmpTrans::ReadBody()
{
    char a;

    stream->getquotedstr(name,EmpNameMax);
    (*stream) >> a;
    if (a == 'S') {
        salaryType = SalTypeSalary;
    } else if (a == 'H') {
        salaryType = SalTypeHourly;
    } else if (a == '*') {
        salaryType = SalTypeEmpty;
    } else {
        throw InvalidContent();
    }
    (*stream) >> salary;
    hireDate = stream->getdate();
}

/**********
*
*   Module:     Open
*
*   Function:   Prepare to read a transaction file
*
*   Description:
*
*       Normally, a transaction file is read by a series of calls to ReadNext().  Before
*       you make such a series of calls, you should call this function, which prepares
*       the file to be read.
*
**********/

void EmpTrans::Open()
{
    if (stream == NULL) {
        stream = new modifstream((char* )"emptrans.dat");
        if (stream->bad()) {
            throw CantOpenFile();
        }
    }
    stream->seekg(0);
}

/**********
*
*   Module:     Close
*
*   Function:   Close the employee transaction file
*
**********/

void EmpTrans::Close()
{
    if (stream != NULL) {
        stream->close();
        stream = NULL;
    }
}

/**********
*
*   Module:     EmpTransAdd::Apply
*
*   Function:   Apply an "add" transaction record to an Employee object
*
**********/

void EmpTransAdd::Apply(Employee &employee)
{
    employee.salaryType = salaryType;
    employee.salary = salary;
    strcpy(employee.name,name);
    employee.hireDate = hireDate;
    employee.Add();
}

/**********
*
*   Module:     EmpTransChange::Apply
*
*   Function:   Apply a "change" transaction record to an Employee object
*
**********/

void EmpTransChange::Apply(Employee &employee)
{
    if (salaryType != SalTypeEmpty) {
        employee.salaryType = salaryType;
    }
    if (salary != 0) {
        employee.salary = salary;
    }
    if (name[0] != 0) {
        strcpy(employee.name,name);
    }
    if (hireDate.Year() != 1901) {
        employee.hireDate = hireDate;
    }
    employee.Update();
}
/**********
*
*   Module:     EmpTransDelete::Apply
*
*   Function:   Apply a "delete" transaction record to an Employee object
*
**********/

void EmpTransDelete::Apply(Employee &employee)
{
    employee.status = EmpStatusInactive;
    employee.Update();
}

