#include <iostream>
#include <fstream>
#include "AVLTree.h"

using namespace std;

int main()
{
    ifstream fin("text.in");
    Word words[500000];
    char* word = new char[30], temp = '\0';
    word[0] = '\0';
    int cnt = 0, k = 0,weights[26] = {0};;
    AVLTree<Word> tree;
    char alphabets[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    while(temp != EOF)
    {
        temp = fin.get();
        while(fin && !isalpha(temp))//escape all the non-alphabet chars.
        {
            fin.get(temp);
        }
        cnt = 0;
        while(fin && isalpha(temp))//read the word.
        {
            if(temp >= 'A' && temp <= 'Z')
            {
                temp += 32;
            }
            word[cnt++] = temp;
            ++weights[temp - 97];
            fin.get(temp);
        }
        word[cnt] = '\0';
        if(word[0] != '\0')
        {
            words[k++] = Word(word);
            tree.inserter(words[k - 1]);
        }
    }
    QuickSort(words, k);
    Word tempWord("Start");
    cout  << endl;
    cout << "The first part, sort the words." << endl << endl;
    for(int i = 0; i < k; ++i)
    {
        if(!(words[i] == tempWord))
        {
            cout << words[i] << ' ';
            tempWord = words[i];
        }
    }
    cout << endl;
    cout << endl << "Enter any key to continue." << endl;
    cin.get();
    cout << endl;
    cout << "The second part, search, insert and delete the words saved in AVL tree." << endl;
    cout << "Enter 'exit' to exit." << endl;
    cout << "Enter 'delete word' to delete word." << endl;
    cout << "Enter 'print' to print the AVL tree in inorder." << endl;
    cout << "Enter 'insert word' to insert word." << endl;
    Huffman<char> codeTree(alphabets, weights, 26);

    char command[30];
    do
    {
        char opWord[30];
        cin >> command;
        switch(command[0])
        {
        case 'i':
            cin >> opWord;
            tree.inserter(Word(opWord));
            break;
        case 'd':
            cin >> opWord;
            tree.remover(Word(opWord));
            break;
        case 'p':
            tree.inOrder();
            cout << endl;
            break;
        case 's':
            cin >> opWord;
            int times = tree.finder(opWord);
            if(times > 0)
            {
                cout << "The word " << opWord << " appears " << times << " times" << endl;
            }
            else
            {
                cout << "This word is not in the text now." << endl;
            }
        }
    }while(command[0] != 'e');

    codeTree.getCode();
    cout << endl;
    cout << "The second part is finished.Enter any key to continue." << endl;
    cin.get();
    cin.get();
    cout  << endl;
    cout << "The third part, print the Huffman codes." << endl;
    codeTree.printCode();
    fin.close();

    return 0;
}
