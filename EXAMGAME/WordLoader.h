#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class WordLoader {
protected:
    string* words;
    int numWords;

public:
    WordLoader() : words(nullptr), numWords(0) {}

    virtual ~WordLoader() {
        delete[] words;
    }

    virtual void loadWords(const char* filename) = 0;

    int getNumWords() const {
        return numWords;
    }

    string* getWords() const {
        return words;
    }
};
