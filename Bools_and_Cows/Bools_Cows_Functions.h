// быки и коровы Корчагин Евнений 414

#pragma once


#include <string>
#include<vector>


using std::string;
using std::vector;


void generateCombinations(string prefix, string available, vector<string>& combinations);

vector<string> filterCombinations(const vector<string>& possibleCombinations, const string& guess, int bulls, int cows);

string generateNumber();

std::pair<int, int> getBullsAndCows(const string& secret, const string& guess);

void computerGuess(const string& secretNumber);

void startGame();

