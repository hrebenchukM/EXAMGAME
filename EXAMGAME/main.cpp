#include <iostream>
#include <fstream>
#include <string>
#include "HangmanGame.h"
using namespace std;





int main() {
    HangmanGame game("words.txt");
    game.play();

    return 0;
}
