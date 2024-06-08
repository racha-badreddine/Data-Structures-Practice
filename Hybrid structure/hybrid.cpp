/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "employee.h"
#include "node.h"
#include "binary_tree.h"
//#include <time.h>

using namespace std;

string get_substring(string& line);

int main(int argc, char** argv){
    //clock_t start = clock(); // start to measure

    vector<BinaryTree*> employee_vector;

    //max node number in each tree
    int tree_size = 5000;

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
            //index of the tree we should add to
            int tree_num = id / tree_size;

            //current vector size
            int vector_size = employee_vector.size();

            //to find the right tree to add to
            if(tree_num >= vector_size){
                for(int i = vector_size - 1; i < tree_num; i++){
                    employee_vector.push_back(new BinaryTree());
                }
            }

            employee_vector[tree_num]->insert(new Employee(id, salary, department));

            //updating largest ID
            if(id > largest_id){
                largest_id = id;
            }
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

            //the index to add to
            int tree_num = largest_id / tree_size;

            int vector_size = employee_vector.size();

            //adding new tree when needed
            if(tree_num >= vector_size){
                employee_vector.push_back(new BinaryTree());
            }

            employee_vector[tree_num]->insert(new Employee(largest_id, salary, department));
            
        }
        if(operation == "UPDATE"){
            //get new data from the file
            int id = stoi(get_substring(line));
            int salary = stoi(get_substring(line));
            int department = stoi(line);

            //indew of the tree
            int tree_num = id / tree_size;

            int vector_size = employee_vector.size();

            //in case the index is bigger than the size
            if(tree_num >= vector_size){
                cout << "ERROR: An invalid ID to update\n";
            }else{
                employee_vector[tree_num]->update(id, salary, department);
            }
            
        }
        if(operation == "DELETE"){
            //get new data from the file
            int id = stoi(get_substring(line));

            int tree_num = id / tree_size;
            int vector_size = employee_vector.size();

            //check if vector is empty
            if(employee_vector.size() == 0){
                cout << "ERROR: There is no Employee\n";
            }else if(tree_num >= vector_size){
                cout << "ERROR: An invalid ID to delete\n";
            }else {
                employee_vector[tree_num]->remove(id);
            }     
        }
    }
    //closing the file
    operation_file.close();

    //creating the csv file
    ofstream my_result_file;
    my_result_file.open("output.csv");

    //Opening Error
    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    my_result_file << "Employee_ID;Salary;Department" <<'\n';

    //printing
    int size = employee_vector.size();
    for(int j = 0; j < size ; j++){
        employee_vector[j]->printToFile(my_result_file);
    }
    
    //closing the file
    my_result_file.close();

    for(int j = 0; j < size ; j++){
        delete employee_vector[j];
    }

    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of hybrid solution in ms is: " << duration_in_ms << endl; 

    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}
