#include <iostream>
#include <cstring>
using namespace std;



template<typename E> class BinNode{
public:
    virtual ~BinNode(){}
    virtual E& element() = 0;
    virtual void setElement(const E&) = 0;
    virtual BinNode* left() const = 0;
    virtual BinNode* right()  const  = 0;
    virtual void setLeft(BinNode*) = 0;
    virtual void setRight(BinNode*) = 0;
    virtual bool isLeaf() = 0;
};


template<typename Key, typename E>
class BSTNode : public BinNode<E>{
private:
    Key k;
    E it;
    BSTNode *lc;
    BSTNode *rc;
public:
    BSTNode(){lc = rc = NULL;}
    BSTNode(Key K,E e,BSTNode* l = NULL, BSTNode* r = NULL){
        k = K;
        it = e;
        lc = l;
        rc = r;
    }

    ~BSTNode() {}

    E& element() {return it;}
    void setElement(const E& e){it = e;}
    Key &key(){return k;}
    void setKey(const Key& K){k = K;}

    inline BSTNode* left()  const{return lc;}
    inline BSTNode* right() const{return rc;}
    void setLeft(BinNode<E>* b) {lc = (BSTNode*) b;}
    void setRight(BinNode<E>* b) {rc = (BSTNode*) b;}



    bool isLeaf() {return (lc == NULL) && (rc == NULL);}

    BSTNode* toPos(char*pre,int st1,int en1,char*in,int st2,int en2){
        if(st2 > en2) return NULL;
        int i = st2;
        for(i=st2;i<en2&&in[i]!=pre[st1];i++);
        BSTNode<int,char>*x = new BSTNode;
        x->setElement(pre[st1]);

        x->setLeft( toPos(pre, st1+1, st1+i-st2,  in,  st2,i-1));
        x->setRight( toPos(pre, st1+1+i-st2, st1+i-st2,  in,  i+1,en2));
        return x;
    }



};

BSTNode<int,char>* findnode(BSTNode<int,char>* head,char target){


        if(head == NULL) return NULL;
        if(head->element() == target) return head;
        if(head->left()!= NULL) return findnode(head->left(),target);
        if(head->right()!= NULL) return findnode(head->right(),target);

}


int height(BSTNode<int,char>*head){
        if(head == NULL ) return 0;
        if(head->isLeaf()) return 1;
        int lheight = height(head->left());
        int rheight = height(head->right());
        if(lheight >= rheight) return lheight + 1;
        else return rheight + 1;
    }

bool findancestor(BSTNode<int,char>*head,char target){
        if(head == NULL) return false;
        if(head->element() == target) return true;
        if(findancestor(head->left(),target) || findancestor(head->right(),target)) {cout << head->element();return true;}
        return false;


    }



void postorder(BSTNode <int,char>*head)
{
    if(head == NULL)return;
    postorder(head->left());
    postorder(head->right());
    cout << head->element();
    return;
}




int main()
{
    char *pre ="YALBECDWXM";
    char *in = "BLEACWXDYM";
    char f;
    int judge = 0;
    BSTNode<int,char> x;

    postorder(x.toPos(pre,0,9,in,0,9));
    cout <<endl;
    cout << "the height is:" <<height(x.toPos(pre,0,9,in,0,9));

    cout << endl;
    cout << "please input the node you want to find:";
    cin >> f;

    for(int i = 0;i < strlen(pre);i++){
        if (pre[i] == f) {judge = 1;break;}
    }
    if(judge == 0) cout << "there are no this value you have input";
    else {  cout << "the ancestors of the input node is:";
            findancestor(x.toPos(pre,0,9,in,0,9),f);
            cout << endl;
            cout << "the descends of the input node is:";
            postorder(findnode(x.toPos(pre,0,9,in,0,9),f));

    }

}



