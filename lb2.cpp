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

class LinkedList {
    Node* head;
    Node* tail;
    
public:
    LinkedList() {
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
        Node* tmp = NULL;
        while(curr != NULL){
            tmp = curr->prev;
            curr->prev = curr->next;
            curr->next = tmp;
            curr = curr->prev; // moved to original next
        }
        // swap head and tail
        if(tmp != NULL){
            Node* newHead = tmp->prev;
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
    LinkedList ll;
    ll.push_back(10);
    ll.push_back(20);
    ll.push_front(5);
    ll.push_front(0);
    ll.push_middle(15, 3);
    ll.print();         // before removal
    ll.pop_value(15);   // remove specific number 15
    ll.print();         // after removal
    ll.reverse();
    ll.print();         // after reverse

    // demo: search for a value
    int pos = ll.search(20);
    if(pos != -1) cout << "Found 20 at index " << pos << endl;
    else cout << "20 not found" << endl;

    // demo: print length
    cout << "Length: " << ll.length() << endl;

    // demo: print even values
    cout << "Even values: ";
    ll.print_even_values();


    return 0;
}
