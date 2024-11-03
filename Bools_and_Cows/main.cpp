
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bools_Cows_Functions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0))); 
    startGame();
    return 0;
}
