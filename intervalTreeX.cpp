/*
Name : 				Utkarsh Maheshwari
Enrollment Number : 13115130
Class : 		    B.Tech, 4th Year, Electrical Engineering
*/

#include<iostream>
using namespace std;

struct time{//structure to store time
	int x,y;//x->low endpoint and y->high endpoint of the time range
};

struct node{//structure for each node of the interval tree
	time t;// time range of the node
	int high;//stores the maximum endpoint value of the subtree
	node *left;//pointer to left subtree
	node *right;//pointer to right subtree
};

int getLeftMaxi(node *root){//returns the maximum endpoint of the left subtree
	return (root->left==NULL)?0:root->left->high;
}

int getRightMaxi(node *root){//returns the maximum endpoint of the right subtree
	return (root->right==NULL)?0:root->right->high;
}

void insert(node **rootptr, time t){//insert time t into the interval tree
	if((*rootptr)==NULL){//base case
		(*rootptr)=new node();
		(*rootptr)->t=t;
		(*rootptr)->high=t.y;
		(*rootptr)->left=NULL;
		(*rootptr)->right=NULL;
	}
	else if(t.x<(*rootptr)->t.x){//node to be inserted in left subtree
		insert(&((*rootptr)->left),t);	
	} 
	else if(t.x>(*rootptr)->t.x){//node to be inserted in right subtree
		insert(&((*rootptr)->right),t);	
	} 
	//maintain the augumented data oh "high" after insertion
	(*rootptr)->high=max((*rootptr)->t.y,max(getLeftMaxi(*rootptr),getRightMaxi(*rootptr)));
}

void inorder(node *root){//prints the inorder traversal of the interval tree
	if(root==NULL){
		return;	
	} 
	inorder(root->left);
	cout<<root->t.x<<":"<<root->t.y<<":"<<root->high<<" ";
	inorder(root->right);
}

void search(node *root, time t){//finds an overlapping time range from the tree
	if(root==NULL){//No overlapping range case
		cout<<"No Overlap"<<endl;	
	}
	else if((root->t.x<=t.y)&&(t.x<=root->t.y)){//overlapping range found case
		cout<<root->t.x<<":"<<root->t.y<<endl;	
	}
	else if((root->left!=NULL)&&(root->left->high>=t.x)){//overlapping range in left subtree
		search(root->left,t);
	}
	else{//overlapping range in right subtree
		search(root->right,t);
	}
}

node* leftmost(node *temp){//returns the leftmost node in a subtree
	if(temp->left==NULL) return temp;
	return leftmost(temp->left);
}

node* successor(node *temp){//returns the successor of a node from the tree
	if(temp->right==NULL) return NULL;
	return leftmost(temp->right);
}

void del(node **rootptr,time t){//delete a time range from the tree
	if((*rootptr)==NULL){
		cout<<"Not in the tree"<<endl;
	} 
	else if(((*rootptr)->t.x==t.x)&&((*rootptr)->t.y==t.y)){
		if(((*rootptr)->left==NULL)&&((*rootptr)->right==NULL)){//leaf node case
			(*rootptr)=NULL;
			return;	
		}
		else if((*rootptr)->left==NULL){//only right substree case
			(*rootptr)=(*rootptr)->right;	
		}
		else if((*rootptr)->right==NULL){//only left subtree case
			(*rootptr)=(*rootptr)->left;		
		} 
		else{//both left and right subtree case
			node *temp=successor((*rootptr));
			(*rootptr)->t.x=temp->t.x;
			(*rootptr)->t.y=temp->t.y;
			(*rootptr)->high=temp->high;
			del(&((*rootptr)->right),temp->t);	
		}
	}
	else if(t.x<(*rootptr)->t.x){//node to be deleted in left subtree
		del(&((*rootptr)->left),t);
	}
	else if(t.x>(*rootptr)->t.x){//node to be deleted in right subtree
		del(&((*rootptr)->right),t);	
	}
	//maintain the augumented data oh "high" after deletion 
	(*rootptr)->high=max((*rootptr)->t.y,max(getLeftMaxi(*rootptr),getRightMaxi(*rootptr)));
}

int main(){
	int n,x,y;
	node *root=NULL;
	cout<<"1) Insert"<<endl//MENU
		<<"2) Delete"<<endl
		<<"3) Search"<<endl
		<<"4) Inorder"<<endl
		<<"5) Exit"<<endl;
	while(true){
		cin>>n;
		if(n==1){
			time t;
			cin>>t.x>>t.y;
			insert(&root,t);//insertion
		}
		else if(n==2){
			time t;
			cin>>t.x>>t.y;
			del(&root,t);//deletion
		}
		else if(n==3){
			time t;
			cin>>t.x>>t.y;
			search(root,t);//searching overlapping time range
		}	
		else if(n==4){
			inorder(root);//inorder traversal
			cout<<endl;
		}	
		else{
			break;
		}
	}
	return 0;	
}
