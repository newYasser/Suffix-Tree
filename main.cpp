#include <iostream>

using namespace std;


struct SuffixNode{
    int startIdx = -1;
    int endIdx = -1; // len
    SuffixNode** children;
    SuffixNode(){}
};


class SuffixTree{

private:
    int n;
    SuffixNode * root;
    char* str;

public:
     // passing the  of the string and the string itself
     // initialize the array of pointers to nodes to nullptr and make it to max. size possible which the is the size
     //of the string
    SuffixTree(int n , char *arr)
    {
        this->n = n;
        root = new SuffixNode();
        root->children = new SuffixNode*[n];
        for(int i = 0; i < n;i++)
        {
            root->children[i] = nullptr;
        }
        str = arr;
    }
     // creating new  the node
     // @return pointer of SuffixNode and initialize the array of pointers to null
     SuffixNode* creatNode ()
     {
       SuffixNode* newNode = new SuffixNode();
       newNode->children = new SuffixNode*[n];
       for(int i = 0; i < n;i++)
       {
            newNode->children[i] = nullptr;
       }
       return newNode;
    }
    /*
     * this function starts from the root and search in its children for the substring if not found it creat
     * a new node and make the start idx with the i and the len will be the rest of the string.
     *
     * it keeps creat new nodes until finds a substring and search for the common substrings then it creat new node
     * for the common substrings
     *
     * the new node will be the root child and the  root child will be child to the new node
     *
     * */
    void build(SuffixNode* root, int idx)
    {
        bool flag = true;
        int temp;
        if(str[idx] == '$')
            return;
        int i = 0;
        int j;
        for(;i < n;i++)
        {
            if(!root->children[i])
                break;

            int s = root->children[i]->startIdx;
            int e = root->children[i]->endIdx;

            if(str[s] == str[idx]){
               temp = idx;
               int c = 0;
                for(j = s; j < s + e;j++){
                    c++;
                    if(str[j] != str[idx++])
                    {
                        SuffixNode* newNode = creatNode();
                        newNode->startIdx = s;
                        newNode->endIdx = c - 1;
                        root->children[i]->startIdx = s + (c - 1);
                        root->children[i]->endIdx = e -(c - 1);
                        for(int k = 0; k < n;k++)
                        {
                            if(!newNode->children[k])
                            {
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

        if(!root->children[i] && flag)
        {
            root->children[i] = creatNode();
            root->children[i]->startIdx = i;
            root->children[i]->endIdx = n - i;
            build(root,idx +1);
        }

    }
    void constract()
    {
       build(root,0);
    }
    // the print function starts from the root and keep traversing to the node
    // and prints the start till the end of the node
    // it shows the nodes of the tree
    void printChildren(SuffixNode* root, int idx)
    {

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
    void print()
    {
        printChildren(root,0);
    }
    // the find function is similar to the print function
    // the only difference it checks if the sub string is found or not and print the start idx of it
    void  find(SuffixNode* root, int idx,char* subString,int subStringIdx,int size)
    {

        if(!root->children[idx])
            return;
        bool flag = true;
        bool startSearch = false;
        find(root,idx + 1,subString,subStringIdx,size);
        int s = root->children[idx]->startIdx;
        int e = root->children[idx]->endIdx;
        for(int i = s; i < s + e && subStringIdx < size;i++){
            if(str[i] != subString[subStringIdx]) {
                flag = false;
                break;
            }
            subStringIdx++;
        }
        if(flag)
        {
            cout << s << endl;
            return;
        }
        int j = -1;
        if(subStringIdx == size) subStringIdx = 0;

        find(root->children[idx],j + 1,subString,subStringIdx,size);
    }

   void find(char*subString,int size)
   {
       find(root,0,subString,0,size);
    }

};



int main()
{
    int n = 10;
    char* String ={ new char[n]{'b','a','n','a','a','a','a','b','a','$'} } ;
    SuffixTree t(n,String);
    t.constract();

    int n2 = 3;
    char * SubString =  { new char[n2]{'n','a','a'} };
    t.find(SubString,n2);
    delete[] SubString;

    n2 = 2;
    SubString =  { new char[n2]{'n','a'} };
    t.find(SubString,n2);
    delete[] SubString;


    n2 = 4;
    SubString =  { new char[n2]{'n','a','n','a'} };
    t.find(SubString,n2);
    delete[] SubString;

    n2 = 1;
    SubString =  { new char[n2]{'a'} };
    t.find(SubString,n2);
    delete[] SubString;

    n2 = 6;
    SubString =  { new char[n2]{'n','a','a','a','a','b'} };
    t.find(SubString,n2);
    delete[] SubString;

    n2 = 4;
    SubString =  { new char[n2]{'a','a','a','b'} };
    t.find(SubString,n2);
    delete[] SubString;

    n2 = 2;
    SubString =  { new char[n2]{'a','b'} };
    t.find(SubString,n2);
    delete[] SubString;


    n2 = 6;
    SubString =  { new char[n2]{'a','b','x','s','s','a'} };
    t.find(SubString,n2);
    delete[] SubString;


    n2 = 2;
    SubString =  { new char[n2]{'a','a'} };
    t.find(SubString,n2);
    delete[] SubString;


    n2 = 9;
    SubString =  { new char[n2]{'b','a','n','a','a','a','a','b','a'} };
    t.find(SubString,n2);
    delete[] SubString;

    return 0;
}