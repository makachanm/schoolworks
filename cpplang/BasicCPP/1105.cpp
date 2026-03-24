#include <iostream>
#include <string>

class Employee {
private:
    std::string name;

public:
    Employee(std::string rname) : name(rname) { }

    virtual int getPay() const = 0;
    virtual void showSalary() 
    { }

    std::string getName() {
        return this->name;
    }
};

class PermanentWorker : public Employee {
private:
    int salary;

public:
    PermanentWorker(std::string ename, int n) :
        salary(n), Employee(ename)
    { }

    int getPay() const {
        return salary;
    }

    void showSalary() {
        std::cout << "name: " << Employee::getName() << " pay: " << this->getPay() << std::endl;
    }
};

class SalesWorker : public PermanentWorker {
private:
    int sales;
    double bonus_r;

public:
    SalesWorker(std::string ename, int n, int s, double ratio) :
        PermanentWorker(ename, n), sales(s), bonus_r(ratio)
    { }

    int getPay() const {
        return (PermanentWorker::getPay() + (this->bonus_r * this->sales));
    }

    void showSalary() {
        std::cout << "name: " << Employee::getName() << " pay: " << this->getPay() << std::endl;
    }
};

class TemporaryWorker : public Employee {
private:
    int workTime;
	int payPerHour;

public:
	TemporaryWorker(std::string ename, int pay) : 
        Employee(ename), workTime(0), payPerHour(pay)
	{  }

	void AddWorkTime(int time) {
		this->workTime+=time;
	}

	int getPay() const {
		return (this->workTime * this->payPerHour);
	}

	void showSalary() {
        std::cout << "name: " << Employee::getName() << " pay: " << this->getPay() << std::endl;
	}
}; 

class EmployeeHandler {
private:
    Employee* workers[50];
    int emp_num;

public:
    EmployeeHandler() : emp_num(0) { }

    void addEmp(Employee* p) {
        this->workers[emp_num++] = p;
    }

    int showTotalSalary() {
        int sum = 0;

        for(int i = 0; i < this->emp_num; i++)
            sum += this->workers[i]->getPay();

        return sum;
    }

    void showAllSalary() {
        for(int i = 0; i < this->emp_num; i++)
            this->workers[i]->showSalary();
    }

    int showEmployeeCount() const {
        return this->emp_num;
    }
};

int main() {
    EmployeeHandler handler;

    PermanentWorker* john = new PermanentWorker("John", 100);
    PermanentWorker* alice = new PermanentWorker("Alice", 300);
    SalesWorker* tom = new SalesWorker("Tom", 200, 5, 2.0);
    TemporaryWorker* alba = new TemporaryWorker("Jung", 10);

    handler.addEmp(john);
    handler.addEmp(alice);
    handler.addEmp(tom);
    handler.addEmp(alba);

    alba->AddWorkTime(5);

    handler.showAllSalary();

    std::cout << "total: " << handler.showEmployeeCount() << std::endl;

    std::cout << "salary sum: " << handler.showTotalSalary() << std::endl;

    return 0;
}