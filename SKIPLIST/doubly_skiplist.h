/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 08/01/2024 > */
#pragma once
#include "doubly_skiplist_node.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <stack>

using namespace std;

class DoublySkipList{
    private:
        DoublySkipList_Node* head;
        int height;
    public:
        DoublySkipList(int height_in);
        ~DoublySkipList();
        void insert(Employee* data);
        void remove(int remove_id);
        Employee* search(int search_id);
        void dumpToFile(ofstream& out_file);
        bool isempty();
};

DoublySkipList::DoublySkipList(int height_in){
    //constructing two sentinels with the given height
    Employee* minus_inf = new Employee(-10000000,-10000000,-10000000);
    Employee* plus_inf = new Employee(100000000,100000000,100000000);

    this->head = new DoublySkipList_Node(minus_inf);
    this->head->set_next(new DoublySkipList_Node(plus_inf));
    
    DoublySkipList_Node* second_sent = this->head->get_next();
    //sentinel
    for(int i = 1; i < height_in; i++){
        DoublySkipList_Node* sent1 = new DoublySkipList_Node(minus_inf);
        DoublySkipList_Node* sent2 = new DoublySkipList_Node(plus_inf);

        //head will always point to the top left
        sent1->set_below(this->head);
        this->head = sent1;

        sent2->set_below(second_sent);
        second_sent = sent2;  


        this->head->set_next(second_sent);
    }
    this->height = height_in;

}
DoublySkipList::~DoublySkipList(){
    //starting from top left
    DoublySkipList_Node* temp = this->head;

    //deleting level by level from top to bottom
    while(temp->get_below()){
        DoublySkipList_Node* Level_below = temp->get_below();
        while(temp){
            DoublySkipList_Node* next_node = temp->get_next();

            delete temp;
            temp = next_node;
        }

        temp = Level_below;
    }

    //last level delete both data and node
    while(temp){
        DoublySkipList_Node* next_node = temp->get_next();

        delete temp->get_data();
        delete temp;
        temp = next_node;
    }

}
void DoublySkipList::insert(Employee* data){
    //start from top left
    DoublySkipList_Node* temp = this->head;
    //stack to keep node to be updated
    stack <DoublySkipList_Node*> nodes_to_update;


    // Traverse the skip list from the top to the bottom
    while (temp != NULL) {
        // Move to the right
        while (temp->get_next() != NULL && temp->get_next()->get_data()->get_id() < data->get_id()) {
            temp = temp->get_next();
        }

        // If bottom level->place found insert the new node
        if (temp->get_below() == NULL) {
            DoublySkipList_Node* new_node = new DoublySkipList_Node(data);

            //update pointers
            new_node->set_next(temp->get_next());
            temp->set_next(new_node);

          int level = 1;

        // Seed the random number generator with the current time
        static default_random_engine generator(random_device{}());
        uniform_real_distribution<double> distribution(0.0, 1.0);

        //flipping coin method
        while (distribution(generator) < 0.5 && level < this->height) {
            //updating level
            level ++;

            DoublySkipList_Node* added_level_node = new DoublySkipList_Node(data);

            //updating the pointers
            added_level_node->set_below(new_node);

            //getting node from stack
            temp = nodes_to_update.top();
            nodes_to_update.pop();

            //updating pointers
            added_level_node->set_next(temp->get_next());
            temp->set_next(added_level_node);

            new_node = added_level_node;
        }

            return;
        }

        //pushing node to stack befor going below
        nodes_to_update.push(temp);
        // Move down to the next level
        temp = temp->get_below();

    }
    
}
void DoublySkipList::remove(int remove_id){
    //starting from top left
    DoublySkipList_Node* temp = this->head;

    //while temp not NULL search for the prev node
    while(temp){
        if(temp->get_next()->get_data()->get_id() == remove_id){
            //prev found
           break;
        }else if(remove_id > temp->get_data()->get_id() && remove_id > temp->get_next()->get_data()->get_id()){
            temp = temp->get_next();
        }else if(remove_id > temp->get_data()->get_id() && remove_id < temp->get_next()->get_data()->get_id()){
            temp = temp->get_below();
        }
    }
    if(temp != NULL && temp->get_next()->get_data()->get_id() == remove_id){

        while(temp != NULL){
            DoublySkipList_Node* bottom = temp->get_below();
            DoublySkipList_Node* next = temp->get_next();
            DoublySkipList_Node* nextnext = temp->get_next()->get_next();

            temp->set_next(nextnext);

            //if last level delete data
            if(bottom == NULL){
                delete next->get_data();
            }
            delete next;
            temp = bottom;

            //at lower level we go next till next is the id to remove
            if(temp!= NULL && temp->get_next() != NULL){
                while (temp->get_next()->get_data()->get_id() != remove_id){
                    temp = temp->get_next();
                }
            }

        }

           return;
    }
           
    //not found
    cout << "ERROR: An invalid ID to delete\n";
    return ;
}
Employee* DoublySkipList::search(int search_id){
    //start from the top left
    DoublySkipList_Node* temp = this->head;

    while(temp){
        if(temp->get_data()->get_id() == search_id){
            //found
            return temp->get_data();
        }else if(search_id > temp->get_data()->get_id() && search_id >= temp->get_next()->get_data()->get_id()){
            temp = temp->get_next();
        }else if(search_id > temp->get_data()->get_id() && search_id < temp->get_next()->get_data()->get_id()){
            temp = temp->get_below();
        }
    }
    return NULL;
}

void DoublySkipList::dumpToFile(ofstream& out_file){
    DoublySkipList_Node* temp = this->head;

    //go to bottom
    while(temp->get_below() != NULL){
        temp = temp->get_below();
    }

    stringstream data;

    while (temp->get_next() != NULL){
        temp = temp->get_next();

        if(temp->get_data()->get_id() != 100000000){
            data << temp->get_data()->get_id() << ";" 
            << temp->get_data()->get_salary() << ";" 
            << temp->get_data()->get_department()<< '\n';
        }
            
    }


    out_file << data.rdbuf();
    
}

bool DoublySkipList::isempty(){
    DoublySkipList_Node* temp = this->head;

    while(temp->get_below() != NULL){
        temp = temp->get_below();
    }
    //only two sentinels
    if(temp->get_next()->get_next() == NULL){
        return true;
    }
    return false;
}
