/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 08/01/2024 > */
#pragma once
#include "quadruply_skiplist_node.h"
#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
#include <stack>

using namespace std;

class QuadruplySkipList{
    private:
        QuadruplySkipList_Node* head;
        int height;
        
    public:
        QuadruplySkipList(int height_in);
        ~QuadruplySkipList();
        void insert(Employee* data);
        void remove(int remove_id);
        Employee* search(int search_id);
        void dumpToFile(ofstream& out_file);
        bool isempty();
};
QuadruplySkipList::QuadruplySkipList(int height_in){
    //constructing two sentinels with the given height
    Employee* minus_inf = new Employee(-10000000,-10000000,-10000000);
    Employee* plus_inf = new Employee(100000000,100000000,100000000);

    this->head = new QuadruplySkipList_Node(minus_inf);
    this->head->set_next(new QuadruplySkipList_Node(plus_inf));
    
    QuadruplySkipList_Node* second_sent = this->head->get_next();
    second_sent->set_prev(this->head);
    //sentinel
    for(int i = 1; i < height_in; i++){
        QuadruplySkipList_Node* sent1 = new QuadruplySkipList_Node(minus_inf);
        QuadruplySkipList_Node* sent2 = new QuadruplySkipList_Node(plus_inf);

        //head will always point to the top left
        this->head->set_above(sent1);
        sent1->set_below(this->head);
        this->head = sent1;

        second_sent->set_above(sent2);
        sent2->set_below(second_sent);
        second_sent = sent2;  


        this->head->set_next(second_sent);
        second_sent->set_prev(this->head);
    }
    this->height = height_in;
}
QuadruplySkipList::~QuadruplySkipList(){
    //start deleting from top left
    QuadruplySkipList_Node* temp = this->head;

    //deleting nodes of level from top to bottom
    while(temp->get_below()){
        QuadruplySkipList_Node* Level_below = temp->get_below();
        while(temp){
            QuadruplySkipList_Node* next_node = temp->get_next();

            delete temp;
            temp = next_node;
        }

        temp = Level_below;
    }

    //last level delete both data and node
    while(temp){
        QuadruplySkipList_Node* next_node = temp->get_next();

        delete temp->get_data();
        delete temp;
        temp = next_node;
    }
}

void QuadruplySkipList::insert(Employee* data){
    //start searching from top left
    QuadruplySkipList_Node* temp = this->head;
    //stack to keep the nodes with pointers to be updated
    stack <QuadruplySkipList_Node*> nodes_to_update;


    while (temp != NULL) {
        // Move to the right
        while (temp->get_next() != NULL && temp->get_next()->get_data()->get_id() < data->get_id()) {
            temp = temp->get_next();
        }

        // If we arrived to bottom->right place to insert the new node
        if (temp->get_below() == NULL) {
            QuadruplySkipList_Node* new_node = new QuadruplySkipList_Node(data);

            //update pointers
            new_node->set_next(temp->get_next());
            new_node->set_prev(temp);

            if (temp->get_next() != NULL) {
                temp->get_next()->set_prev(new_node);
            }
            temp->set_next(new_node);

          int level = 1;

        // Seed the random number generator with the current time
        static default_random_engine generator(random_device{}());
        uniform_real_distribution<double> distribution(0.0, 1.0);

        //flipping coin method
        while (distribution(generator) < 0.5 && level < this->height) {
            //update level
            level ++;

            QuadruplySkipList_Node* added_level_node = new QuadruplySkipList_Node(data);

            //updating the pointers
            new_node->set_above(added_level_node);
            added_level_node->set_below(new_node);

            //node to be updated from the stack
            temp = nodes_to_update.top();
            nodes_to_update.pop();


            added_level_node->set_next(temp->get_next());
            added_level_node->set_prev(temp);

            if (temp->get_next() != NULL) {
                temp->get_next()->set_prev(added_level_node);
            }
            
            temp->set_next(added_level_node);

            new_node = added_level_node;
        }
            return;
        }

        //pushing node to stack before going below
        nodes_to_update.push(temp);
        // Go below
        temp = temp->get_below();

    }
}
void QuadruplySkipList::remove(int remove_id){

    //starting from Top Left
    QuadruplySkipList_Node* temp = this->head;

    //while temp is not NULL we keep searching for the node
    while(temp){
        if(temp->get_data()->get_id() == remove_id){
            //found
           break;
        }else if(remove_id > temp->get_data()->get_id() && remove_id >= temp->get_next()->get_data()->get_id()){
            temp = temp->get_next();
        }else if(remove_id > temp->get_data()->get_id() && remove_id < temp->get_next()->get_data()->get_id()){
            temp = temp->get_below();
        }
    }
    //if temp is not null which means the null is found
    if(temp != NULL && temp->get_data()->get_id() == remove_id){
        //delete data first
        delete temp->get_data();
        temp->set_data(NULL);
        //deleting all levels of the node
        while(temp != NULL){
            QuadruplySkipList_Node* bottom = temp->get_below();
            QuadruplySkipList_Node* next = temp->get_next();
            QuadruplySkipList_Node* prev = temp->get_prev();

            //updating pointers
            prev->set_next(next);
            next->set_prev(prev);
            delete temp;
            temp = bottom;

        }

           return;
    }
           
    //not found
    cout << "ERROR: An invalid ID to delete\n";
    return ;

}
Employee* QuadruplySkipList::search(int search_id){
    //start from the top left
    QuadruplySkipList_Node* temp = this->head;

    //whhile temp is not NULL, continue searching
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
    //Not found
    return NULL;

}

void QuadruplySkipList::dumpToFile(ofstream& out_file){

    //start from Top Left
    QuadruplySkipList_Node* temp = this->head;

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

    //pring stringstream to the file
    out_file << data.rdbuf();
    
}
bool QuadruplySkipList::isempty(){
    QuadruplySkipList_Node* temp = this->head;

    while(temp->get_below() != NULL){
        temp = temp->get_below();
    }
    //only two sentinels in skiplist
    if(temp->get_next()->get_next() == NULL){
        return true;
    }
    return false;
}
