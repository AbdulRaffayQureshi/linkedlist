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
            head = newNode;
        }
    }

// ----------------Insert At End----------------

    void push_back(int val){
        Node* newNode = new Node(val);
        if(head == NULL){
            head = tail = newNode;
        }else {
            tail -> next = newNode;
            tail = newNode;
        }
    }

// ---------------Insert At Middle----------------

    void push_middle(int val, int pos){
        if(pos == 0){
            push_front(val);
            return;
        }
        if (pos < 0){
            cout << "Invalid position" << endl;
            return;
        }
        Node* newNode = new Node(val);
        Node* temp = head;
        for(int i = 0; i < pos-1; i++){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

// ----------------Delete From Beginning----------------

void pop_front(){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        } else {
            Node* temp = head;
            head = temp->next;
            temp->next = NULL;
            delete temp;
            if (head == NULL) tail = NULL; // updated: maintain tail
        }
    }
    
// ----------------Delete From Back----------------

    void pop_back(){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        } else {
            Node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            tail->next = NULL;
            delete tail;
            tail = temp;
        }
    }

// ----------------Delete Specific Value----------------
    void pop_value(int val){
        if(head == NULL){
            cout << "LL is empty" << endl;
            return;
        }
        if(head->data == val){
            Node* temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;
            if(head == NULL) tail = NULL;
            return;
        }
        Node* prev = head;
        Node* curr = head->next;
        while(curr != NULL && curr->data != val){
            prev = curr;
            curr = curr->next;
        }
        if(curr == NULL){
            cout << "Value not found" << endl;
            return;
        }
        prev->next = curr->next;
        if(curr == tail) tail = prev;
        curr->next = NULL;
        delete curr;
    }

// ----------------Print Linked List----------------

    void print(){
        Node* temp = head;
        while(temp != NULL){
            cout << temp->data << " "; // added space between values
            temp = temp->next;
        }
        cout << endl;
    }

// ----------------Reverse Linked List----------------
    void reverse(){
        Node* prev = NULL;
        Node* curr = head;
        Node* next = NULL;
        tail = head;               // new tail will be old head
        while(curr != NULL){
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;               // new head is previous tail
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