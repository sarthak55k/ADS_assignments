//============================================================================
// Name        : Assignment_5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
using namespace std;
class Graph
{
	int G[20][20];
	int vertices,edges;
public :
	Graph()
{
		vertices=edges=0;
		for(int i=0;i<20;i++)
			for(int j=0;j<20;j++)
				G[i][j]=0;
}
	void creategraph();
	void displaygraph();
	//void displayMST(int ***);
	void Prims();
	void Krushkal();
};

void Graph :: creategraph()
{
	int s,d,c;
	cout<<"Enter the number of vertices\n";
	cin>>vertices;
	cout<<"The vertices are\n";
	for(int i=0;i<vertices;i++)
		cout<<i<<" ";
	cout<<"\n";
	cout<<"Enter the number of edges\n";
	cin>>edges;
	for(int i=0;i<edges;i++)
	{
		cout<<"Enter the Source\n";
		cin>>s;
		cout<<"Enter the Destination\n";
		cin>>d;
		cout<<"Enter the Cost\n";
		cin>>c;
		if(G[s][d]==0)
			G[s][d]=G[d][s]=c;
		else
			cout<<"Edge already present\n";
	}
	displaygraph();
}

void Graph :: Prims()
{
	int g[vertices][vertices], ST[vertices][vertices], father[vertices], visited[vertices];
	int count=0,cnt=1,wt=0,min=9999,v;
	int t1,t2,temp1,temp2,root1,root2;
	for(int i=0;i<vertices;i++)
	{
		for(int j=0;j<vertices;j++)
			g[i][j]=G[i][j];
	}
	for(int i=0;i<vertices;i++)
	{
			for(int j=0;j<vertices;j++)
				ST[i][j]=0;
	}
	for(int i=0;i<vertices;i++)
		father[i]=-1;
	cout<<"Enter the starting vertex\n";
	cin>>v;
	visited[cnt]=v;
	cnt++;
	while(count<vertices-1)
	{
		min=999;
		for(int v1=1;v1<cnt;v1++)
		{
			for(int v2=0;v2<vertices;v2++)
			{
				if(g[visited[v1]][v2]!=0 && g[visited[v1]][v2]<min)
				{
					min=g[visited[v1]][v2];
					t1=visited[v1];
					t2=v2;
				}
			}
		}
		temp1=t1;
		temp2=t2;
		g[t1][t2]=g[t2][t1]=0;
		while(t1>=0)
		{
			root1=t1;
			t1=father[t1];
		}
		while(t2>=0)
		{
			root2=t2;
			t2=father[t2];
		}
		if(root1!=root2)
		{
			ST[temp1][temp2]=ST[temp2][temp1]=min;
			wt=wt+ST[temp1][temp2];
			father[root2]=root1;
			count++;
			visited[cnt]=temp2;
			cnt++;
		}
	}
	cout<<"The MST is\n";
	cout<<"      ";
	for(int i=0;i<vertices;i++)
		cout<<i<<setw(5);
	cout<<"\n--";
	for(int k=0;k<=vertices*5;k++)
		cout<<"-";
	cout<<"\n";
	for(int i=0;i<vertices;i++)
	{
		cout<<i<<"  |  ";
		for(int j=0;j<vertices;j++)
			cout<<ST[i][j]<<setw(5);
		cout<<"\n";
	}
	cout<<"\nThe weight is "<<wt<<endl<<endl;
}

void Graph :: Krushkal()
{
	int g[vertices][vertices],ST[vertices][vertices],father[vertices];
	int count=0,wt=0,min=999;
	int t1,t2,temp1,temp2,root1,root2;
	for(int i=0;i<vertices;i++)
	{
		for(int j=0;j<vertices;j++)
			g[i][j]=G[i][j];
	}
	for(int i=0;i<vertices;i++)
	{
		for(int j=0;j<vertices;j++)
			ST[i][j]=0;
	}
	for(int i=0;i<vertices;i++)
		father[i]=-1;
	while(count<vertices-1)
	{
		min=999;
		for(int v1=0;v1<vertices;v1++)
		{
			for(int v2=0;v2<vertices;v2++)
			{
				if(g[v1][v2]!=0 && g[v1][v2]<min)
				{
					min=g[v1][v2];
					t1=v1;
					t2=v2;
				}
			}
		}
		temp1=t1;
		temp2=t2;
		g[t1][t2]=g[t2][t1]=0;
		while(t1>=0)
		{
			root1=t1;
			t1=father[t1];
		}
		while(t2>=0)
		{
			root2=t2;
			t2=father[t2];
		}
		if(root1!=root2)
		{
			ST[temp1][temp2]=ST[temp2][temp1]=min;
			wt=wt+ST[temp1][temp2];
			father[root2]=root1;
			count++;
		}
	}
	cout<<"The MST is\n";
		cout<<"      ";
		for(int i=0;i<vertices;i++)
			cout<<i<<setw(5);
		cout<<"\n";
		for(int k=0;k<=vertices*5;k++)
			cout<<"-";
		cout<<"\n";
		for(int i=0;i<vertices;i++)
		{
			cout<<i<<"  |  ";
			for(int j=0;j<vertices;j++)
				cout<<ST[i][j]<<setw(5);
			cout<<"\n";
		}
		cout<<"\nThe weight is "<<wt<<endl<<endl;
}
void Graph :: displaygraph()
{
	cout<<"      ";
	for(int i=0;i<vertices;i++)
		cout<<i<<setw(5);
	cout<<"\n";
	for(int k=0;k<=vertices*5;k++)
		cout<<"-";
	cout<<"\n";
	for(int i=0;i<vertices;i++)
	{
		cout<<i<<"  |  ";
		for(int j=0;j<vertices;j++)
			cout<<G[i][j]<<setw(5);
		cout<<"\n";
	}
}

/*void Graph :: displayMST(int ***a)
{
	cout<<"      ";
	for(int i=0;i<vertices;i++)
		cout<<i<<setw(5);
	cout<<"\n";
	for(int k=0;k<=vertices*5;k++)
		cout<<"-";
	cout<<"\n";
	for(int i=0;i<vertices;i++)
	{
		cout<<i<<"  |  ";
		for(int j=0;j<vertices;j++)
			cout<<*(a[i][j])<<setw(5);
		cout<<"\n";
	}
}*/

int main()
{
	Graph g;
	int c;
	do
	{
		cout<<"Enter your choice\n1. Create a Graph\n2. Prims\n3. Krushkal\n0. Exit\n";
		cin>>c;
		switch(c)
		{
		case 1 : g.creategraph();
			 	 break;
		case 2 : g.Prims();
				 break;
		case 3 : g.Krushkal();
				 break;
		case 0 : break;
		}
	}while(c!=0);
	return 0;
}
