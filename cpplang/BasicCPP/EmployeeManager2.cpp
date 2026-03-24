#include <iostream>
#include <cstring>
using namespace std;

class Employee
{
private:
	char name[100];
public:
	Employee(char* name)
	{
		strcpy(this->name, name);
	}

	Employee(const Employee& e) 
	{
		strcpy(this->name, e.name);
	}

	void ShowYourName() const
	{
		cout<<"name: "<<name<<endl;
	}

	virtual void ShowSalaryInfo() const { }
	virtual int GetPay() const { return 0; }
};

class PermanentWorker : public Employee
{
private:
	int salary;
public:
	PermanentWorker(char* name, int money)
		: Employee(name), salary(money)
	{  }

	PermanentWorker(const PermanentWorker& worker)
		: Employee(worker), salary(worker.salary)
	{ }

	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout<<"salary: "<<GetPay()<<endl<<endl;
	}
};

class EmployeeHandler
{
private:
	Employee* empList[50];
	int empNum;
public:
	EmployeeHandler() : empNum(0) 
	{ }
	void AddEmployee(Employee* emp)
	{
		empList[empNum++]=emp;
	}
	void ShowAllSalaryInfo() const
	{
		for(int i=0; i<empNum; i++)
			empList[i]->ShowSalaryInfo();
	}
	void ShowTotalSalary() const
	{
		int sum=0;
		for(int i=0; i<empNum; i++)
			sum+=empList[i]->GetPay();

		cout<<"salary sum: "<<sum<<endl;
	}
	~EmployeeHandler()
	{
		for(int i=0; i<empNum; i++)
			delete empList[i];
	}
};

class RefEmployeeHandler
{
private:
	Employee* empList[50];
	int empNum;
public:
	RefEmployeeHandler() : empNum(0) 
	{ }
	void AddEmployee(Employee& emp)
	{
		empList[empNum++] = new Employee(emp);
	}
	void ShowAllSalaryInfo() const
	{
		cout << "RefHandler" << endl;

		for(int i=0; i<empNum; i++)
			empList[i]->ShowSalaryInfo();
	}
	void ShowTotalSalary() const
	{
		cout << "RefHandler" << endl;

		int sum=0;
		for(int i=0; i<empNum; i++)
			sum+=empList[i]->GetPay();

		cout<<"salary sum: "<<sum<<endl;
	}
	~RefEmployeeHandler()
	{
		for(int i=0; i<empNum; i++)
			delete empList[i];
	}
};

int main(void)
{
	// ?????????? ???????? ????? ????? ??????? ???????
	EmployeeHandler handler;
	RefEmployeeHandler rhandler;

	// ???? ???
	PermanentWorker w = PermanentWorker("Park", 1000);
	PermanentWorker* p = new PermanentWorker("Song", 1500);

	Employee* xw = new Employee(w);

	handler.AddEmployee(xw);
	handler.AddEmployee(p);

	handler.AddEmployee(new PermanentWorker("Kim", 1000));
	handler.AddEmployee(new PermanentWorker("Lee", 1500));
	handler.AddEmployee(new PermanentWorker("JUN", 2000));

	// REF TEST
	rhandler.AddEmployee(w);
	rhandler.AddEmployee(*p);

	// ??? ??? ??????? ?? ????? ????
	handler.ShowAllSalaryInfo();	

	// ??? ??? ??????? ?? ????? ????
	handler.ShowTotalSalary();

	rhandler.ShowAllSalaryInfo();
	rhandler.ShowTotalSalary();

	cout << sizeof(handler) << endl;
	return 0;
}