/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "employee.h"
#include "node.h"
#include "binary_tree.h"
//#include <time.h>

using namespace std;


string get_substring(string& line);

int main(int argc, char** argv){
    //clock_t start = clock(); // start to measure

    BinaryTree* tree = new BinaryTree();
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

            if(id > largest_id){
                largest_id = id;
            }

            //save the data in an employee instance
            Employee* employee = new Employee(id, salary, department);
            tree->insert(employee);
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

        if(line == "PRINT\r" || line == "PRINT"){
            cout<< "P\n"; tree->printToConsole();
        }else if(line == "HEIGHT\r" || line == "HEIGHT"){
            cout<< "H "<< tree->getHeight()<<"\n";
        }else{
               string operation = get_substring(line);

            if(operation == "ADD"){
                //updating the largest id
                largest_id++;

                //Reading and spliting the Data
                int salary = stoi(get_substring(line));
                int department = stoi(line);

                tree->insert(new Employee(largest_id, salary, department));
            }
            if(operation == "UPDATE"){
                //get new data from the file
                int id = stoi(get_substring(line));
                int salary = stoi(get_substring(line));
                int department = stoi(line);


                tree->update(id,salary,department);

            }
            if(operation == "DELETE"){
                //get new data from the file
                int id = stoi(get_substring(line));

                //empty tree
                if(tree->get_root() == NULL){
                    cout << "ERROR: There is no Employee\n";
                }
                tree->remove(id);
            }

        }

    }
    
    //creating the csv file
    ofstream my_result_file;
    my_result_file.open("output.csv");

    //Opening Error
    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    my_result_file << "Employee_ID;Salary;Department" <<endl; 
    //printing to file
    tree->printToFile(my_result_file);

    //closing the file
    my_result_file.close();

    delete tree;
    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of binary tree solution in ms is: " << duration_in_ms << endl; 
    
    
    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}
