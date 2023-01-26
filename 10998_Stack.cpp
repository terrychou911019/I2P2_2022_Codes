#include<iostream>
#include<string.h>
//no need to submit
using namespace std;
class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor

    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

//
//#include "function.h"
//using namespace std;
List_stack::List_stack() :head(NULL), tail(NULL) {}
List_stack::~List_stack() {}
void List_stack::push(const int &n) {
    ListNode *node = new ListNode(n);
    if (tail == NULL) {
        head = tail = node;
    }
    else {
        tail->nextPtr = node;
        node->prevPtr = tail;
        tail = tail->nextPtr;
    }   
}
void List_stack::pop() {
    if (tail == NULL) return;
    ListNode *tmp = tail;
    tail = tail->prevPtr;
    delete tmp;
}
void List_stack::print() {
    ListNode *cur = tail;
    while (cur != NULL) {
        if (cur == head) {
            cout << cur->data;
        }
        else {
            cout << cur->data << " ";
        }
        cur = cur->prevPtr;
    }
}
//


int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}
