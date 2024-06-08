/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 08/01/2024 > */
#include <iostream>
#include <fstream>
#include <string>
#include "employee.h"
#include "quadraply_skiplist.h"
//#include <time.h>

using namespace std;


string get_substring(string& line);

int main(int argc, char** argv){
    //clock_t start = clock(); // start to measure

    //14 as max height for better performance 
    QuadruplySkipList* mySkipList = new QuadruplySkipList(14);

    //opening the file
    fstream data_file;
    data_file.open(argv[1], ios::in);

    //Opening Error
    if (!data_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //Reading the data and storing it
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

            if(id > largest_id){
                largest_id = id;
            }

            //save the data in an employee instance
            Employee* employee = new Employee(id, salary, department);
            mySkipList->insert(employee);
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

            mySkipList->insert(employee);

        }
        if(operation == "UPDATE"){
            //get new data from the file
            int id = stoi(get_substring(line));
            int salary = stoi(get_substring(line));
            int department = stoi(line);

            //search foe the employee
            Employee* employee_to_update = mySkipList->search(id);

            if(employee_to_update == NULL){
                //Not Found
                cout << "ERROR: An invalid ID to update\n";
            }else{
                //Found->update
                employee_to_update->set_salary(salary);
                employee_to_update->set_department(department);
            }

        }
        if(operation == "DELETE"){
            //get new data from the file
            int id = stoi(get_substring(line));

            if(mySkipList->isempty()){
                //empty SkipList
                cout << "ERROR: There is no Employee\n";
            }else{
                mySkipList->remove(id);
            }
  
        }

    }

    //creating the csv file
    ofstream my_result_file;
    my_result_file.open("quadruply_output.csv");

    //Opening Error
    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    my_result_file << "Employee_ID;Salary;Department" <<endl; 
    //printing to file
    mySkipList->dumpToFile(my_result_file);

    //free memory
    delete mySkipList;

    //closing the file
    my_result_file.close();

    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of Quadruply SkipList solution in ms is: " << duration_in_ms << endl; 


    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}












