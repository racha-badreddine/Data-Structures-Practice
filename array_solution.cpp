/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 28/10/2023 > */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <time.h>

using namespace std;

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
int file_lines_number(fstream &file);
void copy_arrays(Employee* original, int size_ , Employee* copied);


int main(int argc, char** argv) {
   // clock_t start = clock(); // start to measure
    
    //opening the file
    fstream new_file;
    new_file.open(argv[1], ios::in);

    if (!new_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //Getting the size of the array
    int size = file_lines_number(new_file) - 1; //we do include first line in the array
  
    //Creating the array dynamically
    Employee* Employees = new Employee[size];
    
    //Reading the data and storing it to the array
    int current_line = 1;
    string data_employee;

    //to get the substrings form file
    string id = "";
    string salary = "";
    string department = "";

    while(getline(new_file, data_employee)){
        //here the first line is only a description
        if(current_line > 1){
            //split the data
            id = get_substring(data_employee);
            salary = get_substring(data_employee);
            department = data_employee;
            
            //store the data in the array
            (Employees + (current_line - 2))->set_id(stoi(id));
            (Employees + (current_line - 2))->set_salary(stoi(salary));
            (Employees + (current_line - 2))->set_department(stoi(department));

        }
        current_line++;       
    }

    //Keeping the largest ID 
    int largest_id = size;

    //closing the file
    new_file.close();
    
    //Open the operation file
    fstream operation_file;
    operation_file.open(argv[2], ios::in);

    if (!operation_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //Search of we have ADD
    string line;
    while(getline(operation_file, line)){
        string operation = get_substring(line);

        if(operation == "ADD"){
            //Adding one to size
            size++;

            //creating new array with new size and copy data to it
            Employee* temp_array = new Employee[size];
            copy_arrays(Employees,(size - 1), temp_array);

            //deallocate previous array
            delete[] Employees;
            
            //change the pointer to the new array
            Employees = temp_array;

            //get new data from the file
            salary = get_substring(line);
            department = line;

            //updating the largest id
            largest_id++;

            //Add new employee at the end
            (Employees +(size -1))->set_id(largest_id);
            (Employees +(size -1))->set_salary(stoi(salary));
            (Employees +(size -1))->set_department(stoi(department));

        }

        if(operation == "UPDATE"){

            //get new data from the file
            id = get_substring(line);
            salary = get_substring(line);
            department = line;
            
           //to check the validity of the ID 
            bool found = false;

            //Update the employee 
            for(int i = 0;i < size; i++){
                if(stoi(id) == (Employees + i)->get_id()){
                    (Employees + i)->set_salary(stoi(salary));
                    (Employees + i)->set_department(stoi(department));
                    found = true;
                    break;
                }
            }
            //invalid ID
            if(found == false){
                cout << "ERROR: An invalid ID to update ";
            }
        }

        if(operation == "DELETE"){
            
            //get new data from the file
            id = get_substring(line);

            //Empty array
            if(size == 0){
                cout << "ERROR: There is no Employee\n";
            }

            //to check the validity of the ID
            bool found = false;

            //valid ID
                for(int i = 0;i < size; i++){
                if(stoi(id) == (Employees + i)->get_id()){
                    //decrementing the size
                    size--;

                    //creating new array 
                    Employee* temp_array = new Employee[size];
                    //copying elements before the one to be deleted
                    copy_arrays(Employees,i, temp_array);

                    //copying elements after the deleted one
                    for(int j = i; j < size;j++){
                        (temp_array + j)->set_id((Employees + j + 1)->get_id());
                        (temp_array + j)->set_salary((Employees + j + 1)->get_salary());
                        (temp_array + j)->set_department((Employees + j + 1)->get_department());
                    }
                    //deallocate memory 
                    delete[] Employees;
                    //make the array points to the new one
                    Employees = temp_array;
                    
                    //valid ID
                    found = true;

                    break;
                }
            }

            //invalid ID
            if(found == false){
                cout << "ERROR: An invalid ID to delete ";
            }
        }
    }
    
    //closing the file
    operation_file.close();

    //creating the csv file
    ofstream my_result_file;
    my_result_file.open("array_solution.csv");

    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    stringstream all_employees;


    all_employees <<"Employee_ID;Salary;Department" <<endl;

    for(int j = 0; j < size; j++){
        all_employees << Employees[j].get_id() << ";" 
                       << Employees[j].get_salary() << ";" 
                       << Employees[j].get_department() << endl;
    }

    my_result_file << all_employees.rdbuf();
    //deallocate memory
    delete[] Employees;

    //closing the file
    my_result_file.close();

   // clock_t end = clock();

    //measurement time in milliseconds
   // double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

   // cout << "Duration of array solution in ms is: " << duration_in_ms << endl; 

    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}

int file_lines_number(fstream &file){
    int line_num = 0;
    string line;

    while(getline(file,line)){
        line_num++;
    }

    file.clear();
    file.seekg(0, ios::beg);
    return line_num;

}
void copy_arrays(Employee* original, int size_ , Employee* copied){
    for(int i =0; i < size_ ; i++){
        (copied + i)->set_id((original+ i)->get_id());
        (copied + i)->set_salary((original+ i)->get_salary());
        (copied + i)->set_department((original+ i)->get_department());
    }
}




