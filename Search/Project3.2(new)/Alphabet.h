#ifndef ALPHABET_H_INCLUDED
#define ALPHABET_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

struct Alphabet {                                           //One letter.
    friend ostream &operator<< (ostream &os, const Alphabet &x)
    {
        os << x.data << ":    " << x.occurrence << "\t/  " << x.totalOccurrence << "\t";
        int j = 29;
        for (; j >= 0; --j) {
            if (x.code[j]) break;
        }

        for (; j >= 0; --j) {
            os << x.code[j];
        }

        return os;
    }
    char data;
    int occurrence;
    char code[30];

    Alphabet(char ch = '\0', int i = 0) :data(ch), occurrence(i)
    {
        for (int i = 0; i != 30; ++i) {
            code[i] = '\0';
        }
    }

    static int totalOccurrence;
};

int Alphabet::totalOccurrence = 0;                          //The total occurrences of the letters.

#endif // ALPHABET_H_INCLUDED
