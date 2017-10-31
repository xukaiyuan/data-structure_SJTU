#include "AVLTree.h"
#include "HuffmanTree.h"
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("data.in");
    ofstream fout("data.out");
    AVLTree tree;
    char str[100], ch;
    Alphabet::totalOccurrence = 0;
    Alphabet alps[26];
    for (int i = 0; i != 26; ++i) {
        alps[i].data = 'A' + i;
    }

    while (fin) {                                           //Input process.
        int i = 0;
        while ( (ch = fin.get()) != EOF ) {
            if (ch >= 'A' && ch <= 'Z') {
                ++alps[ch - 'A'].occurrence;
            } else if (ch >= 'a' && ch <= 'z') {
                ++alps[ch - 'a'].occurrence;
            } else break;

            str[i++] = ch;
        }

        str[i] = '\0';

        if (str[0]) {                                       //Insert into the tree.
            Word word(str);
            tree.insert(word);
        }
    }

    for (int i = 0; i != 26; ++i) {
        Alphabet::totalOccurrence += alps[i].occurrence;
    }

    HuffmanTree hfTree(alps, 26, Alphabet::totalOccurrence);        //Calculate the codes for each letter.

    for (int i = 0; i != 26; ++i) {
        if (alps[i].occurrence)
            fout << alps[i] << endl;
    }

    //tree.traverse(fout);

    tree.remove(Word("Why"));                                       //Remove from the tree.
    tree.remove(Word("dear"));
    tree.insert(Word("MATLAB"));                                    //Insert into the tree.
    fout << endl << "\"through\" in the tree? " << (tree.find(Word("through")) ? "Yes" : "No") << endl;     //Search in the tree.
    //tree.traverse(fout);

    return 0;
}
