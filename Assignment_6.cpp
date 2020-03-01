//============================================================================
// Name        : Assignment_6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;
class Entry
{
	string word,meaning;
public :
	Entry()
{
		word=meaning="\0";
}
	friend class HashTable;
};

class HashTable
{
	Entry E[50];
public :
	/* private :
	 *    Entry *E[50];
	 * HashTable()
{
		for(int i=0;i<50;i++)
			E[i]=NULL;
}*/
	int hashfun(string);
	void insert(string,string);
	void insertwr(string, string);
	int find(string);
	void modify(string);
	void delete_key(string);
	void display();
};

int HashTable :: hashfun(string key)
{
	int i=0,c=0;
	while(key[i]!='\0')
	{
		c=c+int(key[i]);
		i++;
	}
	return(c%50);
}

void HashTable :: insert(string key, string value)
{
	int index;
	index=hashfun(key);
	if(E[index].word=="\0")
	{
		E[index].word=key;
		E[index].meaning=value;
	}
	else
	{
		while(E[index].word!="\0")
			index=(index+1)%50;
		E[index].word=key;
		E[index].meaning=value;
	}
	display();
}

/*  if(E[index]==NULL)
	{
		E[index]=new Entry(key,value);
	}
	else
	{
		while(E[index]!=NULL)
			index=(index+1)%50;
		E[index]=new Entry(key,value);
	}*/
void HashTable :: insertwr(string key,string value)
{
	int index,temp,idx;
	index=hashfun(key);
	temp=index;
	if(E[index].word=="\0")
	{
		E[index].word=key;
		E[index].meaning=value;
	}
	else
	{
		idx=hashfun(E[index].word);
		if(idx!=index)
		{
			while(E[temp].word!="\0")
				temp=(temp+1)%50;
			E[temp].word=E[index].word;
			E[temp].meaning=E[index].meaning;
			E[index].word=key;
			E[index].meaning=value;
		}
		else
		{
			while(E[index].word!="\0")
				index=(index+1)%50;
			E[index].word=key;
			E[index].meaning=value;
		}
	}
	display();
}

int HashTable :: find(string key)
{
	int index,found=0,c=1;
	index=hashfun(key);
	if(E[index].word==key)
	{
		cout<<"The Word is found\n";
		cout<<"The number of collisions = "<<c<<endl;
		return index;
	}
	else
	{
		int i=index+1;
		while(i!=index)
		{
			c++;
			if(E[i].word==key)
			{
				found=1;
				break;
			}
			else
				i=(i+1)%50;
		}
		if(found==1)
		{
			cout<<"The Word is found\n";
			cout<<"The number of collisions = "<<c<<endl;
			return i;
		}
		else
			return -1;
	}
}

void HashTable :: modify(string key)
{
	int index;
	string value;
	index=find(key);
	if(index==-1)
		cout<<"The Word is not found\n";
	else
	{
		cout<<"Enter the new meaning\n";
		cin>>value;
		E[index].meaning=value;
		cout<<"The Meaning has been modified\n\n";
		display();
	}
}

void HashTable :: delete_key(string key)
{
	int loc,index,idxtemp;
	loc=find(key);
	if(loc==-1)
		cout<<"The Word is not found\n";
	else
	{
		index=hashfun(E[loc].word);
		E[loc].word=E[loc].meaning="\0";
		if(loc==index)
		{
			for(int i=index+1;i!=index;i=(i+1)%50)
			{
				idxtemp=hashfun(E[i].word);
				if(idxtemp==index)
				{
					E[loc].word=E[i].word;
					E[loc].meaning=E[i].meaning;
					E[i].word="\0";
					E[i].meaning="\0";
					break;
				}
			}
		}
		cout<<"The Entry has been deleted\n\n";
		display();
	}
}
void HashTable :: display()
{
	cout<<"Index\t\tWord\t\tMeaning\n";
	for(int i=0;i<50;i++)
	{
		if(E[i].word!="\0")
			cout<<i<<"\t\t"<<E[i].word<<"\t\t"<<E[i].meaning<<"\n";
	}
}

int main()
{
	HashTable h;
	string w,m;
	int c,c1,fin;
	do
	{
		cout<<"Enter your choice\n1. Without Replacement\n2. With Replacement\n0. Exit\n";
		cin>>c;
		switch(c)
		{
		case 1 : do
				 {
					 cout<<"\nSelect for Without Replacement\n1. Insert\n2. Search\n3. Modify\n4. Delete\n0. Main Menu\n";
					 cin>>c1;
					 switch(c1)
					 {
					 case 1 : cout<<"Enter the word\n";
					 	 	  cin>>w;
					 	 	  cout<<"Enter the meaning\n";
					 	 	  cin>>m;
					 	 	  h.insert(w,m);
					 	 	  break;
					 case 2 : cout<<"Enter the word to search\n";
					 	  	  cin>>w;
					 	  	  fin=h.find(w);
					 	  	  if(fin==-1)
					 	  		  cout<<"The Word is not found\n";
					 	 	  break;
					 case 3 : cout<<"Enter the word\n";
					 	 	  cin>>w;
					 	 	  h.modify(w);
					 	 	  break;
					 case 4 : cout<<"Enter the word to delete\n";
					 	 	  cin>>w;
					 	 	  h.delete_key(w);
					 	 	  break;
					 case 0 : break;
					 default : cout<<"Invalid Choice\n";
					 }
				 }while(c1!=0);
				 break;
		case 2 : do
		 	 	 {
			 	 	 cout<<"\nSelect for With Replacement\n1. Insert\n2. Search\n3. Modify\n4. Delete\n0. Main Menu\n";
			 	 	 cin>>c1;
			 	 	 switch(c1)
			 	 	 {
			 	 	 case 1 : cout<<"Enter the word\n";
			 	 	  	  	  cin>>w;
			 	 	  	  	  cout<<"Enter the meaning\n";
			 	 	  	  	  cin>>m;
			 	 	  	  	  h.insertwr(w,m);
			 	 	  	  	  break;
			 	 	 case 2 : cout<<"Enter the word to search\n";
			 	  	  	  	  cin>>w;
			 	  	  	  	  fin=h.find(w);
			 	  	  	  	  if(fin==-1)
			 	  	  	  		  cout<<"The Word is not found\n";
			 	 	 	 	  break;
			 	 	 case 3 : cout<<"Enter the word\n";
			 	 			  cin>>w;
			 	 			  h.modify(w);
			 	 			  break;
			 	 	case 4 : cout<<"Enter the word to delete\n";
			 	 			 cin>>w;
			 	 			 h.delete_key(w);
			 	 			 break;
			 	 	case 0 : break;
			 	    default : cout<<"Invalid Choice\n";
			 	 	 }
		 	 	 }while(c1!=0);
				 break;
		case 0 : break;
		default : cout<<"Invalid Choice\n";
		}
	}while(c!=0);
	return 0;
}
