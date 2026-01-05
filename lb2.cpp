#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* prev;            // added for doubly linked list
   
    Node(int val) {
        data = val;
        next = NULL;
        prev = NULL;       // initialize prev
    }
};

class DLinkedList {
    Node* head;
    Node* tail;
    
public:
    DLinkedList() {
        head = tail = NULL;
    }

// ----------------Insert At Beginning----------------

    void push_front(int val){
        Node* newNode = new Node(val);
        if (head == NULL){
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

// ----------------Insert At End----------------

    void push_back(int val){
        Node* newNode = new Node(val);
        if(head == NULL){
            head = tail = newNode;
        }else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

// ---------------Insert At Middle----------------

    void push_middle(int val, int pos){
        if(pos <= 0 || head == NULL){
            push_front(val);
            return;
        }
        Node* temp = head;
        for(int i = 0; i < pos-1 && temp->next != NULL; i++){
            temp = temp->next;
        }
        // insert after temp
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        newNode->prev = temp;
        if(temp->next) temp->next->prev = newNode;
        temp->next = newNode;
        if(newNode->next == NULL) tail = newNode;
    }

// ----------------Delete From Beginning----------------

    void pop_front(){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        } else {
            Node* temp = head;
            head = head->next;
            if(head) head->prev = NULL;
            else tail = NULL;
            delete temp;
        }
    }
    
// ----------------Delete From Back----------------

    void pop_back(){
        if(tail == NULL){
            cout << "LL is empty" << endl;
            return;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            if(tail) tail->next = NULL;
            else head = NULL;
            delete temp;
        }
    }

// ----------------Delete Specific Value----------------
    void pop_value(int val){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        }
        Node* curr = head;
        while(curr != NULL && curr->data != val){
            curr = curr->next;
        }
        if(curr == NULL){
            cout << "Value not found" << endl;
            return;
        }
        if(curr == head){
            pop_front();
            return;
        }
        if(curr == tail){
            pop_back();
            return;
        }
        // middle node
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
    }

// ----------------Print Linked List----------------

    void print(){
        Node* temp = head;
        while(temp != NULL){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

// ----------------Reverse Linked List----------------
    void reverse(){
        Node* curr = head;
        Node* temp = NULL;
        while(curr != NULL){
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev; // moved to original next
        }
        // swap head and tail
        if(temp != NULL){
            Node* newHead = temp->prev;
            head = newHead;
        }
        // ensure tail is old head
        // recompute tail for safety
        tail = head;
        if(tail){
            while(tail->next != NULL) tail = tail->next;
        }
    }

// ----------------Search In Linked List----------------
    int search(int val){
        Node* temp = head;
        int idx = 0;
        while(temp != NULL){
            if(temp->data == val) return idx;
            temp = temp->next;
            idx++;
        }
        return -1; // not found
    }

// ----------------Length of Linked List----------------
    int length(){
        Node* temp = head;
        int count = 0;
        while(temp != NULL){
            count++;
            temp = temp->next;
        }
        return count;
    }

// ----------------Print Only Even-Valued Nodes----------------
    void print_even_values(){
        Node* temp = head;
        while(temp != NULL){
            if(temp->data % 2 == 0) cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
    DLinkedList dll;
    dll.push_back(10);
    dll.push_back(20);
    dll.push_front(5);
    dll.push_front(0);
    dll.push_middle(15, 3);
    dll.print();         // before removal
    dll.pop_value(15);   // remove specific number 15
    dll.print();         // after removal
    dll.reverse();
    dll.print();         // after reverse

    // demo: search for a value
    int pos = dll.search(20);
    if(pos != -1) cout << "Found 20 at index " << pos << endl;
    else cout << "20 not found" << endl;

    // demo: print length
    cout << "Length: " << dll.length() << endl;

    // demo: print even values
    cout << "Even values: ";
    dll.print_even_values();

    return 0;
}
