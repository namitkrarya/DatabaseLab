#include <bits/stdc++.h>

using namespace std;

struct Node{
    vector <int> data;
    vector <Node*> index_ptr;
    bool leaf; 
    int totalKeys;
    Node *next;
} *root;
struct NewNode{
    int d;
    Node* entry;
};

#define leafsize 4
#define indexsize 3
int globaldepth;

Node* init(int size){
    Node *node = new Node;
    node->data.resize(size+4);
    node->index_ptr.resize(size+4);
    for(int i=0;i<=size;i++)
        node->index_ptr[i]=NULL;
    node->totalKeys = 0;
    node->leaf = false;
    node->next=NULL;
    return node;
}

// void insert(Node* &root , int key,int &depth){
//     if(depth==0){
//         if(root->totalKeys==leafsize){
//             Node *new_root = init(indexsize);
//             new_root->index_ptr[0] = root;
//             new_root->totalKeys = 1;
//             root = new_root;
//             depth = depth +1;
//             split(new_root,0);
//         }
//         else{
//             root->data.push_back(key);
//         }
//     }
//     else{
//         goToLeaf(root,key,depth,newnode);
//     }
// }

int splitnonleaf(Node *&y,Node *&z){
    int mid = (indexsize+1)/2;
    int midvalue = y->data[mid];
    for(int i=0;i<indexsize-mid;i++){
        z->data[i] = y->data[mid+1+i];
        z->index_ptr[i] = y->index_ptr[mid+1+i];
    }
    z->index_ptr[indexsize-mid] = y->index_ptr[indexsize+1];
    y->totalKeys = mid;
    z->totalKeys = mid-1;
    z->next = y->next;
    y->next = z;
    return midvalue;
}
void splitleaf(Node *&y,Node *&z){

    int mid = leafsize/2;

    z->totalKeys = mid;
    for(int j=0;j<mid;j++){
        z->data[j] = y->data[mid+1+j];
    }
    y->totalKeys = mid+1;
    z->next = y->next;
    y->next = z;

}


void goToLeaf(Node* node , int key,int depth,NewNode* &newnode){
    if(depth==0){
        if(node->totalKeys==leafsize){
            int i = node->totalKeys-1;
            while(i >= 0 && key < node->data[i]){
                node->data[i+1] = node->data[i];
                i = i - 1;
            }    
            i = i + 1;
            node->data[i]=key;
            node->totalKeys++;
            Node* z= init(leafsize);
            splitleaf(node,z);
            newnode = new NewNode;
            newnode->d = z->data[0];
            newnode->entry = z;
            if(node==root){
                root=init(indexsize);
                root->data[0] = newnode->d;
                root->index_ptr[0] = node;
                root->index_ptr[1] = z;
                root->totalKeys++;
                globaldepth = globaldepth + 1;
            }
            return ;
        }
        else{
            int i = node->totalKeys-1;
            while(i >= 0 && key < node->data[i]){
                node->data[i+1] = node->data[i];
                i = i - 1;
            }    
            i = i + 1;
            node->data[i]=key;
            node->totalKeys++;
            newnode = NULL;
            return;
        }
    }
    else{
        int i = node->totalKeys-1;
        while(i >= 0 && key < node->data[i])
			i = i - 1;
		i = i + 1;
        goToLeaf(node->index_ptr[i],key,depth-1,newnode);
        if(newnode!=NULL){            
            node->index_ptr[node->totalKeys+1] = node->index_ptr[node->totalKeys];
            for(int j=node->totalKeys-1;j>i;j--){
                node->index_ptr[j+1] = node->index_ptr[j];
                node->data[j+1]=node->data[j];
            }
            node->data[i+1]=node->data[i];
            node->data[i]=newnode->d;
            node->index_ptr[i+1] = newnode->entry;
            if(node->totalKeys==indexsize){
                Node* z = init(indexsize);
                int mid = splitnonleaf(node,z);
                newnode->d = mid;
                newnode->entry = z;
                if(node == root){
                    root = init(indexsize);
                    root->data[0] = mid;
                    root->index_ptr[0] = node;
                    root->index_ptr[1] = z;
                    globaldepth = globaldepth + 1;
                    root->totalKeys++;
                }
            }
            else{
                newnode=NULL;
                node->totalKeys++;
            }
        }
    }
}

void print(Node *node){
    if(node!=NULL){
        Node *child = node->index_ptr[0];
        while(node!=NULL){
            for(int i=0;i<node->totalKeys;i++)
                cout<<node->data[i]<<" ";
            cout<<"->";
            node  = node->next;    
        }
        cout<<endl;
        print(child);
    }
}


int main(){
    root = init(leafsize);
    globaldepth =0;
    NewNode *newnode=NULL;
    while(1){
        int x;
        cin>>x;
        if(x==2){
            cout<<"enter no. to insert-";
            int y;
            cin>>y;
            goToLeaf(root,y,globaldepth,newnode);
        }
        else if(x==4){
            print(root);
        }
        else
            break;
        
    }
    
}