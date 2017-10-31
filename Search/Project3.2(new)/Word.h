#ifndef WORD_H_INCLUDED
#define WORD_H_INCLUDED

#include <iostream>
#include <cstring>
using namespace std;

class Word {                                                //The class used to represent a word.
    friend ostream &operator<< (ostream &os, const Word &x)
    {
        os << x.data;
        return os;
    }

    friend bool operator< (const Word &a, const Word &b)
    {
        return strcmp(a.data, b.data) < 0;
    }

    friend bool operator== (const Word &a, const Word &b)
    {
        return strcmp(a.data, b.data) == 0;
    }

    friend bool operator> (const Word &a, const Word &b)
    {
        return strcmp(a.data, b.data) > 0;
    }
private:
    char *data;
    unsigned length;
public:
    Word() :length(-1)
    {
        data = new char[1];
    }

    Word(const char *str) :length(strlen(str))
    {
        data = new char [length + 1];
        strcpy(data, str);
    }

    Word& operator= (const Word &x)
    {
        if (this == &x)
            return *this;

        delete [] data;

        length = x.length;
        data = new char [length + 1];
        strcpy(data, x.data);
    }

    Word(const Word &x) :length(x.length)
    {
        data = new char [length + 1];
        strcpy(data, x.data);
    }

    ~Word()
    {
        delete [] data;
    }
};

#endif // WORD_H_INCLUDED
