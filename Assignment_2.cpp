//============================================================================
// Name        : Assignment_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
using namespace std;
class Node
{
	char *word;
	char *meaning;
	Node *left, *right;
public :
	Node()
{
		word=NULL;
		meaning=NULL;
		left=right=NULL;
}
	Node(char *w,char *m)
	{
		word=new char[strlen(w)+1];
		meaning=new char[strlen(m)+1];
		strcpy(word,w);
		strcpy(meaning,m);
		left=right=NULL;
	}
	friend class Dictionary;
};
class Dictionary
{
	Node *root;
public :
	Dictionary()
{
		root=NULL;
}
	Node *get_root();
	void set_root(Node *);
	void create();
	void ascending(Node *);
	void descending(Node *);
	int comparison(char *w);
	Node *search(char *w);
	void modify(char *w);
	void operator = (Dictionary &);
	Node *Copy(Node *);
	void Delete(char *);
};
Node *Dictionary :: get_root()
{
	return root;
}
void Dictionary :: set_root(Node *r)
{
	root=r;
}
void Dictionary :: create()
{
	char w[20],m[20];
	cout<<"Enter the word\n";
	cin>>w;
	cout<<"Enter the meaning\n";
	cin>>m;
	Node *new1=new Node(w,m);
	if(root==NULL)
		root=new1;
	else
	{
		Node *p,*q;
		p=root;
		q=NULL;
		while(p!=NULL)
		{
			q=p;
			if(strcmp(w,p->word)<0)
				p=p->left;
			else
				p=p->right;
		}
		if(strcmp(w,q->word)<0)
			q->left=new1;
		else if(strcmp(w,q->word)>0)
			q->right=new1;
		else
		{
			cout<<"Duplicate Data\n\n";
			delete new1;
		}
	}
}
void Dictionary :: ascending(Node *p)
{
	if(p!=NULL)
	{
		ascending(p->left);
		cout<<p->word<<" : "<<p->meaning<<endl;
		ascending(p->right);
	}
}
void Dictionary :: descending(Node *p)
{
	if(p!=NULL)
	{
		descending(p->right);
		cout<<p->word<<" : "<<p->meaning<<endl;
		descending(p->left);
	}
}
int Dictionary :: comparison(char *w)
{
	Node *p;
	int found=0,c=0;
	p=root;
	while(p!=NULL && found==0)
	{
		if(strcmp(w,p->word)==0)
		{
			c++;
			found=1;
		}
		else
		{
			if(strcmp(w,p->word)<0)
			{
				c++;
				p=p->left;
			}
			else
			{
			    c++;
				p=p->right;
			}
		}
	}
	if(found==1)
	{
		return c;
	}
	else
		return found;
}
Node *Dictionary :: search(char *w)
{
	Node *p,*q;
	p=q=root;
	int found=0;
	while(p!=NULL && found==0)
	{
		if(strcmp(w,p->word)==0)
		{
			found=1;
		}
		else
		{
			q=p;
			if(strcmp(w,p->word)<0)
				p=p->left;
			else
				p=p->right;
		}
	}
	if(found==0)
		return NULL;
	else
		return q;
}
void Dictionary :: modify(char *w)
{
	Node *p,*q;
	char m[20];
	q=search(w);
	if(q==NULL)
		cout<<"The Word is not found\n";
	else
	{
		if(q->left!=NULL)
		{
			if(strcmp(q->left->word,w)==0)
				p=q->left;
		}
		if(q->right!=NULL)
		{
			if(strcmp(q->right->word,w)==0)
				p=q->right;
		}
		cout<<"Enter the meaning of the word to modify\n";
		cin>>m;
		strcpy(p->meaning,m);
		cout<<"The meaning has been modified\n";
	}
	ascending(root);
}
void Dictionary :: operator = (Dictionary &t)
{
	root=Copy(t.root);
}
Node *Dictionary :: Copy(Node *q)
{
	if(q==NULL)
		return NULL;
	else
	{
		Node *p = new Node(q->word,q->meaning);
		p->left=Copy(q->left);
		p->right=Copy(q->right);
		return p;
	}
}
void Dictionary :: Delete(char *w)
{
	Node *p,*q;
	q=search(w);
	if(q==NULL)
		cout<<"The Word is not found\n";
	else
	{
		if(q->left!=NULL)
		{
			if(strcmp(q->left->word,w)==0)
				p=q->left;
		}
		if(q->right!=NULL)
		{
			if(strcmp(q->right->word,w)==0)
				p=q->right;
		}
		if(p->left!=NULL && p->right!=NULL)
		{
			q=p;
			Node *ps=p->right;
			while(ps->left!=NULL)
			{
				q=ps;
				ps=ps->left;
			}
			p->word=ps->word;
			p->meaning=ps->meaning;
			p=ps;
		}
		if(p->left==NULL && p->right!=NULL)
		{
			if(q->right==p)
				q->right=p->right;
			else
				q->left=p->right;
			delete p;
		}
		if(p->left!=NULL && p->right==NULL)
		{
			if(q->right==p)
				q->right=p->left;
			else
				q->left=p->left;
			delete p;
		}
		if(p->left==NULL && p->right==NULL)
		{
			if(q->right==p)
				q->right=NULL;
			else
				q->left=NULL;
			delete p;
		}
		cout<<"The word has been deleted\n";
	}
	ascending(root);
}
int main()
{
	Dictionary d,d2;
	Node *r,*r2;
	int c,cnt;
	char w[20];
	do
	{
		cout<<"Enter your choice\n1. Add a Keyword\n2. Display in Descending order\n3. Search a Word\n4. Modify a Word\n5. Assign one tree to another\n6. Delete a Word\n0. Exit\n";
        cin>>c;
		switch(c)
		{
		case 1 : d.create();
		         r=d.get_root();
			     d.ascending(r);
			     cout<<endl;
			     break;
		case 2 : cout<<"The Descending order is\n";
			     d.descending(d.get_root());
	             cout<<endl;
	             break;
		case 3 : cout<<"Enter the word to search\n";
				 cin>>w;
		         cnt=d.comparison(w);
		         if(cnt==0)
		        	 cout<<"The Word is not found\n";
		         else
		         {
		        	 cout<<"The Word is found\n";
		        	 cout<<"The number of comparisons are "<<cnt<<endl;
		         }
		         break;
		case 4 : cout<<"Enter the word to be modified\n";
			     cin>>w;
			     d.modify(w);
			     cout<<endl;
			     break;
		case 5 : cout<<"After assigning one tree to another\n";
				 d2=d;
				 d2.ascending(d2.get_root());
				 cout<<endl;
				 break;
		case 6 : cout<<"Enter the word to delete\n";
				 cin>>w;
				 d.Delete(w);
				 cout<<endl;
				 break;
		case 0 : break;
		default : cout<<"Invalid Input\n";
		}
	}while(c!=0);
	return 0;
}
