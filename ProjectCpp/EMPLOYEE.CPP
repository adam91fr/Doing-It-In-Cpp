/***********
*
*   File:       employee.cpp
*
*   Function:   Functions relating to employees
*
*   Note:       This is part of the example program in "Doing It In C++", a multimedia
*               CD-ROM.
*
**********/


#include "employee.h"
//#define _SCL_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
using namespace std;

FILE *Employee::file=NULL;
Array<Employee::Location> Employee::locationList(1);
int Employee::locationCount = 0;
int Employee::highestNumber = 0;
long Employee::highestLocation = 0;

/**********
*
*   Module:     Employee
*
*   Function:   Constructor
*
**********/

Employee::Employee()
{
    memset(name,0,EmpNameMax);
    number = -1;
    location = -1;
    salaryType = SalTypeSalary;
    salary = 0;
    status = EmpStatusActive;
    hireDate.Set(1901,1,1);
}

/**********
*
*   Module:     Open
*
*   Function:   Open the employee file and build the index
*
*   Description:
*
*       This module is not called directly by a user of the class.  Instead, it is
*       called by Employee::Read() if the file hasn't been opened yet.
*
*   Note:
*
*       The list of employee records which is stored in "locationList" isn't in any
*       particular order.  A future enhancement that could improve this code would be
*       to keep the list in sorted order so that locating a given employee record's
*       location would be faster.
*
**********/

void Employee::Open()
{
    Employee employee;

    if (file == NULL) {
        file = fopen("employee.dat","r+b");
        if (file == NULL) {
            file = fopen("employee.dat","w+b");
            if (file == NULL) {
                throw CantOpenFile();
            }
        }
        fseek(file,0,0);
        for (locationCount=0; ; ++locationCount) {
            locationList[locationCount].location = ftell(file);
            try {
                employee.Read();
            }
            catch(EndOfFile) {
                break;
            }
            if (employee.number > highestNumber) {
                highestNumber = employee.number;
            }
            locationList[locationCount].number = employee.number;
        }
        highestLocation = ftell(file);
    }
}

/**********
*
*   Module:     Add
*
*   Function:   Add an employee to the file
*
*   Description:
*
*       Before calling this function, all the data members of the object should
*       be given values except "number" and "location"--they are set by this
*       function.  The "number" assigned will be one higher than the highest
*       number currently in the file.
*
**********/

void Employee::Add()
{

    this->number = locationList[locationCount].number = ++highestNumber;
    location = locationList[locationCount++].location = highestLocation;
    Update();
    highestLocation = ftell(file);

}

/**********
*
*	Module:		List
*
*	Function:	Display all the employees on the screen
*
*	Note:
*
*		If you have very many employees, this isn't a useful thing to
*		do.  But it can be helpful during testing when you have just
*		a few of them.
*
**********/

void Employee::List()
{
	Employee employee;

	fseek(file,0,0);
	try {
		for (;;) {
			employee.Read();
			cout << "*** Employee number " << employee.number << " ***" << endl;
			cout << "Status=" << employee.status << endl;
			cout << "Name=" << employee.name << endl;
			cout << "Salary type=" << employee.salaryType << endl;
            cout << "Salary=" << employee.salary << endl;// << endl;

            //?????
            cout << "Hire Date=" << employee.hireDate.Year();
            cout << "/" << employee.hireDate.Month();
            cout << "/" << employee.hireDate.Day() << endl << endl;
		}
	}
	catch (EndOfFile) {
		/* do nothing */
	}
}

/**********
*
*   Module:     Read
*
*   Function:   Read an employee from the file
*
***********/

void Employee::Read(int number)
{
    int i;

    for (i=0; i<locationCount; ++i) {
        if (locationList[i].number == number) {
            break;
        }
    }
    if (i == locationCount) {
        throw NoSuch();
    }
    fseek(file,locationList[i].location,0);
    Read();
}

/**********
*
*   Module:     Read
*
*   Function:   Read an employee from the master file
*
*   Note:       The file is presumed to have been opened and indexed by Employee::Employee().
*               The position in the file is also presumed to have been set.  (This isn't
*               an appropriate routine for an application program to use directly.
*               it is intended to be used by Employee::Read().)
*
**********/

void Employee::Read()
{
    int len;

    location = ftell(file);
    len = fread(&number, sizeof(number), 1, file);
    if (len != 1) {
        throw EndOfFile();
    }
    fread(&status, sizeof(status), 1, file);
    fread(&name, EmpNameMax, 1, file);
    fread(&salaryType, sizeof(SalaryType), 1, file);
    fread(&salary, sizeof(salary), 1, file);
    hireDate.Read(file);
}

/**********
*
*   Module:     Update
*
*   Function:   Write changes in an Employee object to the employee file
*
*   Description:
*
*       To change an employee record, you would normally (1) create an Employee object
*       for the employee, (2) modify the data members of that object, and then (3)
*       call this Update() function.
*
**********/

void Employee::Update()
{
    fseek(file,location,0);
    fwrite(&number,sizeof(number),1,file);
    fwrite(&status,sizeof(status),1,file);
    fwrite(&name,EmpNameMax,1,file);
    fwrite(&salaryType,sizeof(SalaryType),1,file);
    fwrite(&salary,sizeof(salary),1,file);
    hireDate.Write(file);
}


/**********
*
*   Module:     Close
*
*   Function:   Close the employee file
*
*   Description:
*
*       The employee file is automatically opened for you by Employee::Employee().
*       But, when you're all done dealing with employees (probably when your program
*       is done), you should call this function to close the file.
*
**********/

void Employee::Close()
{
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
