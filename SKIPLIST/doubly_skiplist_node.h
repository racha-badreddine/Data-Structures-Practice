/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 08/01/2024 > */
#pragma once
#include "employee.h"
#include <stdlib.h>
class DoublySkipList_Node{
    private:
        Employee* data;
        DoublySkipList_Node* next;
        DoublySkipList_Node* below;
    public:
        DoublySkipList_Node(Employee *data);
        ~DoublySkipList_Node();
        
        void set_data(Employee*);
        void set_next(DoublySkipList_Node*);
        void set_below(DoublySkipList_Node*);

        Employee* get_data();
        DoublySkipList_Node* get_next();
        DoublySkipList_Node* get_below();
    };

DoublySkipList_Node::DoublySkipList_Node(Employee* data){
    this->data = data;
    this->next = NULL;
    this->below = NULL;
}
DoublySkipList_Node::~DoublySkipList_Node(){

}

void DoublySkipList_Node::set_data(Employee* data){
    this->data = data;
}
void DoublySkipList_Node::set_next(DoublySkipList_Node* next){
    this->next = next;
}

void DoublySkipList_Node::set_below(DoublySkipList_Node* below){
    this->below = below;
}

Employee* DoublySkipList_Node::get_data(){
    return this->data;
}
DoublySkipList_Node* DoublySkipList_Node::get_next(){
    return this->next;
}

DoublySkipList_Node* DoublySkipList_Node::get_below(){
    return this->below;
}

