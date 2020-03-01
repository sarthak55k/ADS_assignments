//============================================================================
// Name        : Assignment_4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#define MAX 20
using namespace std;
class Gnode
{
	string name;
	int cost;
	Gnode *next;
public :
	Gnode()
{
		name="\0";
		cost=0;
		next=NULL;
}
	Gnode(string n, int c)
	{
		name=n;
		cost=c;
		next=NULL;
	}
	friend class Graph;
	friend class Queue;
	friend class Stack;
};

class Queue
{
	Gnode *data[MAX];
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
	void push(Gnode *x)
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
	Gnode *pop()
	{
		Gnode *x;
		if(empty())
		{
			cout<<"The Queue is Empty\n";
			x = new Gnode("null",-1);
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

class Stack
{
	Gnode *data[MAX];
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
	void push(Gnode *x)
	{
		if(full())
			cout<<"The Stack is Full\n";
		else
		{
			top++;
			data[top]=x;
		}
	}
	Gnode *pop()
	{
		Gnode *x;
		if(empty())
		{
			cout<<"The Stack is Empty\n";
			x = new Gnode("null",-1);
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

class Graph
{
	int vertices, edges;
	string cityname[20];
	Gnode *source[20];
public :
	Graph()
{
		vertices=edges=0;
		for(int i=0;i<19;i++)
			source[i]=NULL;
		for(int i=0;i<19;i++)
			cityname[i]="\0";
}
	int find(string);
	int search_path(string, string);
	void creategraph();
	void displaygraph();
	void add_edge(string, string, int);
	void delete_edge(string, string);
	void add_vertex(string);
	void delete_vertex(string);
	void indegree(string);
	void outdegree(string);
	void BFS();
	void DFS();
};

int Graph :: find(string p)
{
	int i,flag=0;
	for(i=0;i<vertices;i++)
	{
		if(cityname[i]==p)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
		return i;
	else
		return -1;
}

int Graph :: search_path(string s, string d)
{
	Gnode *p;
	int si,flag=0;
	si=find(s);
	p=source[si]->next;
	while(p!=NULL)
	{
		if(p->name==d)
		{
			flag=1;
			break;
		}
		else
			p=p->next;
	}
	if(flag==1)
		return 1;
	else
		return 0;
}

void Graph :: creategraph()
{
	int i,c,si,di;
	string s,d;
	cout<<"Enter the number of Cities\n";
	cin>>vertices;
	cout<<"\nEnter the City Names\n";
	for(i=0;i<vertices;i++)
	{
		cin>>cityname[i];
		source[i]= new Gnode();
		source[i]->name=cityname[i];
	}
	cout<<"\nEnter the number of Flight Paths\n";
	cin>>edges;
	for(i=0;i<edges;i++)
	{
		cout<<"\nEnter the source for path "<<i+1<<endl;
		cin>>s;
		cout<<"Enter the destination for path "<<i+1<<endl;
		cin>>d;
		cout<<"Enter the cost for path "<<i+1<<endl;
		cin>>c;
		si=find(s);
		di=find(d);
		if(si==-1)
		{
			cout<<"Source City not found\n";
			cout<<"Re-enter City Name\n";
			i--;
		}
		else if(di==-1)
		{
			cout<<"Destination City not found\n";
			cout<<"Re-enter City Name\n";
			i--;
		}
		else
		{
			Gnode *new1 = new Gnode(d,c);
			Gnode *p;
			p=source[si];
			while(p->next!=NULL)
				p=p->next;
			p->next=new1;
		}
	}
	displaygraph();
}

/*
 * else
 * {
 * 	    Gnode *new1 = new Gnode(d,c);
	    if(source[si]==NULL)
		{
			source[si]= new Gnode();
			source[si]->name=s;
			source[si]->next=new1;
		}
		else
		{
			Gnode *p;
			p=source[si];
			while(p->next!=NULL)
				p=p->next;
			p->next=new1;
		}
	}
 */
void Graph :: add_edge(string s, string d, int c)
{
	int si,di;
	si=find(s);
	di=find(d);
	if(si==-1)
		cout<<"Source City not found\n";
	else if(di==-1)
		cout<<"Destination City not found\n";
	else if(search_path(s,d)==1)
		cout<<"Path already present\n";
	else
	{
		Gnode *new1 = new Gnode(d,c);
		if(source[si]==NULL)
		{
			source[si]=new Gnode();
			source[si]->name=s;
			source[si]->next=new1;
		}
		else
		{
			Gnode *p;
			p=source[si];
			while(p->next!=NULL)
				p=p->next;
			p->next=new1;
		}
	}
	cout<<endl;
	displaygraph();
}

void Graph :: delete_edge(string s, string d)
{
	int si,di;
	si=find(s);
	di=find(d);
	if(si==-1)
		cout<<"Source City not found\n";
	else if(di==-1)
		cout<<"Destination City not found\n";
	//else if(search_path(s,d)==0)
		//cout<<"Path not present\n";
	else
	{
		Gnode *current,*previous;
		if(source[si]->next!=NULL)
		{
			current=source[si]->next;
			previous=NULL;
			if(current->name==d)
			{
				source[si]->next=current->next;
				current->next=NULL;
				delete current;
			}
			else
			{
				while(current!=NULL && current->name!=d)
				{
					previous=current;
					current=current->next;
				}
				if(previous->next!=NULL)
				{
					previous->next=current->next;
					current->next=NULL;
					delete current;
				}
			}
		}
	}
	cout<<endl;
}

void Graph :: add_vertex(string s)
{
	cityname[vertices]=s;
	source[vertices] = new Gnode();
	source[vertices]->name=s;
	vertices++;
	displaygraph();
}

void Graph :: delete_vertex(string s)
{
	int si;
	si=find(s);
	if(si==-1)
		cout<<"City not found\n";
	else
	{
		Gnode *p,*q;
		p=source[si];
		q=NULL;
		while(p!=NULL)
		{
			q=p;
			p=p->next;
			q->next=NULL;
			delete q;
		}
		source[si]=NULL;
		for(int i=0;i<vertices;i++)
		{
			if(source[i]!=NULL)
				delete_edge(cityname[i],s);
		}
		for(int i=si;i<vertices-1;i++)
		{
			cityname[i]=cityname[i+1];
			source[i]=source[i+1];
		}
		vertices--;
	}
}

void Graph :: indegree(string s)
{
	int si,c=0;
	si=find(s);
	if(si==-1)
		cout<<"City not found\n";
	else
	{
		Gnode *p;
		for(int i=0;i<vertices;i++)
		{
			p=source[i]->next;
			while(p!=NULL)
			{
				if(p->name==s)
					c++;
				p=p->next;
			}
		}
		cout<<"The In-Degree of "<<s<<" is "<<c<<endl;
	}
}

void Graph :: outdegree(string s)
{
	int si,c=0;
	si=find(s);
	if(si==-1)
		cout<<"City not found\n";
	else
	{
		Gnode *p;
		p=source[si]->next;
		while(p!=NULL)
		{
			c++;
			p=p->next;
		}
		cout<<"The Out-Degree of "<<s<<" is "<<c<<endl;
	}
}

void Graph :: BFS()
{
	Queue q;
	Gnode *temp;
	int visited[vertices];
	for(int i=0;i<vertices;i++)
		visited[i]=0;
	q.push(source[0]);
	visited[0]=1;
	while(!q.empty())
	{
		temp=q.pop();
		cout<<temp->name<<" ";
		temp=temp->next;
		while(temp!=NULL)
		{
			int si=find(temp->name);
			if(visited[si]==0)
			{
				q.push(source[si]);
				visited[si]=1;
			}
			temp=temp->next;
		}
	}
	cout<<endl;
}

void Graph :: DFS()
{
	Stack s;
	Gnode *temp;
	int visited[vertices];
	for(int i=0;i<vertices;i++)
		visited[i]=0;
	//cout<<source[0]->name<<" ";
	s.push(source[0]);
	visited[0]=1;
	while(!s.empty())
	{
		temp=s.pop();
		cout<<temp->name<<" ";
		temp=temp->next;
		while(temp!=NULL)
		{
			int si=find(temp->name);
			if(visited[si]==0)
			{
				//cout<<source[si]->name<<" ";
				s.push(source[si]);
				visited[si]=1;
			}
			temp=temp->next;
		}
	}
	cout<<endl;
}

void Graph :: displaygraph()
{
	int i;
	Gnode *p;
	for(i=0;i<vertices;i++)
	{
		if(source[i]!=NULL)
		{
			cout<<source[i]->name<<" -> ";
			p=source[i]->next;
			while(p!=NULL)
			{
				cout<<p->name<<"("<<p->cost<<")"<<" , ";
				p=p->next;
			}
			cout<<endl;
		}
	}
	cout<<endl;
}

int main()
{
	Graph g;
	string s,d;
	int c,ct;
	do
	{
		cout<<"Enter your choice\n1. Create a Graph\n2. Add a Path\n3. Delete a Path\n4. Add a City\n5. Delete a City\n6. Calculate In-Degree\n7. Calculate Out-Degree\n8. Display the Graph\n9. BFS Traversal\n10.DFS Traversal\n0. Exit\n";
		cin>>c;
		switch(c)
		{
		case 1 : g.creategraph();
			     break;
		case 2 : cout<<"Enter the source\n";
		         cin>>s;
		         cout<<"Enter the destination\n";
		         cin>>d;
		         cout<<"Enter the cost\n";
		         cin>>ct;
		         g.add_edge(s,d,ct);
		         break;
		case 3 : cout<<"Enter the source\n";
        	     cin>>s;
                 cout<<"Enter the destination\n";
                 cin>>d;
                 g.delete_edge(s,d);
                 g.displaygraph();
                 break;
		case 4 : cout<<"Enter the new City Name\n";
			     cin>>s;
			     g.add_vertex(s);
			     break;
		case 5 : cout<<"Enter the City Name\n";
	     	     cin>>s;
	     	     g.delete_vertex(s);
	     	     g.displaygraph();
	     	     break;
		case 6 : cout<<"Enter the City Name\n";
				 cin>>s;
				 g.indegree(s);
				 break;
		case 7 : cout<<"Enter the City Name\n";
				 cin>>s;
				 g.outdegree(s);
				 break;
		case 8 : g.displaygraph();
			     break;
		case 9 : cout<<"The Cities are\n";
				 g.BFS();
				 cout<<endl;
			     break;
		case 10: cout<<"The Cities are\n";
				 g.DFS();
				 cout<<endl;
				 break;
		case 0 : break;
		default : cout<<"Invalid Choice\n";
		}
	}while(c!=0);
	return 0;
}
