/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 28/10/2023 > */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
//#include <time.h>

using namespace std;

//class node declarations and definitions
class Node{
    private:
        int id;
        int salary;
        int department;
        Node* next;
    public:
        Node(int,int,int);
        ~Node();
        void set_salary(int);
        void set_id(int); 
        void set_department(int);
        void set_next(Node*);
        Node* get_next();
        int get_id();
        int get_salary();
        int get_department();
};

//Node mathods' definitions
Node::Node(int id, int salary, int department){
    this->id =id;
    this->salary =salary;
    this->department =department;
  //  this->next = NULL;
}
Node::~Node(){

}
void Node::set_salary(int salary){
    this->salary = salary;
}
void Node::set_id(int id){
    this->id = id;
}
void Node::set_department(int department){
    this->department = department;
}
void Node::set_next(Node* next){
    this->next = next;
}
int Node::get_id(){
    return id;
}
int Node::get_salary(){
    return salary;
}
int Node::get_department(){
    return department;
}
Node* Node::get_next(){
    return this->next;
}

//Linked List Declarations and Definitions
class LinkedList {
    private:
        Node* head;
        Node* tail;
    public:
    LinkedList();
    ~LinkedList();
    void add_node(int,int,int);
    void delete_node(int);
    Node* search_prev(int); //previous needed for the delete and can be used for the update
    bool contains(int);
    bool is_empty();
    void print_list(stringstream&);
    Node* get_head();

};

LinkedList::LinkedList(){
    this->head = NULL;
    this->tail = NULL;
}
LinkedList::~LinkedList(){
    Node* p =head;

    while(p->get_next() != NULL){
        head = p->get_next();
         delete p;
         p = head;
    }
    delete p;
    tail = NULL;
    head = NULL;
}

Node* LinkedList::search_prev(int id){
    Node* prev = this->head;
    if(prev->get_id() == id){
        return NULL; //first node
    }else{
        while(prev->get_next()){
            if(prev->get_next()->get_id() == id){
                return prev;
            }
            prev = prev->get_next(); 
        }
    }
    return prev; 

}
void LinkedList::add_node(int id,int salary,int department){
    Node* new_node = new Node(id, salary, department);

    if(this->head == NULL){
        head = new_node;
        tail = new_node;
    }else{
        tail->set_next(new_node);
        tail = new_node;
        tail->set_next(NULL);
    }
}
void LinkedList::delete_node(int id){
    if(head == tail){ //one node case
        delete head;
        head = NULL;
        tail= NULL;
    }else{
        Node* prev = this->search_prev(id); 

        if(prev == NULL){
            Node* temp = this->head;
            head = head->get_next();

            //Free memory
            temp->set_next(NULL);
            delete temp;
        }else if(prev->get_next() == tail){
            tail = prev;
            delete tail->get_next();
            tail->set_next(NULL);
        }else{
            Node* temp = prev->get_next();
            prev->set_next( temp->get_next());

            //Free memory
            temp->set_next(NULL);
            delete temp;
        }
        // prev == tail is not checked because we know that the node exists
    }

}
bool LinkedList::contains(int id){
    Node* current = this->head;

        while(current != NULL && current->get_id()!= id){
            current = current->get_next();
        }
    return current == NULL? false : true;
}
bool LinkedList::is_empty(){
    return head == NULL? true:false;
}
void LinkedList::print_list(stringstream& ss){
    Node* current = this->head;

    while(current != this->tail){
        ss << current->get_id() << ";" << current->get_salary() << ";" << current->get_department() <<endl ;
        current = current->get_next();
    }
    //for the tail
    ss << current->get_id() << ";" << current->get_salary() << ";" << current->get_department() <<endl;
  
}
Node* LinkedList::get_head(){
    return this->head;
}

string get_substring(string& line);


int main(int argc, char** argv){

    //clock_t start = clock(); // start to measure

    //opening the file
    fstream source_file;
    source_file.open(argv[1], ios::in);

    //Opening Error
    if (!source_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //Reading the data and storing it to the array
    int current_line = 1;
    string data_employee;

    //Linked list
    LinkedList* employees_list = new LinkedList;

    while(getline(source_file, data_employee)){
        //Skip first line
        if(current_line > 1){
            //split and read the data from file
            int id = stoi(get_substring(data_employee));
            int salary = stoi(get_substring(data_employee));
            int department = stoi(data_employee);

            //storing the data in the list by adding a node 
            employees_list->add_node(id, salary, department);

        }
        current_line++;
    }

    //Keeping the largest ID ( we have 2 additional lines)
    int largest_id = current_line - 2;

    //closing the file
    source_file.close();

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
            //Adding the node
            employees_list->add_node(largest_id, salary, department);
        }
        if(operation == "UPDATE"){
            //get new data from the file
            int id = stoi(get_substring(line));
            int salary = stoi(get_substring(line));
            int department = stoi(line);

            //Invalid ID
            if(!employees_list->contains(id)){
                cout << "ERROR: An invalid ID to update";
            }else{
                Node* prev = employees_list->search_prev(id);

                if(prev == NULL){//first node
                    employees_list->get_head()->set_salary(salary);
                    employees_list->get_head()->set_department(department);
                }else{
                    prev->get_next()->set_salary(salary);
                    prev->get_next()->set_department(department);
                }

            }
        }
        if(operation == "DELETE"){
            //get new data from the file
            int id = stoi(get_substring(line));

            //Empty List
            if(employees_list->is_empty()){
                cout << "ERROR: There is no Employee";
            }
            //Invalid ID
            if(!employees_list->contains(id)){
                cout << "ERROR: An invalid ID to delete";
            }else{
                employees_list->delete_node(id);
            }
        }
    }

    //closing the file
    operation_file.close();


    //creating the csv file
    fstream my_result_file;
    my_result_file.open("linked_list_solution.csv",ios::out);

    //Opening Error
    if (!my_result_file.is_open()) {
        cerr << "File could not be opened!" <<endl;
    }

    //string stream to write
    stringstream all_employees;

    all_employees <<"Employee_ID;Salary;Department" <<endl;

    employees_list->print_list(all_employees);

    my_result_file << all_employees.rdbuf();

    //closing the file
    my_result_file.close();

    //Free Memory
    delete employees_list;

     //clock_t end = clock();

    //measurement time in milliseconds
    //double duration_in_ms = (double)(end - start)* 1000 / CLOCKS_PER_SEC;

    //cout << "Duration of linked list solution in ms is: " << duration_in_ms << endl; 

    return 0;


    return 0;
}

string get_substring(string& line){
    int semicolon_index = line.find(';');
    string sub = line.substr(0, semicolon_index);
    line = line.erase(0, semicolon_index + 1);
    return sub;

}
