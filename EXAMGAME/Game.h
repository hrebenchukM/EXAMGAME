#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;



class Game {
protected:

    int attempts;
    string targetWord;
    string currentGuess;

public:
    Game() : attempts(0) {}

    virtual ~Game() {}

    virtual void play() = 0;

    virtual void displayGameState() const = 0;

    virtual void processGuess(char guess) = 0;

    virtual bool isGameOver() const = 0;

    virtual void displayGameResult() const = 0;

    virtual void displayHangman(int attempts) const = 0;
};