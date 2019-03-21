/* written by Namit Kumar & Abhinav Mishra on 21/03/2019 11:55PM */

#include<bits/stdc++.h>
using namespace std;

struct Bucket{
  list<int> bucket;
};

struct LinearHash{
  int level;
  int next;
  int nBucket;
  int bucketSize;
  vector<Bucket*> dir;
};

int getIndex(struct LinearHash *hash, int val){
    if(val%((int)pow(2, hash->level)*hash->nBucket) >= hash->next){
      return val%((int)pow(2, hash->level)*hash->nBucket);
    }else{
      return val%((int)pow(2, hash->level+1)*hash->nBucket);
    }
}

void increaseBucket(struct LinearHash *hash){
  Bucket * bucket = new Bucket();
  hash->dir.push_back(bucket);
  return;
}

void splitBucket(struct LinearHash * hash){
  list <int> &bucket = hash->dir[hash->next]->bucket;
  list <int> &bucket2 = hash->dir[hash->dir.size()-1]->bucket;
  for(auto itr = bucket.begin();itr!=bucket.end();){
    if((*itr)%((int)pow(2, hash->level+1)*hash->nBucket)==hash->dir.size()-1){
      bucket2.push_back(*itr);
      itr = bucket.erase(itr);
    }else{
      itr++;
    }
  }
}


void insert(struct LinearHash * hash, int val){
  int index = getIndex(hash, val);
  if(hash->dir[index]->bucket.size() > 0 && hash->dir[index]->bucket.size()%hash->bucketSize==0){
    increaseBucket(hash);
    splitBucket(hash);
    hash->next = (hash->next+1)%((int)pow(2, hash->level)*hash->nBucket);
    if(hash->next==0)
      hash->level++;
  }
  index = getIndex(hash, val);
  hash->dir[index]->bucket.push_back(val);
}

bool searchElement(struct LinearHash * hash, int val){
  int index = getIndex(hash, val);
  for(auto itr = hash->dir[index]->bucket.begin();itr!=hash->dir[index]->bucket.end();itr++){
    if(*itr==val){
      return true;
    }
  }
  return false;
}

void printHashTable(struct LinearHash * hash){
  for(int i=0;i<hash->dir.size();i++){
    cout<<i<<" : ";
    for(auto l:hash->dir[i]->bucket)
			cout<<l<<" ";
    cout<<endl;
  }
}

int main(){
  LinearHash * hash = new LinearHash();
  hash->level = 0;
  hash->next = 0;
  cout<<"Enter total no. of buckets : ";
  cin>>hash->nBucket;
  for(int i=0;i<hash->nBucket;i++){
    hash->dir.push_back(new Bucket());
  }
  cout<<"Enter bucket size : ";
  cin>>hash->bucketSize;
  while(1){
    int a;
    cin>>a;
    if(a==-1){
      break;
    }
    insert(hash, a);
  }
  printHashTable(hash);
  return 0;

}
