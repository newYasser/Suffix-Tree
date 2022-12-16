#include <iostream>

using namespace std;


struct SuffixNode{
    int startIdx;
    int endIdx; // len
    SuffixNode** children;
    SuffixNode(){}
};


class SuffixTree{

private:
    int n; //SIZE of the string
    SuffixNode * root;
    char* str;
    int*ans;

public:

    SuffixTree(int n , char *arr){
        this->n = n;
        root = new SuffixNode();
        root->children = new SuffixNode*[n];
        for(int i = 0; i < n;i++){
            root->children[i] = nullptr;
        }
        ans = new int[2];
        ans[0] = -1;
        ans[1] = 0;
        str = arr;
    }

     SuffixNode* creatNode (){
       SuffixNode* newNode = new SuffixNode();
       newNode->children = new SuffixNode*[n];
       for(int i = 0; i < n;i++){
            newNode->children[i] = nullptr;
        }
       return newNode;
    }

     //bana na$

    void build(SuffixNode* root, int idx){
        bool flag = true;
        int temp;
        if(str[idx] == '$')
            return;
        int i = 0;
        int j;
        for(;i < n;i++){
            if(!root->children[i])
              break;
            int s = root->children[i]->startIdx;
            int e = root->children[i]->endIdx;
            if(str[s] == str[idx]){
               temp = idx;
               int c = 0;
                for(j = s; j < s + e;j++){
                    c++;
                    if(str[j] != str[idx++]){
                        SuffixNode* newNode = creatNode();
                        newNode->startIdx = s;
                        newNode->endIdx = c - 1;
                        root->children[i]->startIdx = s + (c - 1);
                        root->children[i]->endIdx = e -(c - 1);
                        for(int k = 0; k < n;k++){
                            if(!newNode->children[k]){
                                newNode->children[k] = root->children[i];
                                root->children[i] = newNode;
                                break;
                            }
                        }
                        break;

                    }


                }
                build(root,temp + 1);
                flag = false;
                i = n;
                break;
            }
        }

        if(!root->children[i] && flag){
            root->children[i] = creatNode();
            root->children[i]->startIdx = i;
            root->children[i]->endIdx = n - i;
            build(root,idx +1);
        }

    }
    void constract(){
       build(root,0);
    }
    void printChildren(SuffixNode* root, int idx){

        if(!root->children[idx])
            return;
        printChildren(root,idx + 1);
        int s = root->children[idx]->startIdx;
        int e = root->children[idx]->endIdx;
        for(int i = s; i <s + e;i++){
            cout << str[i];
        }
        cout << "\ns = " << s<<  endl;
        cout << "e = " << e << endl;
        cout << endl;
        int j = -1;
        printChildren(root->children[idx],j + 1);
    }
    void print(){
        printChildren(root,0);
    }

    bool find(SuffixNode* root, int idx,char* subString,int subStringIdx,int size) {

        if(size <= subStringIdx - 1){
            return true;
        }
        int j = -1;
        //find(root,idx + 1,subString);
        int s = root->children[idx]->startIdx;
        int e = root->children[idx]->endIdx;
        for(int i = s; i <s + e;i++){
            if(subString[subStringIdx] == str[i] && i == s + e - 1){
                cout << s << " ";
                if(find(root->children[idx],j + 1,subString,subStringIdx+1,size)) {
                    cout << s << endl;
                    break;
                }
            }
            else if(subString[subStringIdx] != str[i]){
                 if(find(root,idx + 1,subString,subStringIdx,size)){
                     return true;
                 }
                 else{
                     find(root->children[idx],idx + 1,subString,0,size);
                 }
            }

            subStringIdx++;
        }
        return true;
    }

   bool find(char*subString,int size){
      return find(root,0,subString,0,size);
    }

};


//b a n a n a $

int main()
{
    int n = 13;
    char *arr = new char[n];
    for(int i = 0; i < n;i++){
        cin >> arr[i];
    }
   char* subString = new char[3];

    for(int i = 0; i < 3;i++){
        cin >> subString[i];
    }
    SuffixTree t(n,arr);
    t.constract();

    t.find(subString,3);
 //   t.print();
    return 0;
}
