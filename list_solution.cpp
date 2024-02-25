/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 10/11/2023 > */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
//#include <time.h>

using namespace std;

//Employee class declarations and definitions
class Employee{
    private:
        int id;
        int salary;
        int department;
    public:
        Employee();
        ~Employee();
        void set_salary(int);
        void set_id(int); 
        void set_department(int);
        int get_id();
        int get_salary();
        int get_department();
};

Employee::Employee(){
    this->id =0;
    this->salary =0;
    this->department =0;
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

string get_substring(string& line);

int main(int argc, char** argv){
    //clock_t start = clock(); // start to measure

    //opening the file
    fstream new_file;
    new_file.open(argv[1], ios::in);

    //Opening Error
    if (!new_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    list<Employee> employees_list;

    //Reading the data and storing it to the array
    int current_line = 1;
    string data_employee;

    //to get the substrings form file
    int id = 0;
    int salary = 0;
    int department = 0;

    while(getline(new_file, data_employee)){
        //here the first line is only a description
        if(current_line > 1){
            //split the data
            id = stoi(get_substring(data_employee));
            salary = stoi(get_substring(data_employee));
            department = stoi(data_employee);

            //create employee object
            Employee employee;

            employee.set_id(id);
            employee.set_salary(salary);
            employee.set_department(department);

            //Push the employee to the list
            employees_list.push_back(employee);
            
        }
        current_line++;       
    }

    int largest_id = current_line -2; //to keep largest id

    //closing the file
    new_file.close();


    //Open the operation file
    fstream operation_file;
    operation_file.open(argv[2], ios::in);

    //Opening Error
    if (!operation_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }


    string line;

    while(getline(operation_file, line)){
        string operation = get_substring(line);

        if( operation == "ADD"){

            //update the largest ID and size
            largest_id++;

            //get new data from the file
            salary = stoi(get_substring(line));
            department = stoi(line);

            //creating an employee object
            Employee employee_toadd;
            employee_toadd.set_id(largest_id);
            employee_toadd.set_salary(salary);
            employee_toadd.set_department(department);
            //Push it to the list
            employees_list.push_back(employee_toadd);

        }
        

        if(operation == "UPDATE"){

            //get new data from the file
            id = stoi(get_substring(line));
            salary = stoi(get_substring(line));
            department = stoi(line);

            //to check the validity of the ID 
            bool found = false;

            //Iterate the list and update
            for(list<Employee>::iterator it = employees_list.begin(); it!= employees_list.end();++it){
                if(it->get_id() == id){
                    it->set_salary(salary);
                    it->set_department(department);
                    found =true;      
                }
            }
            //Invalid ID
            if(found == false){
                cout << "ERROR: An invalid ID to update";
            }
        }
        if(operation =="DELETE"){
            //get new data from the file
            id = stoi(get_substring(line));
            if(employees_list.empty()){
                cout << "ERROR: There is no Employee\n";
            }
            //to check the validity of the ID
            bool found = false;

            //Iterate the list and delete
            for(list<Employee>::iterator it = employees_list.begin(); it!= employees_list.end();++it){
                if(it->get_id() == id){
                    employees_list.erase(it);
                    found = true;
                    break;
                }
            }
             //invalid ID
            if(found == false){
                cout << "ERROR: An invalid ID to delete";
            }
        }

    }

    //closing the file
    operation_file.close();

    //creating the csv file
    fstream my_result_file;
    my_result_file.open("list_solution.csv", ios::out);

    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    stringstream all_employees;

    all_employees <<"Employee_ID;Salary;Department" <<endl;

    for(list<Employee>::iterator it = employees_list.begin(); it!= employees_list.end();++it){
        all_employees << it->get_id() << ";" 
                       << it->get_salary() << ";" 
                       << it->get_department() << endl;
    }

    my_result_file << all_employees.rdbuf();

    //closing the file
    my_result_file.close();

    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of list solution in ms is: " << duration_in_ms << endl; 

    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}








