/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#pragma once
#include <stdlib.h> //for NULL
#include "employee.h"
class Node{
    private:
        Employee *employee;
        Node *left;
        Node *right;
    public:
        Node(Employee *employee);
        ~Node();
        void set_employee(Employee*);
        void set_left(Node*);
        void set_right(Node*);
        Employee* get_employee();
        Node* get_left();
        Node* get_right();
        Node** get_left_address();
        Node** get_right_address();
};
Node::Node(Employee *employee){
    this->employee = employee;
    this->left = NULL;
    this->right = NULL;
}
Node::~Node(){
    delete this->employee;
}
void Node::set_employee(Employee* employee){
    this->employee = employee;
    this->left = NULL;
    this->right = NULL;
}
void Node::set_left(Node* left){
    this->left = left;
}
void Node::set_right(Node* right){
    this->right = right;
}
Employee* Node::get_employee(){
        return this->employee;
}
Node* Node::get_left(){
    return this->left;
}
Node* Node::get_right(){
    return this->right;
}
Node** Node::get_left_address(){
    return &(this->left);
}
Node** Node::get_right_address(){
    return &(this->right);
}