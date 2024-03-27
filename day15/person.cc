#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Person{
public:
    Person(const char *name, const int age)
    : _name(new char[strlen(name) + 1]())
    , _age(age)
    {
        strcpy(_name, name);
    }

    ~Person(){
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }

    Person(const Person & per)
    : _name(new char[strlen(per._name) + 1]())
    , _age(per._age)
    {
        strcpy(_name, per._name);
    }

    Person & operator=(const Person & per){
        if(this != &per){
            delete [] _name;
            _name = new char[strlen(per._name) + 1]();
            strcpy(_name, per._name);
            _age = per._age;
        }
        return *this;
    }

    void display() const{
        cout << "name: " << _name << endl;
        cout << "age: " << _age << endl;
    }

private:
    char *_name;
    int _age;
};

class Employee
: public Person
{
public:
    Employee(const char *name, const int age, const char *department, const double salary)
    : Person(name, age)
    , _department(new char[strlen(department) + 1]())
    , _salary(salary)
    {
        strcpy(_department, department);
    }

    ~Employee(){
        if(_department){
            delete [] _department;
            _department = nullptr;
        }
    }

    Employee(const Employee & emp)
    : Person(emp)
    , _department(new char[strlen(emp._department) + 1]())
    , _salary(emp._salary)
    {
        strcpy(_department, emp._department);
    }

    Employee & operator=(const Employee & emp){
        if(this != &emp){
            Person::operator=(emp);
            delete [] _department;
            _department = new char[strlen(emp._department) + 1]();
            strcpy(_department, emp._department);
            _salary = emp._salary;
        }
        return *this;
    }

    void display(){
        Person::display();
        cout << "department: " << _department << endl;
        cout << "salary: " << _salary << endl;
    }

private:
    char *_department;
    double _salary;
};

int main(){
    Employee e1("Li", 13, "HR", 10000);
    Employee e2("Hua", 50, "CEO", 100);
    Employee e3 = e2;
    e3.display();
    cout << "---------------" << endl;
    e2 = e1;
    e2.display();

    return 0;
}
