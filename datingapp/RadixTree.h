#ifndef RADIXTREE_H
#define RADIXTREE_H
#include<string>
using namespace std;
const int numOfletter = 128;

template <typename ValueType>
class RadixTree {
public:
     RadixTree();
     ~RadixTree();
     void insert(string key, const ValueType& value);
     ValueType* search(string key) const;
private:
    struct Node
    {
        string word;
        Node* child[numOfletter];
        Node* parent=nullptr;
        bool endOfword=false;
        ValueType* paired=nullptr;
    };
    Node root;
    
    void deleteNode(Node* nodeTodelete)
    {
        if(!nodeTodelete)
            return;
        for(int i = 1;i < numOfletter; i++)
        {
            if(nodeTodelete -> child[i])
                deleteNode(nodeTodelete -> child[i]);
        }
        if(nodeTodelete -> paired != nullptr)
            delete nodeTodelete -> paired;
        delete nodeTodelete;
    }
    
    Node* add(string added, Node* parentnode)
    {
    Node* newnode = new Node;
    newnode -> word = added;
    for(int i = 0;i < numOfletter; i++)
        newnode -> child[i]=nullptr;
    newnode -> parent = parentnode;
    return newnode;
    }
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
{
    root.word="";
    for(int i = 0; i < numOfletter; i++)
        root.child[i]=nullptr;
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
    for(int i = 0; i < numOfletter; i++){
        deleteNode(root.child[i]);
    }
}

template <typename ValueType>
void RadixTree<ValueType>::insert(string key, const ValueType& value)
{
    if(root.child[key[0]]==nullptr)
    {
        Node* addednode = add(key, &root);
        addednode -> endOfword = true;
        addednode -> paired = new ValueType(value);
        root.child[key[0]] = addednode;
        return;
    }
    Node* cur = root.child[key[0]];
    int count1 = 0;
    while(count1 < key.length())
    {
        string curword = cur -> word;
        int count2 = 0;
        while(count1 < key.length() && count2 < curword.length())
        {
            if(key[count1] != curword[count2])
            {
                string finished = curword.substr(0,count2);
                string unfinished = curword.substr(count2,-1);
                cur -> word = finished;
                Node* oldword = add(unfinished, cur);
                Node* addword = add(key.substr(count1, -1), cur);
                for(int i = 0; i < numOfletter; i++)
                {
                    oldword -> child[i] = cur -> child[i];
                    cur -> child[i] = nullptr;
                }
                oldword -> endOfword = cur-> endOfword;
                cur -> endOfword = false;
                oldword -> paired = cur -> paired;
                cur -> paired = nullptr;
                cur -> child[key[count1]] = addword;
                cur -> child[unfinished[0]] = oldword;
                break;
            }
            count1++;
            count2++;
        }
        if(count1 == key.length() && count2 == curword.length())
        {
            cur -> endOfword = true;
            cur -> paired = new ValueType(value);
            return;
        }
        else if (count1 == key.length())
        {
            string finished = curword.substr(0,count2);
            string unfinished = curword.substr(count2,-1);
            Node* newnode = add(unfinished,cur);
            newnode -> paired = cur -> paired;
            newnode -> endOfword = cur -> endOfword;
            for(int i=0;i < numOfletter; i++)
            {
                newnode -> child[i] = cur -> child[i];
                cur -> child[i]=nullptr;
            }
            cur -> child[unfinished[0]] = newnode;
            cur -> endOfword = true;
            cur -> paired = new ValueType(value);
            cur -> word = finished;
            return;
        }
        else
        {
            if(cur -> child[key[count1]] == nullptr)
            {
                Node* newnode = add(key.substr(count1, -1), cur);
                cur -> child[key[count1]] = newnode;
            }
            cur = cur -> child[key[count1]];
        }
    }
}

template<typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    int count1 = 0;
    if(root.child[key[0]]==nullptr)
        return nullptr;
    Node* cur = root.child[key[0]];
    while(count1 < key.length())
    {
        string curword = cur -> word;
        int count2 = 0;
        while(count1 < key.length() && count2 < curword.length())
        {
            if(curword[count2] != key[count1])
                return nullptr;
            count1++;
            count2++;
        }
        if(count1 == key.length() && count2 == curword.length())
        {
            if(cur -> endOfword)
                return cur -> paired;
            else
                return nullptr;
        }
        else if (count1 == key.length())
        {
            return nullptr;
        }
        else
        {
            if(cur -> child[key[count1]] == nullptr)
                return nullptr;
            else
                cur = cur -> child[key[count1]];
        }
    }
    return nullptr;
}
#endif /* RadixTree_h */
