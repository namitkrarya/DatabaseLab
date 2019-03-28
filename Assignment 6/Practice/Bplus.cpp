#include <bits/stdc++.h>
using namespace std;
#define ll long long int

int n,m;
class Bucket{
public:
	vector<int> data;
	vector<Bucket*> childptr;
	Bucket * next;
	bool isLeaf;
};

class Bplus
{
	public:
	Bucket * root = NULL;
	Bucket * head = NULL;

 	void createTree();
 	void printTree();
 	void pri(Bucket*);
 	void insert1(int);
 	bool search(int);
 	int insertElement(Bucket*,int);
};

void Bplus::createTree()
{
	Bucket * b = new Bucket();
	this->root = b;
	this->head = b;
	b-> isLeaf = true;
	b->next = NULL;
	return;
}

int Bplus::insertElement(Bucket * b , int val)
{
	if (b->isLeaf==true)
	{
		b->data.push_back(val);
		sort(b->data.begin(), b->data.end());
		if (b->data.size()>n)
		{
			cout << "split leaf with first data " << b->data[0] << endl;
			Bucket * b1 = new Bucket();
			b1->next = b->next;
			b->next = b1;
			b1->isLeaf= true;

			for (int i = n/2; i <= n; ++i)
				b1->data.push_back(b->data[i]);
			for (int i = n/2; i <= n; ++i)
				b->data.pop_back();
			return 1;
		}
		return 0;
	}
	else
	{
		Bucket * b1 = b->childptr[0];
		int size1 = b->data.size();
		for (int i = 0; i < size1; ++i)
		{
			if (b->data[i]>val)
				break;
			b1 = b->childptr[i+1];
		}
		int c = insertElement(b1,val);

		if (c==1)
		{
			Bucket *b2  = b1->next;
			int d = b2->data[0];
			if (b2->isLeaf==false)
			{
				b2->data.erase(b2->data.begin());
			}
			int p=b->data.size();
			for (int i = 0; i < b->data.size(); ++i)
			{
				if (b->data[i]>d)
				{
					p = i;
					break;
				}
			}
			b->data.insert(b->data.begin()+p,d);
			b->childptr.insert(b->childptr.begin()+p+1,b2);

			if (b->data.size() > m)
			{
				cout << "split index node with first data" << b->data[0] << endl;
				Bucket * b3 = new Bucket();
				b3->next = b->next;
				b->next = b3;
				b3->isLeaf = false;

				for (int i = m/2 + 1; i <= m; ++i)
				{
					b3->data.push_back(b->data[i]);
					b3->childptr.push_back(b->childptr[i+1]);
				}
				for (int i = m/2 + 1; i <= m; ++i)
				{
					b->data.pop_back();
					b->childptr.pop_back();
				}
				return 1;
			}
			return 0;
		}
	}
}

void Bplus::insert1(int val)
{
	int c = insertElement(this->root,val);
	if (c==1)
	{
		Bucket *r1 = new Bucket();
		r1->isLeaf = false;
		r1->next = NULL;

		Bucket *b1 = this->root;
		Bucket *b2  = b1->next;
		r1->childptr.push_back(b1);
		r1->childptr.push_back(b2);
		this->root = r1;

		int d = b2->data[0];
		if (b2->isLeaf==false)
		{
			b2->data.erase(b2->data.begin());
		}
		r1->data.push_back(d);
	}
}

bool Bplus::search(int val)
{
	Bucket * r1 = this->root;

	while(!r1->isLeaf)
	{
		int d = r1->data.size();
		for (int i = 0; i < r1->data.size(); ++i)
		{
			cout << r1->data[i] << " " ;
			if (r1->data[i] > val)
			{
				d = i;
				break;
			}
		}
		r1 = r1->childptr[d];
	}

	for (int i = 0; i < r1->data.size(); ++i)
	{
		cout << r1->data[i] << " " ;
		if (r1->data[i] == val)
			return true;
		if (r1->data[i] > val)
			return false;
	}
	return false;
}

void Bplus::pri(Bucket * r1){

	cout << r1->data.size() << " | " ;

	for (int i = 0; i < r1->data.size(); ++i)
	{
		cout << r1->data[i] << " " ;
	}
	cout << " || ";
}

void Bplus::printTree()
{
	Bucket * r = this->root;
	cout << endl << endl;
	while(r)
	{
		Bucket *r1 = r;
		cout << "|| ";
		while(r1)
		{
			pri(r1);
			r1 = r1->next;
		}

		if (r->childptr.size()==0)
			break;

		r = r->childptr[0];
		cout << endl;
	}
	cout << endl << endl;
}

int main(){

	Bplus * d = NULL;

	do{
		int choice;
		cin>>choice;
		cout<<"You entered "<<choice<<endl;
		switch(choice){
			case 1:
				if(d!=NULL)
					delete d;
				d= new Bplus();
				cout << "Enter size of data node\n";
				cin>>n;
				cout << "Enter size of index node\n";
				cin>>m;
				d->createTree();
				break;
			case 2:
				int add;
				cout<<"Enter element to add: ";
				cin>>add;
				d->insert1(add);
				break;
			case 3:
				int search;
				cout<<"Enter element to search: ";
				cin>>search;
				if(d->search(search))
					cout<<"Element is found"<<endl;
				else
					cout<<"Element is not found"<<endl;
				break;
			case 4:
				d->printTree();
				break;
			default:
				return 0;
		}
	}while(true);

	return 0;
}

// 1 4 3  2 1 2 5 2 9 2 11 2 15 2 3 2 4 2 2 2 6 2 7 2 8 2 10
