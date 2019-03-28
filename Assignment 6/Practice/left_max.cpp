#include<bits/stdc++.h>
using namespace std;

struct Bucket{
  vector<int> val;
  vector<Bucket*> child;
  Bucket * next;
  Bucket * prev;
  bool leaf;
};

struct Btree{
  Bucket * root;
  Bucket * head;
  int indexSize;
  int dataSize;
};

void insertionSort(vector<int> &v, int key){
  int i;
  for(i=0;i<v.size();i++){
    if(v[i]>key){
      break;
    }
  }
  if(i==v.size()){
    v.push_back(key);
  }else{
    v.insert(v.begin()+i, key);
  }
  return;
}

int insert(Btree * tree, Bucket * cur, int key){
  if(cur->leaf){
    insertionSort(cur->val, key);
    if(cur->val.size() > tree->dataSize){
      Bucket * splitBucket = new Bucket();
      splitBucket->leaf = true;
      int n = cur->val.size();
      for(int i=n/2+1;i<n;i++){
        splitBucket->val.push_back(cur->val[i]);
      }
      for(int i=n/2+1;i<n;i++){
        cur->val.pop_back();
      }
      splitBucket->next = cur->next;
      cur->next = splitBucket;
      splitBucket->prev = cur;
      return 1;
    }else{
      return 0;
    }
  }else{
    int i;
    for(i=0;i<cur->val.size();i++){
      if(key<cur->val[i]){
        break;
      }
    }
    if(insert(tree, cur->child[i], key)){
      Bucket * b1 = cur->child[i];
      Bucket * b2 = cur->child[i]->next;
      if(b1->leaf){
        insertionSort(cur->val, b1->val[b1->val.size()-1]);
        int i;
        for(i=0;i<cur->val.size();i++){
          if(cur->val[i]==b1->val[b1->val.size()-1])break;
        }
        cur->child.insert(cur->child.begin()+i+1,b2);
      }else{
        insertionSort(cur->val, b2->val[0]);
        int i;
        for(i=0;i<cur->val.size();i++){
          if(cur->val[i]==b2->val[0])break;
        }
        cur->child.insert(cur->child.begin()+i+1,b2);
        b2->val.erase(b2->val.begin());
      }
      if(cur->val.size() > tree->indexSize){
        int n = cur->val.size();
        Bucket * splitBucket = new Bucket();
        splitBucket->leaf = false;
        splitBucket->next = cur->next;
        cur->next = splitBucket;
        splitBucket->prev = cur;
        for(int i=n/2;i<n;i++){
          splitBucket->val.push_back(cur->val[i]);
          splitBucket->child.push_back(cur->child[i+1]);
        }
        for(int i=n/2;i<n;i++){
          cur->val.pop_back();
          cur->child.pop_back();
        }
        return 1;
      }
      return 0;
    }else{
      return 0;
    }
  }
}

void insertElement(Btree * tree, int key){
  if(insert(tree, tree->root, key)){
    Bucket * new_root = new Bucket();
    new_root->leaf = false;
    new_root->next = NULL;
    new_root->prev = NULL;
    Bucket * cur_root = tree->root;
    Bucket * cur_next = tree->root->next;
    if(cur_root->leaf){
      new_root->val.push_back(cur_root->val[cur_root->val.size()-1]);
    }else{
      new_root->val.push_back(cur_next->val[0]);
      cur_next->val.erase(cur_next->val.begin());
    }
    tree->root = new_root;
    new_root->child.push_back(cur_root);
    new_root->child.push_back(cur_next);
    return;
  }
}

void printLevelOrder(Bucket * b){
  Bucket * temp = b;
  while(b!=NULL){
    cout<<"|"<<b->val.size()<<"|";
    for(int i=0;i<b->val.size();i++){
      cout<<b->val[i]<<" ";
    }
    cout<<"||";
    b = b->next;
  }
  cout<<endl;
  if(!temp->leaf){
    printLevelOrder(temp->child[0]);
  }
  return;
}

int main(){
  Btree * tree = NULL;
  do {
    cout << "1. Create new tree" << endl;
    cout << "2. Add new key to the tree" << endl;
    cout << "3. Search a key in the tree" << endl;
    cout << "4. Postorder traversal of the tree" << endl;
    cout << "Any other choice to exit" << endl;
    cout << "Enter your choice: ";
    int choice, key;
    cin >> choice;
    cout << "You entered " << choice << endl;
    if(choice==1){
        if(tree != NULL){
          delete tree;
        }
        int numIndexPointers, numDataPointers;
        cout<<"Enter number of Index pointers: ";
        cin>>numIndexPointers;
        cout<<"Enter number of Data pointers: ";
        cin>>numDataPointers;
        tree = new Btree();
        Bucket * root = new Bucket();
        root->leaf = true;
        root->next = NULL;
        root->prev = NULL;
        tree->root = root;
        tree->head = root;
        tree->indexSize = numIndexPointers;
        tree->dataSize = numDataPointers;
    }else if(choice==2){
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
        }
        cout << "Enter key to add ";
        cin >> key;
        insertElement(tree, key);
    }else if(choice==3){
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
        }
        cout << "Enter key to search: ";
        cin >> key;
    }
    else if(choice==4){
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
        }
        // cout<<tree->root->val[0]<<endl;
        printLevelOrder(tree->root);
    }else{
      return 0;
    }
  }
  while(true);
	return 0;
}
