#include<iostream>

using namespace std;

template<typename T>
struct node {
    T val;
    node<T> *next;
};

template<typename T>
class stack {
    node<T> *top_ptr;
    int size;

    public:stack(): top_ptr(nullptr), size(0) {}

    public:bool empty() {
        return top_ptr == nullptr;
    }
    public:void push(T val) {
        ++size;
        if(empty()) {
            top_ptr = new node<T>();
            top_ptr->val = val;
            return;
        }
        node<T> *new_top = new node<T>();
        new_top->val = val;
        new_top->next = top_ptr;
        top_ptr = new_top;
    }

    public:void pop() {
        if(!empty()) {
            node<T> *temp = top_ptr;
            top_ptr = top_ptr->next;
            delete temp;
            --size;
        }
    }

    public:T top() {
        if(empty())
            return T();
        return top_ptr->val;
    }

    public:void print() {
        node<T> *temp = top_ptr;
        while(temp!=nullptr) {
            cout<<temp->val<<" ";
            temp = temp->next;
        }
        cout<<"\n";
    }
};