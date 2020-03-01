//============================================================================
// Name        : Assignment_1.cpp
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
public :
	Node()
{
		data=0;
		left=right=NULL;
}
	Node(int d)
	{
		data=d;
		left=right=NULL;
	}
	friend class Queue;
	friend class Stack;
	friend class BinaryTree;
};
class Stack
{
	Node *data[MAX];
	int top;
public :
	Stack()
{
		top=-1;
}
	int empty()
	{
		if(top==-1)
			return 1;
		else
			return 0;
	}
	int full()
	{
		if(top==MAX-1)
			return 1;
		else
			return 0;
	}
	void push(Node *x)
	{
		if(full())
			cout<<"The Stack is Full\n";
		else
		{
			top++;
			data[top]=x;
		}
	}
	Node *pop()
	{
		Node *x;
		if(empty())
		{
			cout<<"The Stack is Empty\n";
			x = new Node(-1);
			return x;
		}
		else
		{
			x=data[top];
			top--;
			return x;
		}
	}
};
class Queue
{
	Node *data[MAX];
	int front,rear;
public :
	Queue()
{
		front=rear=-1;
}
	int empty()
	{
		if(front==-1||front==rear+1)
			return 1;
		else
			return 0;
	}
	int full()
	{
		if(rear==MAX-1)
			return 1;
		else
			return 0;
	}
	void push(Node *x)
	{
		if(full())
			cout<<"The Queue is Full\n";
		else
		{
			if(front==-1)
				front=0;
			rear=(rear+1)%MAX;
			data[rear]=x;
		}
	}
	Node *pop()
	{
		Node *x;
		if(empty())
		{
			cout<<"The Queue is Empty\n";
			x = new Node(-1);
			return x;
		}
		else
		{
			x=data[front];
			front=(front+1)%MAX;
			return x;
		}
	}
};
class BinaryTree
{
	Node *root;
public :
	BinaryTree()
{
		root=NULL;
}
	Node *get_root();
	void set_root(Node *);
	Node *create_rec();
	void create_nonrec();
	void display_rec(Node *);
	void inorder_rec(Node *);
	void preorder_rec(Node *);
	void postorder_rec(Node *);
	void display_nonrec();
	void inorder_nonrec();
	void preorder_nonrec();
	void postorder_nonrec();
	int Count(Node *);
	int Internal(Node *);
	int Leaf(Node *);
	void Deletenode(Node *);
	void operator = (BinaryTree &);
	Node *Copytree(Node *);
	Node *Mirror(Node *);
	int Equal(Node *, Node *);
};
Node *BinaryTree :: get_root()
{
	return root;
}
void BinaryTree :: set_root(Node *r)
{
	root=r;
}
Node *BinaryTree :: create_rec()
{
	Node *p;
	int x;
	cout<<"Enter the Data OR -1 to STOP\n";
	cin>>x;
	if(x==-1)
		return NULL;
	p=new Node(x);
	cout<<"Enter the Left Child of "<<x<<endl;
	p->left=create_rec();
	cout<<"Enter the Right Child of "<<x<<endl;
	p->right=create_rec();
	return p;
}
void BinaryTree :: create_nonrec()
{
	Queue q;
	Node *p1,*p2,*temp;
	int x;
	char ch;
	cout<<"Insert Data of Root\n";
	cin>>x;
	p1=new Node(x); 
	root=p1;
	q.push(p1);
	while(!q.empty())
	{
		temp=q.pop();
		cout<<"Do you want to insert to the left of "<<temp->data<<endl;
		cin>>ch;
		if(ch=='y'||ch=='Y')
		{
			cout<<"Enter Data\n";
			cin>>x;
			p1=new Node(x);
			temp->left=p1;
			q.push(p1);
		}
		cout<<"Do you want to insert to the right of "<<temp->data<<endl;
		cin>>ch;
		if(ch=='y'||ch=='Y')
		{
			cout<<"Enter Data\n";
			cin>>x;
			p2=new Node(x);
			temp->right=p2;
			q.push(p2);
		}
	}
}
void BinaryTree :: display_rec(Node *r)
{
    cout<<"Inorder Traversal\n";
    inorder_rec(r);
    cout<<endl;
    cout<<"Preorder Traversal\n";
    preorder_rec(r);
    cout<<endl;
    cout<<"Postorder Traversal\n";
    postorder_rec(r);
    cout<<endl;
    cout<<endl;
}
void BinaryTree :: inorder_rec(Node *p)
{
	if(p!=NULL)
	{
		inorder_rec(p->left);
		cout<<p->data<<" ";
		inorder_rec(p->right);
	}
}
void BinaryTree :: preorder_rec(Node *p)
{
	if(p!=NULL)
	{
		cout<<p->data<<" ";
		preorder_rec(p->left);
		preorder_rec(p->right);
	}
}
void BinaryTree :: postorder_rec(Node *p)
{
	if(p!=NULL)
	{
		postorder_rec(p->left);
		postorder_rec(p->right);
		cout<<p->data<<" ";
	}
}
void BinaryTree :: display_nonrec()
{
    cout<<"Inorder Traversal\n";
    inorder_nonrec();
    cout<<"Preorder Traversal\n";
    preorder_nonrec();
    cout<<"Postorder Traversal\n";
    postorder_nonrec();
}
void BinaryTree :: inorder_nonrec()
{
	Stack s;
	Node *t=root;
	while(1)
	{
		while(t!=NULL)
		{
			s.push(t);
	        t=t->left;
		}
		if(s.empty())
			break;
		t=s.pop();
		cout<<t->data<<" ";
		t=t->right;
	}
	cout<<endl;
}
void BinaryTree :: preorder_nonrec()
{
	Stack s;
	Node *t=root;
	s.push(t);
	while(!s.empty())
	{
		t=s.pop();
		cout<<t->data<<" ";
		if(t->right!=NULL)
			s.push(t->right);
		if(t->left!=NULL)
			s.push(t->left);
	}
	cout<<endl;
}
void BinaryTree :: postorder_nonrec()
{
	Stack s1,s2;
	Node *t=root;
	s1.push(t);
	while(!s1.empty())
	{
		t=s1.pop();
		s2.push(t);
		if(t->left!=NULL)
			s1.push(t->left);
		if(t->right!=NULL)
			s1.push(t->right);
	}
	while(!s2.empty())
	{
		t=s2.pop();
		cout<<t->data<<" ";
	}
	cout<<endl;
}
int BinaryTree :: Internal(Node *t)
{
	if(t==NULL)
		return 0;
	if(t->left==NULL && t->right==NULL)
		return 0;
	else
	{
		int l,r;
		cout<<t->data<<" ";
		l=Internal(t->left);
		r=Internal(t->right);
		return (l+r+1);
	}
}
int BinaryTree :: Leaf(Node *t)
{
	if(t==NULL)
		return 0;
	if(t->left==NULL && t->right==NULL)
	{
		cout<<t->data<<" ";
		return 1;
	}
	else
	{
		int l,r;
		l=Leaf(t->left);
		r=Leaf(t->right);
		return (l+r);
	}
}
void BinaryTree :: Deletenode(Node *t)
{
	if(t!=NULL)
	{
		Deletenode(t->left);
		Deletenode(t->right);
		cout<<t->data<<" ";
		delete(t);
	}
}
void BinaryTree :: operator = (BinaryTree &t)
{
	root=Copytree(t.root);
}
Node *BinaryTree :: Copytree(Node *q)
{
	if(q==NULL)
		return NULL;
	else
	{
		Node *p=new Node(q->data);
		p->left=Copytree(q->left);
		p->right=Copytree(q->right);
		return p;
	}
}
Node *BinaryTree :: Mirror(Node *q)
{
	if(q==NULL)
		return NULL;
	else
	{
		Node *p=new Node(q->data);
		p->left=Mirror(q->right);
		p->right=Mirror(q->left);
		return p;
	}
}
int BinaryTree :: Equal(Node *p, Node *q)
{
	if(p==NULL && q==NULL)
		return 1;
	else if(p==NULL)
		return 0;
	else if(q==NULL)
		return 0;
	else
	{
		if(p->data!=q->data)
			return 0;
		else
			return(Equal(p->left,q->left) && Equal(p->right,q->right));
	}
}
int main()
{
	BinaryTree b1,b2;
	Node *r,*r2;
	int c,cnt;
	do
	{
	cout<<"Enter your choice\n1. Recursive Creation and Display\n2. Non-recursive Creation and Display\n3. Delete all Nodes\n4. Assign one tree to another\n5. Display the Internal and Leaf Nodes\n6. Create a Mirror Image\n7. To check if two trees are equal or not\n0. Exit\n";
	cin>>c;
	switch(c)
	{
	case 1 : r=b1.create_rec();
	         b1.set_root(r);
	         r=b1.get_root();
             b1.display_rec(r);
	         //cout<<"The Number of Nodes are "<<b1.Count(r)<<endl;
	         break;
    case 2 : b1.create_nonrec();
             b1.display_nonrec();
             break;
	case 3 : cout<<"The nodes are deleted in the order\n";
		     r=b1.get_root();
	         b1.Deletenode(r);
	         r=NULL;
	         b1.set_root(r);
	         cout<<endl;
	         //cout<<"All nodes have been deleted\n";
	         break;
	case 4 : cout<<"After assigning one tree to another\n";
	         b2=b1;
	         r=b2.get_root();
	         b2.display_rec(r);
		     break;
	case 5 : r=b1.get_root();
		     cout<<"The Internal Nodes are\n";
             cnt=b1.Internal(r);
             cout<<"\nThe number of Internal Nodes is "<<cnt<<endl;
             cout<<endl;
             cnt=0;
             cout<<"The Leaf Nodes are\n";
             cnt=b1.Leaf(r);
             cout<<"\nThe number of Leaf Nodes is "<<cnt<<endl;
             cout<<endl;
             break;
	case 6 : cout<<"The Mirror Image is\n";
		     r=b1.get_root();
	         r2=b2.Mirror(r);
	         b2.set_root(r2);
	         b2.display_rec(r2);
	         break;
	case 7 : cout<<"Create second tree\n";
	         r2=b2.create_rec();
		     b2.set_root(r2);
		     r2=b2.get_root();
	         b2.display_rec(r2);
	         r=b1.get_root();
	         cnt=b1.Equal(r,r2);
	         if(cnt==0)
	        	 cout<<"\nThe two trees are not equal\n\n";
	         else
	        	 cout<<"\nThe two trees are equal\n\n";
	         break;
	case 0 : break;
	default : cout<<"Invalid Choice\n";
	}
	}while(c!=0);
	return 0;
}
