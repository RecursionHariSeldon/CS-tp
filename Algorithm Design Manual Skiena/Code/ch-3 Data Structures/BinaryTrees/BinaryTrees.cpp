#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* parent;
    Node* left = NULL;
    Node* right = NULL;

    Node(int d, Node* a, bool right){
        data = d;
        parent = a;
        if(a!= NULL){
            if(!right) a->left = this;
            else a->right = this;
        }
    }
    Node(){}
};

Node* searchTree(Node* root,int data){

    Node* temp = new Node();
    temp->right = root;
    if (root == NULL) return NULL;

    while(temp->data != data ){
        if (temp->data > data) temp = temp->left;
        if (temp->data < data) temp = temp->right;
    }
    return temp;
}

Node* searchTreeRecursion(Node* root,int data){
    if(root==NULL) return NULL;

    if(root->data == data) return root;

    if (data < root->data) return searchTreeRecursion(root->left,data);
    else return searchTreeRecursion(root->right,data);
}

Node* min(Node* root){
    if (root == NULL)return NULL;

    Node* min = root;

    while (min->left !=NULL) min = min->left;

    return min;
}

void traverse_tree(Node* root){
    if(root != NULL){
        traverse_tree(root->left);
        cout<< root->data << " , ";
        traverse_tree(root->right);

    }

}


int main(){
    Node n1 = Node(7,NULL,0);
    Node n2 = Node(5,&n1,0);
    Node n3 = Node(3,&n2,0);
    Node n4 = Node(2,&n3,0);
    Node n5 = Node(6,&n2,1);
    Node n6 = Node(9,&n1,1);
    Node n7 = Node(8,&n6,0);
    Node n8 = Node(11,&n6,1);
    Node n9 = Node(10,&n8,0);
    Node n10 = Node(12,&n8,1);

    cout << "Minimum of the tree is " <<min(&n1)->data<<endl;
    cout<< "Parent of n8 is : "<< n8.parent->data<<endl;  
    cout<< "Left child of n6 is : "<< n6.left->data<<endl;    
    cout<< "The entire tree is : " ; traverse_tree(&n1);cout<<endl;
    

    
    
}