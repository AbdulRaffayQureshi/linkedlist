#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
   
    Node(int val) {
        data = val;
        next = NULL;
    }
};

class CLinkedList {
    Node* head;
    Node* tail;
    
public:
    CLinkedList() {
        head = tail = NULL;
    }

// ----------------Insert At Beginning----------------

    void push_front(int val){
        Node* newNode = new Node(val);
        if (head == NULL){
            head = tail = newNode;
            newNode->next = newNode; // circular
        } else {
            newNode->next = head;
            tail->next = newNode;
            head = newNode;
        }
    }

// ----------------Insert At End----------------

    void push_back(int val){
        if(head == NULL){
            push_front(val);
            return;
        }
        Node* newNode = new Node(val);
        tail->next = newNode;
        newNode->next = head;
        tail = newNode;
    }

// ---------------Insert At Middle----------------

    void push_middle(int val, int pos){
        if(pos <= 0 || head == NULL){
            push_front(val);
            return;
        }
        int len = length();
        if(pos >= len){
            push_back(val);
            return;
        }
        Node* temp = head;
        for(int i = 0; i < pos-1; i++){
            temp = temp->next;
        }
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
    }

// ----------------Delete From Beginning----------------

    void pop_front(){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        }
        if(head == tail){ // single node
            delete head;
            head = tail = NULL;
            return;
        }
        Node* temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
    }
    
// ----------------Delete From Back----------------

    void pop_back(){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        }
        if(head == tail){
            delete head;
            head = tail = NULL;
            return;
        }
        Node* prev = head;
        while(prev->next != tail) prev = prev->next;
        prev->next = head;
        delete tail;
        tail = prev;
    }

// ----------------Delete Specific Value----------------
    void pop_value(int val) {
        if (head == NULL) {
            cout << "LL is empty" << endl;
            return;
        }

        Node* curr = head;
        Node* prev = tail;
        bool found = false;

        // iterate using a while loop for readability
        while (true) {
            if (curr->data == val) {
                found = true;
                break;
            }

            // if we've reached tail and it's not a match, stop searching
            if (curr == tail) {
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        if (!found) {
            cout << "Value not found" << endl;
            return;
        }

        if (curr == head) {
            pop_front();
            return;
        }

        if (curr == tail) {
            pop_back();
            return;
        }

        prev->next = curr->next;
        delete curr;
    }

// ----------------Print Linked List----------------

    void print(){
        if(head == NULL){
             cout << endl;
             return;
        }
        Node* temp = head;
        cout << temp->data << " ";
        temp = temp->next;
        while(temp != head){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

// ----------------Reverse Linked List----------------
    void reverse(){
        if(head == NULL || head == tail) return;
        // break circularity
        tail->next = NULL;
        Node* prev = NULL;
        Node* curr = head;
        Node* next = NULL;
        Node* oldHead = head;
        while(curr != NULL){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
        tail = oldHead;
        tail->next = head; // restore circularity
    }

// ----------------Search In Linked List----------------
    int search(int val){
        if(head == NULL){
            return -1;
        }
        Node* temp = head;
        int idx = 0;
        if(temp->data == val){
            return idx;
        }
        temp = temp->next;
        idx++;
        while(temp != head){
            if(temp->data == val){
                return idx;
            }
            temp = temp->next;
            idx++;
        }
        return -1; // not found
    }

// ----------------Length of Linked List----------------
    int length(){
        if(head == NULL){
            return 0;
        }
        Node* temp = head;
        int count = 1;
        temp = temp->next;
        while(temp != head){
            count++;
            temp = temp->next;
        }
        return count;
    }

// ----------------Print Only Even-Valued Nodes----------------
    void print_even_values(){
        if(head == NULL){
             cout << endl;
             return;
        }
        Node* temp = head;
        bool any = false;
        if(temp->data % 2 == 0){
            cout << temp->data << " ";
            any = true;
        }
        temp = temp->next;
        while(temp != head){
            if(temp->data % 2 == 0){
                cout << temp->data << " ";
                any = true;
            }
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
    CLinkedList cll;
    cll.push_back(10);
    cll.push_back(20);
    cll.push_front(5);
    cll.push_front(0);
    cll.push_middle(15, 3);
    cll.print();         // before removal
    cll.pop_value(15);   // remove specific number 15
    cll.print();         // after removal
    cll.reverse();
    cll.print();         // after reverse

    // demo: search for a value
    int pos = cll.search(20);
    if(pos != -1) cout << "Found 20 at index " << pos << endl;
    else cout << "20 not found" << endl;

    // demo: print length
    cout << "Length: " << cll.length() << endl;

    // demo: print even values
    cout << "Even values: ";
    cll.print_even_values();

    return 0;
}
