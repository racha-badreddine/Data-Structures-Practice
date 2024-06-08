/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 08/01/2024 > */
#pragma once
#include "employee.h"
#include <stdlib.h>

class QuadruplySkipList_Node{
    private:
        Employee* data;
        QuadruplySkipList_Node* next;
        QuadruplySkipList_Node* prev;
        QuadruplySkipList_Node* below;
        QuadruplySkipList_Node* above;
    public:
        QuadruplySkipList_Node(Employee *data);
        ~QuadruplySkipList_Node();

        void set_data(Employee*);
        void set_next(QuadruplySkipList_Node*);
        void set_prev(QuadruplySkipList_Node*);
        void set_below(QuadruplySkipList_Node*);
        void set_above(QuadruplySkipList_Node*);

        Employee* get_data();
        QuadruplySkipList_Node* get_next();
        QuadruplySkipList_Node* get_prev();
        QuadruplySkipList_Node* get_below();
        QuadruplySkipList_Node* get_above();
};

QuadruplySkipList_Node::QuadruplySkipList_Node(Employee* data){
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
    this->below = NULL;
    this->above = NULL;
}
QuadruplySkipList_Node::~QuadruplySkipList_Node(){

}

void QuadruplySkipList_Node::set_data(Employee* data){
    this->data = data;
}
void QuadruplySkipList_Node::set_next(QuadruplySkipList_Node* next){
    this->next = next;
}
void QuadruplySkipList_Node::set_prev(QuadruplySkipList_Node* prev){
    this->prev = prev;
}
void QuadruplySkipList_Node::set_below(QuadruplySkipList_Node* below){
    this->below = below;
}
void QuadruplySkipList_Node::set_above(QuadruplySkipList_Node* above){
    this->above = above;
}

Employee* QuadruplySkipList_Node::get_data(){
    return this->data;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_next(){
    return this->next;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_prev(){
    return this->prev;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_below(){
    return this->below;
}
QuadruplySkipList_Node* QuadruplySkipList_Node::get_above(){
    return this->above;
}