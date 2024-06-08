/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include "employee.h"
#include "node.h"
//#include <time.h>

using namespace std;
string get_substring(string& line);

int main(int argc, char** argv){
    //clock_t start = clock(); // start to measure

    //the map
    map<int, Employee*> employee_map;

    //opening the file
    fstream data_file;
    data_file.open(argv[1], ios::in);

    //Opening Error
    if (!data_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //Reading the data and storing it to the array
    int current_line = 1;
    string data_employee;
    int largest_id = 0;

    while(getline(data_file, data_employee)){
        //Skip first line
        if(current_line > 1){
            //split and read the data from file
            int id = stoi(get_substring(data_employee));
            int salary = stoi(get_substring(data_employee));
            int department = stoi(data_employee);

            //updating the largest id
            if(id > largest_id){
                largest_id = id;
            }

            //save the data in an employee instance
            Employee* employee = new Employee(id, salary, department);
            employee_map[employee->get_id()] = employee;
        }
        current_line++;
    }
    //closing the file 
    data_file.close();

    //Open the operation file
    fstream operation_file;
    operation_file.open(argv[2], ios::in);

    //Opening Error
    if (!operation_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //The operation's file line
    string line;

    while(getline(operation_file, line)){
            string operation = get_substring(line);

            if(operation == "ADD"){
                //updating the largest id
                largest_id++;

                //Reading and spliting the Data
                int salary = stoi(get_substring(line));
                int department = stoi(line);

                //save the data in an employee instance
                Employee* employee = new Employee(largest_id, salary, department);
                //add it to the map
                employee_map[employee->get_id()] = employee;
     
            }
            if(operation == "UPDATE"){
                //get new data from the file
                int id = stoi(get_substring(line));
                int salary = stoi(get_substring(line));
                int department = stoi(line);

                //iterator to find the id
                map<int, Employee*>::iterator itr = employee_map.find(id);

                //ID found
                if(itr != employee_map.end()){
                    itr->second->set_salary(salary);
                    itr->second->set_department(department);
                }else{
                    //ID not found
                    cout << "ERROR: An invalid ID to update\n";
                }

            }
            if(operation == "DELETE"){
                //get new data from the file
                int id = stoi(get_substring(line));

                //check if empty
                if(employee_map.empty()){
                    cout << "ERROR: There is no Employee\n";
                }else{
                    //iterator to find the ID
                    map<int, Employee*>::iterator itr = employee_map.find(id);

                    //ID not found
                    if(itr == employee_map.end()){
                        cout << "ERROR: An invalid ID to delete\n";
                    }else{
                        //ID found
                        employee_map.erase(itr);
                        delete itr->second;
                    }
                }
        }
    }

    //closing the file
    operation_file.close();


    //creating the csv file
    fstream my_result_file;
    my_result_file.open("output.csv", ios::out);

    //Opening Error
    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //string stream to write
    stringstream all_employees;

    all_employees <<"Employee_ID;Salary;Department" <<endl;

    //Iterator to write the data
    map<int, Employee*>::iterator itr;

    for(itr = employee_map.begin(); itr != employee_map.end(); ++itr){
        all_employees << itr->first << ";"
                      << employee_map[itr->first]->get_salary() << ";"
                      << employee_map[itr->first]->get_department() <<"\n";
        delete itr->second;
    }
    my_result_file << all_employees.rdbuf();

    //closing the file
    my_result_file.close();


    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of map solution in ms is: " << duration_in_ms << endl; 


    return 0;
}
string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;
}
