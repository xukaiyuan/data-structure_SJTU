#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

#include "Alphabet.h"

class HuffmanTree {
private:
    struct node {
        Alphabet data;
        int parent;
        int left, right;
    };

    node *data;

public:
    HuffmanTree(Alphabet *alps, int n, int maximum)
    {
        int min1, min2;
        int x, y;

        data = new node [2 * n];

        for (int i = n; i < 2 * n; ++i) {
            data[i].data = alps[i - n];
            data[i].parent = data[i].left = data[i].right = 0;
        }

        for (int i = n - 1; i > 0; --i) {
            min1 = min2 = maximum;
            x = y = 0;
            for (int j = i + 1; j < 2 * n; ++j) {
                if (data[j].data.occurrence) {
                    if (!data[j].parent) {
                        if (data[j].data.occurrence < min1) {
                            min2 = min1;
                            min1 = data[j].data.occurrence;
                            y = x;
                            x = j;
                        }
                        else if (data[j].data.occurrence < min2) {
                            min2 = data[j].data.occurrence;
                            y = j;
                        }
                    }
                }
            }

            data[i].data.occurrence = min1 + min2;
            data[i].left = x;
            data[i].right = y;
            data[i].parent = 0;

            data[x].parent = data[y].parent = i;
        }

        for (int i = n; i != 2 * n; ++i) {
            int p = data[i].parent, s = i;
            int j = 0;
            while (p) {
                if (data[p].left == s) {
                    alps[i - n].code[j++] = '0';
                } else {
                    alps[i - n].code[j++] = '1';
                }

                s = p;
                p = data[p].parent;
            }
        }
    }
};

#endif // HUFFMANTREE_H_INCLUDED
