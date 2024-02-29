#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;



class HangmanGame {
private:
    int attempts; // попытки 
    string targetWord; // слово
    string currentGuess; // текущее состояние угадывания 
    string* words; // массив слов из файла
    int numWords; //  количество слов из файла

    // проверяе символ =пробел ?
    bool isWhitespace(char c) {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    // подсчитывает количество слов в файле
    int countWords(const char* filename) {
        ifstream file(filename);
        string line;
        int n = 0;

        if (file.is_open()) {
            while (getline(file, line)) {
                bool inWord = false;

                for (int i = 0; i < line.length(); ++i) {
                    char c = line[i];

                    if (isWhitespace(c)) {
                        inWord = false;
                    }
                    else {
                        if (!inWord) {
                            n++;
                            inWord = true;
                        }
                    }
                }
            }

            file.close();
            return n;
        }
        else {
            cout << "Failed to open file: " << filename << endl;
            return 0;
        }
    }

    // загружает слова из файла в массив
    void loadWords(const char* filename) {
        ifstream wordsFile(filename);

        if (wordsFile.is_open()) {
            int totalWords = countWords(filename);
            words = new string[totalWords];
            string word;

            while (getline(wordsFile, word) && numWords < totalWords) {
                words[numWords] = word;
                ++numWords;
            }

            wordsFile.close();
        }
        else {
            cout << "Failed to open file: " << filename << endl;
        }
    }

    // выбирает случайное слово из массива 
    void chooseRandomWord() {
        srand(time(nullptr));
        int randomIndex = rand() % numWords;
        targetWord = words[randomIndex];
    }

    // инициализирует текущее состояние угадывания супер слова
    void initializeCurrentGuess() {
        currentGuess = string(targetWord.length(), '_');
    }

    // проверяет,   угаданная буква правильная или не
    bool isCorrectGuess(char guess) const {
        for (int i = 0; i < targetWord.length(); ++i) {
            if (targetWord[i] == guess) {
                return true;
            }
        }
        return false;
    }

    // обновляет текущее состояние угадывания слова после правильной попытки
    void updateCurrentGuess(char guess) {
        for (int i = 0; i < targetWord.length(); ++i) {
            if (targetWord[i] == guess) {
                currentGuess[i] = guess;
            }
        }
    }

  
    int maxAttempts() const {
        return 6;
    }

public:
    // загружает слова из файла, выбирает случайное супер слово и инициализирует текущее состояние угадывания
    HangmanGame(const char* filename) : attempts(0), words(nullptr), numWords(0) {
        loadWords(filename);
        chooseRandomWord();
        initializeCurrentGuess();
    }

  
    ~HangmanGame() {
        delete[] words;
    }

  
    void play() {
        while (!isGameOver()) {
            displayGameState();
            char guess;
            cout << "Enter your guess: ";
            cin >> guess;
            processGuess(guess);
        }

        displayGameResult();
    }

 
    void displayGameState() const {
        cout << "Current word: " << currentGuess << endl;
        cout << "Attempts left: " << maxAttempts() - attempts << endl;
    }

    // обрабатывает попытку угадывания буковки
    void processGuess(char guess) {
        if (isCorrectGuess(guess)) {
            updateCurrentGuess(guess);
        }
        else {
            cout << "Incorrect guess. Try again." << endl;
            attempts++;
            displayHangman(attempts);
        }
    }

   
    bool isGameOver() const {
        return attempts >= maxAttempts() || currentGuess == targetWord;
    }

  
    void displayGameResult() const {
        if (currentGuess == targetWord) {
            cout << "Congratulations! You guessed the word: " << targetWord << endl;
        }
        else {
            cout << "Sorry, you ran out of attempts. The word was: " << targetWord << endl;
        }

        cout << "Total attempts: " << attempts << endl;

        cout << "Your guesses: ";
        for (int i = 0; i < targetWord.length(); ++i) {
            cout << currentGuess[i] << " ";
        }
        cout << endl;
    }


    void displayHangman(int attempts) const {
        switch (attempts) {
        case 1:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            break;
        case 2:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |     |" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            break;
        case 3:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |    /|" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            break;
        case 4:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |    /|\\" << endl;
            cout << " |" << endl;
            cout << " |" << endl;
            break;
        case 5:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |    /|\\" << endl;
            cout << " |    /" << endl;
            cout << " |" << endl;
            break;
        case 6:
            cout << " _______" << endl;
            cout << " |     |" << endl;
            cout << " |     O" << endl;
            cout << " |    /|\\" << endl;
            cout << " |    / \\" << endl;
            cout << " |" << endl;
            break;
        }
    }
};
