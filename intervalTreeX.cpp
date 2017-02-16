/*
Name : Utkarsh Maheshwari
Enrollment Number : 13115130
Class : B.Tech, 4th Year, Electrical Engineering
*/

#include<iostream>
using namespace std;

struct range{//structure to store time
	int x,y;//x->low endpoint and y->high endpoint of the time range
};

struct node{//structure for each node of the interval tree
	range r;// time range of the node
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

void insert(node **rootptr, range r){//insert time t into the interval tree
	if((*rootptr)==NULL){//base case
		(*rootptr)=new node();
		(*rootptr)->r=r;
		(*rootptr)->high=r.y;
		(*rootptr)->left=NULL;
		(*rootptr)->right=NULL;
	}
	else if(r.x<(*rootptr)->r.x){//node to be inserted in left subtree
		insert(&((*rootptr)->left),r);	
	} 
	else if(r.x>(*rootptr)->r.x){//node to be inserted in right subtree
		insert(&((*rootptr)->right),r);	
	} 
	//maintain the augumented data oh "high" after insertion
	(*rootptr)->high=max((*rootptr)->r.y,max(getLeftMaxi(*rootptr),getRightMaxi(*rootptr)));
}

void inorder(node *root){//prints the inorder traversal of the interval tree
	if(root==NULL){
		return;	
	} 
	inorder(root->left);
	cout<<root->r.x<<":"<<root->r.y<<":"<<root->high<<" ";
	inorder(root->right);
}

void search(node *root, range r){//finds an overlapping time range from the tree
	if(root==NULL){//No overlapping range case
		cout<<"No Overlap"<<endl;	
	}
	else if((root->r.x<=r.y)&&(r.x<=root->r.y)){//overlapping range found case
		cout<<root->r.x<<":"<<root->r.y<<endl;	
	}
	else if((root->left!=NULL)&&(root->left->high>=r.x)){//overlapping range in left subtree
		search(root->left,r);
	}
	else{//overlapping range in right subtree
		search(root->right,r);
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

void del(node **rootptr,range r){//delete a time range from the tree
	if((*rootptr)==NULL){
		cout<<"Not in the tree"<<endl;
	} 
	else if(((*rootptr)->r.x==r.x)&&((*rootptr)->r.y==r.y)){
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
			(*rootptr)->r.x=temp->r.x;
			(*rootptr)->r.y=temp->r.y;
			(*rootptr)->high=temp->high;
			del(&((*rootptr)->right),temp->r);	
		}
	}
	else if(r.x<(*rootptr)->r.x){//node to be deleted in left subtree
		del(&((*rootptr)->left),r);
	}
	else if(r.x>(*rootptr)->r.x){//node to be deleted in right subtree
		del(&((*rootptr)->right),r);	
	}
	//maintain the augumented data oh "high" after deletion 
	(*rootptr)->high=max((*rootptr)->r.y,max(getLeftMaxi(*rootptr),getRightMaxi(*rootptr)));
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
			range r;
			cin>>r.x>>r.y;
			insert(&root,r);//insertion
		}
		else if(n==2){
			range r;
			cin>>r.x>>r.y;
			del(&root,r);//deletion
		}
		else if(n==3){
			range r;
			cin>>r.x>>r.y;
			search(root,r);//searching overlapping time range
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
