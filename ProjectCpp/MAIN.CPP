/***********
*
*   File:       main.cpp
*
*   Function:   Program mainline
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
**********/

#include <windows.h>
#include <iostream>
#include <fstream>
#include "employee.h"

using namespace std;
/**********
*
*   Module:     main
*
*   Function:   Program mainline
*
*   Description:
*
*       This module reads each record in the employee transaction file.  Each of
*       those transactions is then applied to the appropriate employee record.
*
**********/

int main()
{
    EmpTrans        *empTrans;
    Employee        employee;

    Employee::Open();
	Employee::List();  // Done for debugging only ??????
	EmpTrans::Open();
    for (;;) {
	try {
		empTrans = EmpTrans::ReadNext();
	    if (empTrans->number != -1) {
			employee.Read(empTrans->number);
	    }
	    empTrans->Apply(employee);
	    delete empTrans;
	}
	catch(EmpTrans::NoMore) {
		break;
	}
	catch(Employee::NoSuch) {
		cerr << "\nTransaction found for invalid employee\n"; //: ";// << empTrans->number;
	}
    }
	Employee::List();  // Done for debugging only
    Employee::Close();
    EmpTrans::Close();
	return 0;
}
