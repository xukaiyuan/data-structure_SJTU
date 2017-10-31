#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "Word.h"

class AVLTree {                                             //AVl tree.
private:
    struct node {
        Word data;

        node *left, *right;
        int height;

        node(const Word &x, node *l = NULL, node *r = NULL, int h = 0) :data(x), left(l), right(r), height(h) {}
        node() :left(NULL), right(NULL) {}

        ~node() {}
    };

    node *root;

public:
    AVLTree() :root(NULL) {}

    void insert(const Word &x)
    {
        insertHelper(root, x);
    }

    bool find(const Word &x)
    {
        return findHelper(root, x);
    }

    void remove(const Word &x)
    {
        removeHelper(root, x);
    }

    void traverse(ostream &os)
    {
        traverseHelper(root, os);
        os << endl;
    }

    ~AVLTree()
    {
        clearHelper(root);
    }

private:
    void clearHelper(node *p)
    {
        if (p) {
            clearHelper(p -> left);
            clearHelper(p -> right);
            delete p;
        }
    }

    bool findHelper(node *p, const Word &x)
    {
        if (p) {
            if (x < p -> data)
                return findHelper(p -> left, x);
            if (x > p -> data)
                return findHelper(p -> right, x);
            return true;
        }

        return false;
    }

    int height(node *t)
    {
        return t ? t -> height : -1;
    }

    int maxHeight(node *&a, node *&b)
    {
        return (height(a) >= height(b)) ? height(a) : height(b);
    }

    void LL(node *&t)
    {
        node *tmp = t -> left;
        t -> left = tmp -> right;
        tmp -> right = t;
        t -> height = maxHeight(t -> left, t -> right) + 1;
        tmp -> height = maxHeight(tmp -> left, t) + 1;
        t = tmp;
    }

    void RR(node *&t)
    {
        node *tmp = t -> right;
        t -> right = tmp -> left;
        tmp -> left = t;
        t -> height = maxHeight(t -> left, t -> right) + 1;
        tmp -> height = maxHeight(t, tmp -> right) + 1;
        t = tmp;
    }

    void LR(node *&t)
    {
        RR(t -> left);
        LL(t);
    }

    void RL(node *&t)
    {
        LL(t -> right);
        RR(t);
    }

    void insertHelper(node *&t, const Word &x)
    {
        if (!t) {
            t = new node(x);
        }
        else if (x < t -> data) {
            insertHelper(t -> left, x);
            if (height(t -> left) - height(t -> right) == 2) {
                if (x < t -> left -> data) {
                    LL(t);
                } else {
                    LR(t);
                }
            }
        }
        else if (x > t -> data) {
            insertHelper(t -> right, x);
            if (height(t -> right) - height(t -> left) == 2) {
                if (x > t -> right -> data) {
                    RR(t);
                } else {
                    RL(t);
                }
            }
        }

        t -> height = maxHeight(t -> left, t -> right) + 1;

    }

    bool removeHelper(node *&t, const Word &x)
    {
        bool stop = false, inLeft = false;

        if (!t) return true;

        if (x < t -> data) {
            stop = removeHelper(t -> left, x);
            inLeft = true;
        }
        else if (x > t -> data) {
            stop = removeHelper(t -> right, x);
            inLeft = false;
        }
        else if (t -> left && t -> right) {
            node *tmp = t -> right;
            while (tmp -> left) {
                t -> data = tmp -> data;
                tmp = tmp -> left;
            }

            stop = removeHelper(t -> right, t -> data);
            inLeft = false;
        }
        else {
            node *tmp = t;
            t = (t -> left) ? t -> left : t -> right;
            delete tmp;
            return false;
        }

        t -> height = maxHeight(t -> left, t -> right) + 1;
        if (stop) return true;
        int bf;

        if (inLeft) {
            bf = height(t -> left) - height(t -> right) + 1;
            if (bf == -1) {
                switch (height(t -> right -> left) - height(t -> right -> right)) {
                    case 0:
                        RR(t);
                        return true;
                    case 1:
                        RL(t);
                        return false;
                    case -1:
                        RR(t);
                        return false;
                }
            }
            else return 1 - bf;
        } else {
            bf = height(t -> left) - height(t -> right) - 1;
            if (bf == 1) {
                switch (height(t -> left -> left) - height(t -> left -> right)) {
                    case 0:
                        LL(t);
                        return true;
                    case 1:
                        LL(t);
                        return false;
                    case -1:
                        LR(t);
                        return false;
                }
            }
            else return 1 + bf;
        }

    }

    void traverseHelper(node *p, ostream &os)
    {
        if (p) {
            traverseHelper(p -> left, os);
            os << p -> data << endl;
            traverseHelper(p -> right, os);
        }
    }
};

#endif // AVLTREE_H_INCLUDED
