#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
#include <iostream>

using namespace std;

template <typename E>
void Swap(E arr[], int i, int j)
{
    E temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template <typename E>
void InsertionSort(E arr[], int n)
{
    for(int i = 1; i < n; ++i)
    {
        for(int j = i; j > 0 && arr[j] < arr[j - 1]; --j)
        {
            Swap(arr, j, j - 1);
        }
    }
}

template <typename E>
void QuickSortHelp(E arr[], int low, int high);

template <typename E>
int divide(E arr[], int low, int high);

template <typename E>
void QuickSort(E arr[], int n)
{
    QuickSortHelp(arr, 0, n - 1);
}

template <typename E>
void QuickSortHelp(E arr[], int low, int high)
{
    if(high <= low)
    {
        return;
    }
    Swap(arr, (low + high) / 2, high);
    int mid = divide(arr, low - 1, high);
    Swap(arr, mid, high);
    QuickSortHelp(arr, low, mid - 1);
    QuickSortHelp(arr, mid + 1, high);
}

template <typename E>
int divide(E arr[], int low, int high)
{
    E temp = arr[high];
    do
    {
        while(arr[++low] < temp);
        while(low < high && temp < arr[--high]);
        Swap(arr, low, high);
    }while(low < high);
    return low;
}

class Word
{
    friend ostream& operator<<(ostream& os, const Word& w);
private:
    char* word;
public:
    Word(const char* w = NULL)
    {
        if(w)
        {
            int i;
            for(i = 0; w[i] != '\0'; ++i);
            word = new char[i + 1];
            for(i = 0; w[i] != '\0'; ++i)
            {
                word[i] = w[i];
            }
            word[i] = '\0';
        }
        else
        {
            word = NULL;
        }
    }

    Word(const Word& w)
    {
        int i = -1;
        while(w.word[++i] != '\0');
        word = new char[i + 1];
        for(int j = 0; j <= i; ++j)
        {
            word[j] = w.word[j];
        }
    }

    ~Word()
    {
        if(word)
        {
            delete [] word;
        }
    }

    Word& operator=(const Word& w)
    {
        int i = -1;
        while(w.word[++i] != '\0');
        word = new char[i + 1];
        for(int j = 0; j <= i; ++j)
        {
            word[j] = w.word[j];
        }
        return *this;
    }

    bool operator<(const Word& w) const
    {
        int i = 0;
        while(word[i] == w.word[i] && word[i] != '\0' && w.word[i] != '\0')
        {
            ++i;
        }
        if((w.word[i] != '\0' && word[i] == '\0') || (word[i] != '\0' && w.word[i] != '\0' && word[i] < w.word[i]))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator==(const Word& w) const
    {
        int i = 0;
        while(word[i] != '\0' && w.word[i] != '\0')
        {
            if(word[i] != w.word[i])
            {
                return false;
            }
            ++i;
        }
        if(word[i] == '\0' && w.word[i] == '\0')
        {
            return true;
        }
        return false;
    }
};

ostream& operator<<(ostream& os, const Word& w)
{
    os << w.word;
    return os;
}

template <typename E>
class AVLTree;

template <typename E>
class AVLNode
{
    friend class AVLTree<E>;
private:
    E element;
    AVLNode* left;
    AVLNode* right;
    int height;
    int frequency;
public:
    AVLNode(const E e, AVLNode* le = NULL, AVLNode* ri = NULL, int h = 0) : element(e), left(le), right(ri), height(h), frequency(1)
    {

    }

    ~AVLNode()
    {

    }
};

template <typename E>
class AVLTree
{
private:
    AVLNode<E>* root;

    void clearHelp(AVLNode<E>* root)
    {
        if(!root)
        {
            return;
        }
        clearHelp(root -> left);
        clearHelp(root -> right);
        delete root;
    }

    int findHelp(const E& e, AVLNode<E>* root)
    {
        if(!root)
        {
            return -1;
        }
        if(root -> element == e)
        {
            return root -> frequency;
        }
        if(e < root -> element)
        {
            return findHelp(e, root -> left);
        }
        else
        {
            return findHelp(e, root -> right);
        }
    }

    AVLNode<E>* insertHelp(const E& e, AVLNode<E>* root)
    {
        if(!root)
        {
            return new AVLNode<E>(e);
        }
        if(root -> element == e)
        {
            ++root -> frequency;
            return root;
        }
        if(e < root -> element)
        {
            root -> left = insertHelp(e, root -> left);
            if(getHeight(root -> left) - getHeight(root -> right) == 2)
            {
                if(e < root -> left -> element)
                {
                    root = LLSpin(root);
                }
                else
                {
                    root = LRSpin(root);
                }
            }
        }
        else
        {
            root -> right = insertHelp(e, root -> right);
            if(getHeight(root -> right) - getHeight(root -> left) == 2)
            {
                if(root -> right -> element < e)
                {
                    root = RRSpin(root);
                }
                else
                {
                    root = RLSpin(root);
                }
            }
        }
        int leftHeight = getHeight(root -> left), rightHeight = getHeight(root -> right);
        root -> height = (leftHeight + 1 > rightHeight + 1 ? leftHeight + 1 : rightHeight + 1);
        return root;
    }

    bool removeHelp(const E& e, AVLNode<E>* &root)
    {
        bool stop = false;
        int subTree;
        int leftChildHeight, rightChildHeight;


        if(!root)
        {
            return true;
        }

        if(e < root -> element)
        {
            stop = removeHelp(e, root -> left);
            subTree = 1;
        }
        else
        {
            if(root -> element < e)
            {
                stop = removeHelp(e, root -> right);
                subTree = 2;
            }
            else
            {
                if(root -> left && root -> right)
                {
                    AVLNode<E>* temp = root -> right;
                    while(temp -> left)
                    {
                        temp = temp -> left;
                    }
                    root -> element = temp -> element;
                    stop = removeHelp(temp -> element, root -> right);
                    subTree = 2;
                }
                else
                {
                    AVLNode<E>* temp = root;
                    if(root -> left)
                    {
                        root = root -> left;
                    }
                    else
                    {
                        root = root -> right;
                    }
                    delete temp;
                    return false;
                }
            }
        }

        leftChildHeight = getHeight(root -> left);
        rightChildHeight = getHeight(root -> right);
        root -> height = (leftChildHeight > rightChildHeight ? leftChildHeight + 1 : rightChildHeight + 1);

        if(stop)
        {
            return true;
        }

        int balance;
        switch(subTree)
        {
        case 1:
            balance = getHeight(root -> left) - getHeight(root -> right) + 1;
            if(balance == 0)
            {
                return true;
            }
            if(balance == 1)
            {
                return false;
            }
            if(balance == -1)
            {
                int balanceRight = getHeight(root -> right -> left) - getHeight(root -> right -> right);
                switch(balanceRight)
                {
                case 0:
                    root = RRSpin(root);
                    return true;
                case -1:
                    root = RRSpin(root);
                    return false;
                default:
                    root = RLSpin(root);
                    return false;
                }
            }
            break;
        case 2:
            balance = getHeight(root -> left) - getHeight(root -> right) - 1;
            if(balance == 0)
            {
                return true;
            }
            if(balance == -1)
            {
                return false;
            }
            if(balance == 1)
            {
                int balanceLeft = getHeight(root -> left -> left) - getHeight(root -> left -> right);
                switch(balanceLeft)
                {
                case 0:
                    root = LLSpin(root);
                    return true;
                case 1:
                    root = LLSpin(root);
                    return false;
                default:
                    root = LRSpin(root);
                    return false;
                }
            }
        }
        return true;
    }

    AVLNode<E>* LLSpin(AVLNode<E>* root)
    {
        AVLNode<E>* temp = root -> left;
        root -> left = temp -> right;
        temp -> right = root;
        int rootLeftHeight = getHeight(root -> left), rootRightHeight = getHeight(root -> right), tempLeftHeight = getHeight(temp -> left);
        root -> height = (rootLeftHeight + 1 > rootRightHeight + 1 ? rootLeftHeight + 1 : rootRightHeight + 1);
        temp -> height = (tempLeftHeight + 1 > root -> height + 1 ? tempLeftHeight + 1 : root -> height + 1);
        return temp;
    }

    AVLNode<E>* RRSpin(AVLNode<E>* root)
    {
        AVLNode<E>* temp = root -> right;
        root -> right = temp -> left;
        temp -> left = root;
        int rootLeftHeight = getHeight(root -> left), rootRightHeight = getHeight(root -> right), tempRightHeight = getHeight(temp -> right);
        root -> height = (rootLeftHeight + 1 > rootRightHeight + 1 ? rootLeftHeight + 1 : rootRightHeight + 1);
        temp -> height = (tempRightHeight + 1 > root -> height + 1 ? tempRightHeight + 1 : root -> height + 1);
        return temp;
    }

    AVLNode<E>* LRSpin(AVLNode<E>* root)
    {
        root -> left = RRSpin(root -> left);
        root = LLSpin(root);
        return root;
    }

    AVLNode<E>* RLSpin(AVLNode<E>* root)
    {
        root -> right = LLSpin(root -> right);
        root = RRSpin(root);
        return root;
    }

    int getHeight(AVLNode<E>* root)
    {
        if(!root)
        {
            return -1;
        }
        return (root -> height);
    }

    void preOrderHelp(AVLNode<E>* root)
    {
        if(!root)
        {
            return;
        }
        cout << root -> element << ' ';
        preOrderHelp(root -> left);
        preOrderHelp(root -> right);
    }

    void inOrderHelp(AVLNode<E>* root)
    {
        if(!root)
        {
            return;
        }
        inOrderHelp(root -> left);
        cout << root -> element << ' ';
        inOrderHelp(root -> right);
    }
public:
    AVLTree()
    {
        root = NULL;
    }

    ~AVLTree()
    {
        clearer();
    }

    void clearer()
    {
        clearHelp(root);
    }

    int finder(const E& e)
    {
        return findHelp(e, root);
    }

    void inserter(const E& e)
    {
        root = insertHelp(e, root);
    }

    void remover(const E& e)
    {
        removeHelp(e, root);
    }

    void preOrder()
    {
        preOrderHelp(root);
    }

    void inOrder()
    {
        inOrderHelp(root);
    }
};

template <typename E>
class Huffman;
template <typename E>
class Node
{
    friend class Huffman<E>;
private:
    int parent;
    int left;
    int right;
    E element;
    int weight;
};

template <typename E>
class HuffCode
{
    friend class Huffman<E>;
private:
    string code;
    E element;
};

template <typename E>
class Huffman
{
private:
    Node<E>* storage;
    int charNum;
    HuffCode<E>* codes;
    int treeWeight[26];
    int totalAlphabet;
public:
    Huffman(const E* elements, const int* weights, int si)
    {
        totalAlphabet = 0;
        int l1 = si, l2 = si;
        charNum = si;
        storage = new Node<E>[2 * si];
        codes = new HuffCode<E>[si];
        for(int i = 0; i < charNum; ++i)
        {
            treeWeight[i] = weights[i];
            totalAlphabet += weights[i];
        }
        for(int i = 0; i < si; ++i)
        {
            storage[si + i].parent = 0;
            storage[si + i].left = 0;
            storage[si + i].right = 0;
            storage[si + i].element = elements[i];
            storage[si + i].weight = weights[i];
        }
        for(int i = 0; i < si - 1; ++i)
        {
            l1 = si - i;
            while(storage[l1].parent)
            {
                ++l1;
            }
            l2 = l1 + 1;
            while(storage[l2].parent)
            {
                ++l2;
            }
            for(int j = l2 + 1; j < 2 * si; ++j)
            {
                if((storage[j].weight < storage[l1].weight || storage[j].weight < storage[l2].weight) && storage[j].parent == 0)
                {
                    if(storage[l1].weight < storage[l2].weight)
                    {
                        l2 = j;
                    }
                    else
                    {
                        l1 = j;
                    }
                }
            }
            storage[l1].parent = si - i - 1;
            storage[l2].parent = si - i - 1;
            storage[si - i - 1].parent = 0;
            storage[si - i - 1].left = l1;
            storage[si - i - 1].right = l2;
            storage[si - i - 1].weight = storage[l1].weight + storage[l2].weight;
        }
    }

    void getCode()
    {
        int p;
        for(int i = charNum; i < 2 * charNum; ++i)
        {
            p = i;
            codes[i - charNum].code = "";
            codes[i - charNum].element = storage[i].element;
            while(storage[p].parent)
            {
                if(storage[storage[p].parent].right == p)
                {
                    codes[i - charNum].code = '1' + codes[i - charNum].code;
                }
                else
                {
                    codes[i - charNum].code = '0' + codes[i - charNum].code;
                }
                p = storage[p].parent;
            }
        }
    }

    void printCode()
    {
        for(int i = 0; i < charNum; ++i)
        {
            cout << codes[i].element << ' ' << double(treeWeight[i]) / totalAlphabet << ' ' << codes[i].code << endl;;
        }
    }
};




#endif
