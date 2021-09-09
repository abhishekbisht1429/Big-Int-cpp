#include<iostream>
#include<string> 

using namespace std;

struct node {
    string val;
    node *next;
};
class stack {
    node *top_ptr;
    int size;

    public:stack(): top_ptr(nullptr), size(0) {}

    public:bool empty() {
        return top_ptr == nullptr;
    }
    public:void push(string val) {
        ++size;
        if(empty()) {
            top_ptr = new node();
            top_ptr->val = val;
            return;
        }
        node *new_top = new node();
        new_top->val = val;
        new_top->next = top_ptr;
        top_ptr = new_top;
    }

    public:void pop() {
        if(!empty()) {
            node *temp = top_ptr;
            top_ptr = top_ptr->next;
            delete temp;
            --size;
        }
    }

    public:string top() {
        if(empty())
            return "";
        return top_ptr->val;
    }

    public:void print() {
        node *temp = top_ptr;
        while(temp!=nullptr) {
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<"\n";
    }
};