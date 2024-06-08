/* @Author
Student Name :< Racha Badreddine >
StudentID :< 150210928 >
Date :< 18/12/2023 > */
#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include "employee.h"
#include "node.h"

using namespace std;
class BinaryTree{
    private:
        Node *root;
        Node* search_parent(int id,Node*** child);
    public:
        BinaryTree();
        ~BinaryTree();
        void insert(Employee* employee);
        void update(int,int,int);
        void remove(int id);
        Employee *search(int id);
        int getHeight();
        void printToFile(ofstream &output_file);
        void printToConsole();
        Node* get_root();
};
BinaryTree::BinaryTree(){
    this->root = NULL;
}
BinaryTree::~BinaryTree(){
    Node* ptr = this->root;

    //checking if the tree is empty
    if(ptr != NULL){
        queue<Node*> q;
        q.push(ptr);

        while(!q.empty()){
            ptr = q.front();
            q.pop();

            //to not get a segmentation fault we check if it is NULL
            if(ptr != NULL){
                if(ptr->get_left() != NULL){
                q.push(ptr->get_left());
                }
                if(ptr->get_right() != NULL){
                    q.push(ptr->get_right());
                }

                delete ptr;

            }
        }
    }else{
        delete ptr;
    }

}
   

Node* BinaryTree::search_parent(int id,Node*** child){
    //if tree is empty
    if(this->root == NULL ){
        return NULL;
    }else if (this->root->get_employee()->get_id() == id){       
        //when the root is the child
        (*child) = &(this->root);
        return NULL;  
    }
    Node* temp = this->root;

    while(temp != NULL){
        if(temp->get_left() == NULL && temp->get_right() == NULL){
            //when we arrive to a leaf we return the parent and child stays NULL
            return temp;
        }else{
            if(temp->get_left() != NULL){
                if(temp->get_left()->get_employee()->get_id() == id){
                    (*child)= temp->get_left_address();
                    return temp;
                }
            }else if(id < temp->get_employee()->get_id()){
                return temp;
            }
            if(temp->get_right() != NULL){
                if(temp->get_right()->get_employee()->get_id() == id){
                (*child)= temp->get_right_address();
                return temp;
                }
            }else if (id > temp->get_employee()->get_id()){
                return temp;
            }
        }
        //traversing the binary search tree according ti id
        if(id > temp->get_employee()->get_id()){
            temp = temp->get_right();
        }else if(id < temp->get_employee()->get_id()){
            temp = temp->get_left();
        }else{
            return NULL;
        }
    }
    return NULL;

}
void BinaryTree::insert(Employee* employee){
    //empty tree
    if(this->root == NULL){
       this->root = new Node(employee);
       return;
    }
    int id = employee->get_id();
    //searching for the parent to where we insert
    Node** child = NULL;
    Node* parent = this->search_parent(id, &child);

    if(parent != NULL){
        //NOT A ROOT
        if(id > parent->get_employee()->get_id()){
            parent->set_right(new Node(employee));
            return;
        }else if(id < parent->get_employee()->get_id()){
            parent->set_left(new Node(employee));
            return;
        }else{
            return;
        }
    }else if(parent == NULL){
        //ROOT
        if(id > this->root->get_employee()->get_id()){
            this->root->set_right(new Node(employee));
            return;
        }else if(id < this->root->get_employee()->get_id()){
            this->root->set_left(new Node(employee));
            return;
        }else{
            return;
        }
    }
}
void BinaryTree::update(int id, int salary, int department){
    Employee* employee = this->search(id);
    if(employee == NULL){
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
    employee->set_salary(salary);
    employee->set_department(department);

}
void BinaryTree::remove(int id){
    Node** node_to_delete = NULL;
   
    Node* parent = this->search_parent(id,&node_to_delete);

    //ID NOT FOUND
    if(node_to_delete == NULL){
        cout << "ERROR: An invalid ID to delete\n";
        delete node_to_delete;
        return;
    }
    Node* leftchild = (*node_to_delete)->get_left();
    Node* rightchild = (*node_to_delete)->get_right();

    //root
    if(parent == NULL){
        if(leftchild == NULL && rightchild == NULL){
            //only root in the tree
            delete this->root;
            this->root = NULL;
            return;
        }else if(rightchild != NULL){
            //looking for the new root to replace the deleted one
            Node* new_parent = this->root;
            Node* new_root = rightchild;

            while(new_root->get_left() != NULL){
                new_parent = new_root;
                new_root = new_root->get_left();
            }

            //root to be deleted
            Node* temp = this->root;
            temp->set_left(NULL);
            temp->set_right(NULL);

            this->root = new_root;
            
            this->root->set_left(leftchild);
            
            //keepin the new root's children if any
            Node* temp2 = this->root;
            while(temp2->get_right() != NULL){
                temp2 = temp2->get_right();   
            }

           if(rightchild != this->root){
               temp2->set_right(rightchild);
            }
            new_parent->set_left(NULL);

            //deleting
            delete temp;
            return;
            
        }else{
            //only left child
            Node* t = this->root;
            this->root = leftchild;
            delete t;
            return;
        }
    }else{
        //not the root
        if(leftchild == NULL && rightchild == NULL){
            //leaf
            delete (*node_to_delete);
            (*node_to_delete)= NULL;

            return;
        }else if(rightchild != NULL){
            //looking for the new node to replace
            Node* new_parent = (*node_to_delete);
            Node* new_node = rightchild;

            while(new_node->get_left() != NULL){
                new_parent = new_node;
                new_node = new_node->get_left();
            }

            Node* temp = (*node_to_delete);
            temp->set_left(NULL);
            temp->set_right(NULL);

            (*node_to_delete) = new_node;
            (*node_to_delete)->set_left(leftchild);

            //keeping the new node's children if any
            Node* temp2 = new_node;
            while(temp2->get_right() != NULL){
                temp2 = temp2->get_right();   
            }
            
            if(rightchild != (*node_to_delete)){
               temp2->set_right(rightchild);
            }
            new_parent->set_left(NULL);

            delete temp;
            return;
            
        }else{
            //only left child
            Node* t = (*node_to_delete);
            (*node_to_delete) = leftchild;
            t->set_left(NULL); 
            delete t;
            return;
        }
    }
}
Employee* BinaryTree::search(int id){
    Node* temp = this->root;

    //Binary Search
    while(temp != NULL){
         if(id > temp->get_employee()->get_id()){
            temp = temp->get_right();
        }else if (id < temp->get_employee()->get_id()){
            temp = temp->get_left();
        }else{
            return temp->get_employee();
        }
    }    
    return NULL;
}
int BinaryTree::getHeight(){
    if(this->root == NULL){
        return 0;
    }
    int height = 0;

    //Applying breadth first traversal with keeping levels to find height
    queue<Node*> q; 
    q.push(this->root);

    while (!q.empty()) {
        int level_size = q.size();

        while (level_size > 0) {
            Node* current = q.front();
            q.pop();
            level_size--;

            if(current != NULL){             
                if (current->get_left() != NULL) {
                    q.push(current->get_left());
                }
                if (current->get_right() != NULL) {
                    q.push(current->get_right());
                }
            }

        }
        //incrementing the height after traversing all nodes of same level
        height++;
    }

    return height;
}
void BinaryTree::printToFile(ofstream &output_file){
    //printing to the file inorder(l-R-r)
    if(this->root == NULL){
        return;
    }
    stringstream data;

    stack<Node*> traverse;
  
    Node* current = this->root;

    while(current != NULL || !traverse.empty()){
        //we traverse thruogh the left and we push
        while(current!= NULL){
            traverse.push(current);
            current = current->get_left();
        }
        current = traverse.top();
        traverse.pop();
        //print
        if(current->get_employee() != NULL){
            data << current->get_employee()->get_id() << ";" 
            << current->get_employee()->get_salary() << ";" 
            << current->get_employee()->get_department()<< '\n' ;
        }
        
        current = current->get_right();
        
    }
    output_file << data.rdbuf();
    
}
void BinaryTree::printToConsole(){
    //printing to the console pre-order(R-l-r)
    if(this->root == NULL){
        return;
    }

    stringstream data;

    stack<Node*> s; 
    s.push(this->root);
    while(!s.empty()){
        Node* current = s.top();
        s.pop();
        if(current->get_employee() != NULL){
            data << current->get_employee()->get_id() << ";" 
            << current->get_employee()->get_salary() << ";" 
            << current->get_employee()->get_department()<< '\n' ;
        }
        if(current->get_right() != NULL ){
            s.push(current->get_right());
        }
        if(current->get_left() != NULL ){
            s.push(current->get_left());
        }
    }
    cout << data.rdbuf();

}
Node* BinaryTree::get_root(){
    return this->root;
}