/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#pragma once
class Employee{
    private:
        int id;
        int salary;
        int department;
    public:
        Employee(int,int,int);
        ~Employee();
        void set_salary(int);
        void set_id(int); 
        void set_department(int);
        int get_id();
        int get_salary();
        int get_department();
};
Employee::Employee(int id, int salary, int department){
    this->id = id;
    this->salary = salary;
    this->department = department;
}

Employee::~Employee(){
}

void Employee::set_salary(int salary){
    this->salary = salary;
}
void Employee::set_id(int id){
    this->id = id;
}
void Employee::set_department(int department){
    this->department = department;
}
int Employee::get_id(){
    return id;
}

int Employee::get_salary(){
    return salary;
}

int Employee::get_department(){
    return department;
}

