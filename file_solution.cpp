/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 28/10/2023 > */
#include <iostream>
#include <fstream>
#include <sstream>
//#include <time.h>

using namespace std;

string get_substring(string& line);
int file_lines_number(fstream &file);

int main(int argc, char** argv) {

    //clock_t start = clock(); // start to measure

    //opening the file /*GIVE  IT AS ARGUMENT*/
    fstream my_file;
    my_file.open(argv[1], ios::in | ios::out);

    if (!my_file.is_open()) {
    cerr << "File could not be opened!" << endl;
    }

    int largest_id = file_lines_number(my_file) - 1;
    /*I OPENED THE FILE TO CALCULATE THE LARGEST ID AND CLOSED IT TO START APPLYING OPERATIONS*/

    my_file.close();

    //opening the operation file
    fstream operation_file;
    operation_file.open(argv[2], ios::in);

    if (!operation_file.is_open()) {
        cerr << "File could not be opened!" << endl;
    }

    string line;

    while(getline(operation_file,line )){

        fstream my_file;
        my_file.open(argv[1], ios::in | ios::out);

        if (!my_file.is_open()) {
        cerr << "File could not be opened!" << endl;
        }


        //the data that i will take from the file
        string id = "";
        string salary = "";
        string department = "";
        string operation = get_substring(line);
        
        if(operation == "ADD"){

            my_file.seekp(0, ios::end);

            //getting data from operation file
            salary = get_substring(line);
            department = line;
            
            //writing into the file
            my_file << largest_id +1 << ";" << salary <<";"<< department <<"\n";

            //updating the largest id
            largest_id++;
    
        }
        if(operation == "UPDATE"){

            //getting data from operation file
            id = get_substring(line);
            salary = get_substring(line);
            department = line;


            string data_s;
            string employees_id;

            //to read from beggining
            my_file.seekg(0, ios::beg); 
            my_file.seekp(0, ios::beg);
            streampos position = my_file.tellg();


            bool found = false;

            while(getline(my_file, data_s)){
                employees_id = data_s.substr(0,data_s.find(";"));
                if( employees_id == id){
                    my_file.seekp(position);
                    my_file << id << ";" << salary << ";" << department <<"\n";
                    found = true;
                    break;     
                }
                position = my_file.tellg();
            }

            //Invalid ID
            if(found == false){
                cout << "ERROR: An invalid ID to update" << "\n";
            }            
                  
         }
        if(operation == "DELETE"){
            ////getting data from operation file
            id = get_substring(line); //here \r is a problem
            id = id.substr(0, id.find("\r"));

            //Empty file
            my_file.seekg(0, ios::end);//go to the end of file
            streampos file_size = my_file.tellg();

            if(file_size == 0){
                cout << "ERROR: There is no Employee" <<"\n";
            }

            // to start reading from begining
            my_file.seekg(0, ios::beg); 
            my_file.seekp(0, ios::beg);
            
            //creating new file
            fstream new_file;
            new_file.open("new2.csv", ios::app);

            if (!new_file.is_open()) {
                cerr << "File could not be opened!" <<endl;
        }

            string data_s;
            string employees_id;

            stringstream all_employees;

            while(getline(my_file, data_s)){
                employees_id = data_s.substr(0,data_s.find(";"));
                if (employees_id == id){
                        //skip this employee
                }else{
                    all_employees << data_s <<endl;
                }
            }
            

            //write into the file
            new_file << all_employees.rdbuf();

            //close the file
            new_file.close();
            my_file.close();

            //remove previous one and rename
            remove(argv[1]);
            rename("./new2.csv", argv[1]);
        }


    }

    //closing the files
    operation_file.close();

    //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of file solutions in ms is: " << duration_in_ms << endl; 
    
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