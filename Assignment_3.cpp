//============================================================================
// Name        : Assignment_3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define MAX 20
using namespace std;
class Node
{
	int data;
	Node *left, *right;
	int lbit, rbit;
public :
	Node()
{
		data=0;
		left=right=NULL;
		lbit=0;
		rbit=0;
}
	Node(int d)
	{
		data=d;
		left=right=NULL;
		lbit=0;
		rbit=0;
	}
	friend class Queue;
	friend class TBT;
};

class TBT
{
	Node *root, *head;
public :
	TBT()
{
		root=NULL;
		head=NULL;
}

	void create();
	void create_normal();
	Node *create_rec(Node *, int);
	void insert();
	void l_insert(Node *, Node *);
	void r_insert(Node *, Node *);
	void inorder();
	Node *insuccessor(Node *);
	void preorder();
};
/*void TBT :: create()
{
	Queue q;
	Node *p1,*p2;
	int x;
	if(head==NULL)
	{
		p1=new Node(-1);
		head=p1;
		p1->left=p1->right=p1;
		p1->lbit=0;
		p1->rbit=1;
	}
	cout<<"Enter the data of root\n";
    cin>>x;
	p1=new Node(x);
	root=p1;
	l_insert(head,p1);
	q.push(p1);

}*/

/*void TBT :: create_normal()
{
	root=create_rec(root,0);
}

Node *TBT :: create_rec(Node *p, int c)
{
	int x;
	cout<<"Enter Data\n";
	cin>>x;
	if(x==-1)
		return NULL;
	Node *new1 = new Node(x);
	if(c==0)
		l_insert(p,new1);
	else if(c==1)
		r_insert(p,new1);
	cout<<"Enter left child of "<<new1->data<<endl;
	new1=create_rec(new1,0);
	cout<<"Enter right child of "<<new1->data<<endl;
	new1=create_rec(new1,1);
	return new1;
}*/

void TBT :: create()
{
	Node *ptr;
	int x;
	if(root!=NULL)
		cout<<"The Threaded Binary Tree is already created\n";
	else
	{
		head=new Node(-99);
		head->left=head->right=head;
		head->lbit=0;
		head->rbit=1;
		cout<<"Enter Data of root\n";
		cin>>x;
		root=new Node(x);
		root->left=root->right=head;
		root->lbit=root->rbit=0;
		head->left=root;
		head->lbit=1;
		do
		{
			ptr=root;
			cout<<"Enter the data or -1 to stop\n";
			cin>>x;
			while(x!=-1)
			{
				if(x<ptr->data)
				{
					if(ptr->lbit!=0)
						ptr=ptr->left;
					else
					{
						Node *temp = new Node(x);
						l_insert(ptr,temp);
						break;
					}
				}
				if(x>ptr->data)
				{
					if(ptr->rbit!=0)
						ptr=ptr->right;
					else
					{
						Node *temp = new Node(x);
						r_insert(ptr,temp);
						break;
					}
				}
			}
		}while(x!=-1);
	}
}

void TBT :: insert()
{
	Node *ptr;
	int x;
	if(root==NULL)
	{
		head=new Node(-99);
		head->left=head->right=head;
		head->lbit=0;
		head->rbit=1;
		cout<<"Enter Data of root\n";
		cin>>x;
		root=new Node(x);
		root->left=root->right=head;
		root->lbit=root->rbit=0;
		head->left=root;
		head->lbit=1;
	}
	else
	{
		ptr=root;
		cout<<"Enter the data\n";
		cin>>x;
		while(1)
		{
			if(x<ptr->data)
			{
				if(ptr->lbit!=0)
					ptr=ptr->left;
				else
				{
					Node *temp = new Node(x);
					l_insert(ptr,temp);
					break;
				}
			}
			if(x>ptr->data)
			{
				if(ptr->rbit!=0)
					ptr=ptr->right;
				else
				{
					Node *temp = new Node(x);
					r_insert(ptr,temp);
					break;
				}
			}
		}
	}
}

void TBT :: l_insert(Node *q, Node *p)
{
	p->left=q->left;
	p->right=q;
	p->lbit=q->lbit;
	p->rbit=0;
	q->left=p;
	q->lbit=1;
}

void TBT :: r_insert(Node *q, Node*p)
{
	p->left=q;
	p->right=q->right;
	p->lbit=0;
	p->rbit=q->rbit;
	q->right=p;
	q->rbit=1;
}

void TBT :: inorder()
{
	Node *p;
	p=head;
	cout<<"Inorder Traversal\n";
	while(1)
	{
		p=insuccessor(p);
		if(p==head)
			break;
		cout<<p->data<<" ";
	}
	cout<<endl;
}

Node *TBT :: insuccessor(Node *p)
{
	Node *ps;
	ps=p->right;
	if(p->rbit==1)
	{
		while(ps->lbit!=0)
			ps=ps->left;
	}
	return ps;
}

void TBT :: preorder()
{
	Node *p;
	p=head->left;
	cout<<"Preorder Traversal\n";
	while(p!=head)
	{
		//if(p==head)
			//break;
		cout<<p->data<<" ";
		if(p->lbit==1)
			p=p->left;
		else
		{
			if(p->rbit==1)
				p=p->right;
			else
			{
				while(p->rbit!=1)
					p=p->right;
				p=p->right;
			}
		}
	}
	cout<<endl;
}
int main()
{
	TBT t;
	int c;
	do
	{
		cout<<"Enter your choice\n1. Create a Threaded Binary Tree\n2. Insert a Node\n3. Preorder Traversal\n0. Exit\n";
		cin>>c;
		switch(c)
		{
		case 1 : t.create();
			     t.inorder();
			     cout<<endl;
			     break;
		case 2 : t.insert();
			     t.inorder();
			     cout<<endl;
			     break;
		case 3 : t.preorder();
			     cout<<endl;
			     break;
		case 0 : break;
		default : cout<<"Invalid Choice\n\n";
		}
	}while(c!=0);
}
