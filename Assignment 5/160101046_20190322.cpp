#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<list>
#include<unordered_set>

using namespace std;

class Bucket{
public:
	int localDepth;
	list<int> bucket;
};
class ExtendibleHashing{
	int globalDepth,bucketSize;
	vector<Bucket*> dir;
public:
	void createHashTable(int globalDepth,int bucketSize);
	void insertElement(int val);
	bool searchElement(int val);
	bool deleteElement(int val);
	int getBucketIndex(int val);
	void doubleHashTable();
	void splitBucket(int bucketIndex);
	int twoPower(int p);
	void printHashTable();
};

void ExtendibleHashing::createHashTable(int globalDepth,int bucketSize){
	int buckets = twoPower(globalDepth);
	this->globalDepth = globalDepth;
	this->dir.resize(buckets);
	this->bucketSize=bucketSize;
	for(int i=0;i<buckets;i++){
		this->dir[i] = new Bucket();
		this->dir[i]->localDepth = globalDepth;
	}
}

int ExtendibleHashing::getBucketIndex(int val){
	int lsbOfOnes = twoPower(this->globalDepth)-1;
	return val & lsbOfOnes;
}

void ExtendibleHashing::insertElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	if(this->dir[bucketIndex]->bucket.size() >= this->bucketSize){
		if(this->globalDepth == this->dir[bucketIndex]->localDepth){
      if(this->dir[bucketIndex]->bucket.size() > this->bucketSize){
        // case 2.1
        // cout<<"2.1"<<endl;
        this->dir[bucketIndex]->bucket.push_back(val);
      }else{
        // case 2.2
        // cout<<"2.2"<<endl;
        bool flag = false;
        for(int i=0;i<this->dir.size();i++){
          if(i!=bucketIndex){
            if(this->dir[i]->bucket.size() <= this->bucketSize){
              flag = true;
            }
          }
        }
        if(!flag){
          // case 2.2.1
          // cout<<"2.2.1"<<endl;
          int size = this->dir.size();
          this->doubleHashTable();
          unordered_set<Bucket*> uset;
          for(int i=0;i<size;i++){
            if(uset.find(this->dir[i])!=uset.end())
        			continue;
        		uset.insert(this->dir[i]);
            this->splitBucket(i);
          }
          int index = this->getBucketIndex(val);
          this->dir[index]->bucket.push_back(val);
        }else{
          // case 2.2.2
          // cout<<"2.2.2"<<endl;
          this->dir[bucketIndex]->bucket.push_back(val);
        }
      }
		}
		else{
      // case 1
      // cout<<"1"<<endl;
      // local depth < global depth
			this->splitBucket(bucketIndex);
      this->insertElement(val);
		}
	}
	else{
    // case 0
    // cout<<"0"<<endl;
		this->dir[bucketIndex]->bucket.push_back(val);
	}
}

bool ExtendibleHashing::searchElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	for(auto itr = this->dir[bucketIndex]->bucket.begin(); itr!=this->dir[bucketIndex]->bucket.end(); itr++)
		if(*itr==val)
			return true;
	return false;
}

bool ExtendibleHashing::deleteElement(int val){
	int bucketIndex = this->getBucketIndex(val);
	for(auto itr = this->dir[bucketIndex]->bucket.begin(); itr!=this->dir[bucketIndex]->bucket.end(); itr++){
		if(*itr==val){
			this->dir[bucketIndex]->bucket.erase(itr);
			return true;
		}
	}
	return false;
}

void ExtendibleHashing::doubleHashTable(){
	int size = this->dir.size();
	this->globalDepth++;
	this->dir.resize(2*size);
	for(int i=size;i<2*size;i++)
		this->dir[i]=this->dir[i-size];
}

void ExtendibleHashing::splitBucket(int bucketIndex){
	int localDepthPower = twoPower(this->dir[bucketIndex]->localDepth);
	int firstBucketIndex = bucketIndex & (localDepthPower-1);
	int secondBucketIndex = firstBucketIndex + localDepthPower;
	/*creating new bucket and updating local depths*/
	this->dir[secondBucketIndex] = new  Bucket();
	this->dir[secondBucketIndex]->localDepth = ++this->dir[firstBucketIndex]->localDepth;

	list<int> &firstBucket = this->dir[firstBucketIndex]->bucket;
	list<int> &secondBucket = this->dir[secondBucketIndex]->bucket;
	/*distributing values to two buckets*/
	for(auto itr=firstBucket.begin();itr!=firstBucket.end();){
		if(*itr & localDepthPower){
			secondBucket.push_back(*itr);
			itr = firstBucket.erase(itr);
		}
		else itr++;
	}
	/*pointing to proper buckets after spliting*/
	localDepthPower = 2*localDepthPower;
	for(int i=secondBucketIndex+localDepthPower; i < this->dir.size(); i=i+localDepthPower)
		this->dir[i] = this->dir[secondBucketIndex];
}

int ExtendibleHashing::twoPower(int p){
	return 1<<p;
}

void ExtendibleHashing::printHashTable(){
	cout<<"\n ***** Hash Table ***** \n"<<endl;
	cout<<"globalDepth :: " << this->globalDepth<<endl;
	unordered_set<Bucket*> uset;
	cout<<"localDepth ::| Elements |"<<endl;
	for(int i=0; i<this->dir.size(); i++){
		if(uset.find(this->dir[i])!=uset.end())
			continue;
		cout<<this->dir[i]->localDepth<<" :: | ";
		uset.insert(this->dir[i]);
		for(auto l:this->dir[i]->bucket)
			cout<<l<<" ";
		cout<<"|" <<endl;
	}
	cout<<endl;
}

int main(){

	int choice;
	ExtendibleHashing *d=NULL;
	do{
		cout<<"1. Create new ExtendibleHashTable"<<endl;
		cout<<"2. Add an element to the HashTable"<<endl;
		cout<<"3. Search an element to the HashTable"<<endl;
		cout<<"4. Delete an element from the HashTable"<<endl;
		cout<<"5. Print HashTable"<<endl;

		cout<<"Any other choice to exit"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		cout<<"You entered "<<choice<<endl;
		switch(choice){
			case 1:
				if(d!=NULL)
					delete d;
				d= new ExtendibleHashing();
				int globalDepth;
				cout<<"Enter global depth: ";
				cin>>globalDepth;
				int bucketSize;
				cout<<"Enter number of entries in bucket: ";
				cin>>bucketSize;
				d->createHashTable(globalDepth,bucketSize);
				break;
			case 2:
				if(!d){
					cout<<"No hash table created!"<<endl;
					continue;
				}
				int add;
				cout<<"Enter element to add: ";
				cin>>add;
				d->insertElement(add);
				break;
			case 3:
				if(!d){
					cout<<"No hash table created!"<<endl;
					continue;
				}
				int search;
				cout<<"Enter element to search: ";
				cin>>search;
				if(d->searchElement(search))
					cout<<"Element is found"<<endl;
				else
					cout<<"Element is not found"<<endl;
				break;
			case 4:
				if(!d){
					cout<<"No hash table created!"<<endl;
					continue;
				}
				int del;
				cout<<"Enter element to delete: ";
				cin>>del;
				if(d->deleteElement(del))
					cout<<"Element is deleted"<<endl;
				else
					cout<<"Element is not found"<<endl;
				break;
			case 5:
				if(!d){
					cout<<"No hash table created!"<<endl;
					continue;
				}
				d->printHashTable();
				break;
			default:
				return 0;
		}
	}while(true);
}
