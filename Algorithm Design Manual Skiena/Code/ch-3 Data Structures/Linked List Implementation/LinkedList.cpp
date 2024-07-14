#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* element_at(Node* head, int pos) {
    Node* temp = new Node();
    temp->next = head;
    
    for (int index = 0; index < pos ;index++) {
        temp = temp->next;
    }

    return temp;
}

void insert(Node* &head, int new_data,int pos=0) {
    Node* temp = new Node();
    temp->data = new_data;

    if (pos == 0) {
        temp->next = head;
        head = temp;
    }
    else {
        temp->next = element_at(head, pos);
        element_at(head, pos - 1)->next = temp;
    }
}

Node* search_r_node(Node* head, int data) {
    Node* temp = new Node();
    temp->next = head;
    int index = 0;
    while(temp && temp->data != data ) {
        temp = temp->next;
    } 
    return temp;
}

int search_r_index(Node* head, int data) {
    Node* temp = new Node();
    temp->next = head;
    int index = 0;
    while (temp && temp->data != data ) {
        temp = temp->next;
        index++;
    }
    if (temp != NULL)
        return index;
    else return -1;
}

void print_list(Node* head) {
    Node* temp = new Node();
    temp->next = head;
    temp = temp -> next;
    while (temp) {                                      // checks for temp = NULL
        cout << temp->data << '\t';
        temp = temp->next;
    }
    cout << endl;
}

void insert_at_end(Node* head, int data) {
    Node* temp = new Node();
    temp->data = data;
    temp->next = NULL;
    if (head == NULL) {
        head = temp;
    }
    else {
        Node* temp1 = new Node();
        temp1->next = head;
        while (temp1->next) temp1 = temp1->next;
        temp1->next = temp;
    }
}

int length_of_list(Node* head) {
    Node* temp = new Node();
    temp = head;
    int len;

    for  (len = 0; temp; len++) temp = temp->next;

    return len;
}

void pop(Node* head, int pos = -1) {
    if (pos == -1) {
        pop(head, length_of_list(head));
    }

    else {
        Node* pop = element_at(head, pos);
        Node* popb = element_at(head, pos - 1);
        popb->next = pop->next;
        free(pop);

    }
    
}

void merge(Node* head1, Node* head2) {
    Node* linker = element_at(head1, length_of_list(head1));
    linker->next = head2;
}


int main()
{
    Node* head = new Node();
    head->data = 6;
    head->next = NULL;

    cout << "OG LINKED LIST" << endl;
    insert(head, 5);
    insert(head, 4);
    insert(head, 3);
    print_list(head);
    cout << endl;

    insert(head, 7, 3);
    cout << "Adding 7 at pos 3" << endl;
    print_list(head);
    cout << endl;

    insert(head, 7, 3); 
    insert(head, 7, 3); 
    insert(head, 7, 3);
    cout << "Adding 7 at pos 3 , 3 more times" << endl;
    print_list(head);
    cout << endl;

    insert_at_end(head, 10);
    insert_at_end(head, 11);
    insert_at_end(head, 12);
    cout << "Adding 10,11,12 at the end of linst" << endl;
    print_list(head);
    cout << endl;

    int array[] = { 1,2,3,4,5,6,7,8,9,11,12,13 };
    for (int i : array)
        cout << "First apperance of " << i << " is at index " << search_r_index(head, i) << endl;
    cout << endl;

    //print full
    for (int i = 1; i <= length_of_list(head); i++) 
        cout << "Element at pos " << i << " is " << element_at(head, i)->data << endl;
    cout << endl;

    cout << "Now popping element at pos 7" << endl;
    pop(head, 7);
    for (int i = 1; i <= length_of_list(head); i++) 
        cout << "Element at pos " << i << " is " << element_at(head, i)->data << endl;
    cout << endl;

    cout << "Now popping last element " << endl;
    pop(head);
    for (int i = 1; i <= length_of_list(head); i++) 
        cout << "Element at pos " << i << " is " << element_at(head, i)->data << endl;
    cout << endl;

    Node* head2 = new Node();
    head2->data = 100;
    head2->next = NULL;

    cout << "OG LINKED LIST -- 2" << endl;
    insert(head2, 70);
    insert(head2, 20);
    insert(head2, 40);
    print_list(head2);
    cout << endl;

    cout << "now merging them :)" << endl;
    merge(head, head2);
    for (int i = 1; i <= length_of_list(head); i++)
        cout << "Element at pos " << i << " is " << element_at(head, i)->data << endl;
    cout << endl;




}

