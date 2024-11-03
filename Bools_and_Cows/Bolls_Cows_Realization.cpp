
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Bools_Cows_Functions.h"
#include <algorithm>
#include <set>
#include <string>


using std::string;
using std::vector;
using std::pair;
using std::min;
using std::cout;
using std::endl;
using std::cin;


// ������� ���������� ��� ��������� ���������� ����� ��� ����

void generateCombinations(string prefix, string available, vector<string>& combinations) {
    if (prefix.length() == 4) {
        combinations.push_back(prefix);
        return;
    }
    for (int i = 0; i < available.length(); i++) {
        generateCombinations(prefix + available[i], available.substr(0, i) + available.substr(i + 1), combinations);
    }
}

// ������� ������� ������� ��������� ���������� ��� ������ �� ������ ���������� ����� � �����

vector<string> filterCombinations(const vector<string>& possibleCombinations, const string& guess, int bulls, int cows) {
    vector<string> filtered;
    for (const string& combo : possibleCombinations) {
        if (getBullsAndCows(guess, combo) == std::make_pair(bulls, cows)) {
            filtered.push_back(combo);
        }
    }
    return filtered;
}

// ������� ����� ���������� �� �������� �������, �������� ��������� ��� ���������� � �������� ������: ���� �� �������

void computerGuess(const string& secret) {
    string available = "0123456789";
    vector<string> possibleCombinations;
    generateCombinations("", available, possibleCombinations);
    int attempts = 0;

    while (!possibleCombinations.empty()) {
        string guess = possibleCombinations[possibleCombinations.size() / 2]; 
        attempts++;
        cout << "��������� ������������: " << guess << endl;

        pair<int, int>b_k = getBullsAndCows(secret, guess);
        int bulls = b_k.first;
        int cows = b_k.second;
        if (bulls == 4) { 
            cout << "��������� ������ ����� " << guess << " �� " << attempts << " �������!" << endl;
            break;
        }

        possibleCombinations = filterCombinations(possibleCombinations, guess, bulls, cows);
    }
}

//��� ������� ������ ���������� ��������� ���������� �����

string generateNumber() {
    string number;
    vector<bool> digits(10, false); 

    while (number.size() < 4) {
        char digit = '0' + rand() % 10;
        if (!digits[digit - '0'] && (number.empty() || digit != '0')) {
            number += digit;
            digits[digit - '0'] = true; 
        }
    }
    return number;
}

// ��������� ����� � �����

pair<int, int> getBullsAndCows(const string& secret, const string& guess) {
    int bulls = 0;
    int cows = 0;
    for (int i = 0; i < 4; ++i) {
        if (secret[i] == guess[i]) {
            bulls++;
        }
    }
    for (int i = 0; i < 4; i++) 
    {
        if (secret.find(guess[i]) != string::npos)
        {
            cows++;
            
        }
    }
    return { bulls,cows-bulls };
    
}

// ��������� ���������� ���������� �����

string checkNumber()
{
    string secretNumber;
    cout << "������� �������������� ����� (����� �� ����� �����������): ";
    cin >> secretNumber;

    while (secretNumber.length() != 4 || !isdigit(secretNumber[0]) ||
        (secretNumber[0] == '0') ||
        (secretNumber[1] == secretNumber[0]) ||
        (secretNumber[2] == secretNumber[0]) ||
        (secretNumber[3] == secretNumber[0]) ||
        (secretNumber[2] == secretNumber[1]) ||
        (secretNumber[3] == secretNumber[1]) ||
        (secretNumber[3] == secretNumber[2])) {
        cout << "�������� ����. ����������, ������� �������������� ����� (����� �� ����� �����������): ";
        cin >> secretNumber;
    }
    return secretNumber;
}

// ��������� ���� 

void startGame() {
    cout << "����� ���������� � ���� '���� � ������'!" << endl;
    start:
    cout << "�������� ����� ����:" << endl;
    cout << "1. ����� ���������� �����, ��������� ���������." << endl;
    cout << "2. ��������� ���������� �����, ����� ���������." << endl;
    cout << "3. �����" << endl;

    int mode;
    cin >> mode;

    if (mode == 1) {
        
        string  secretNumber=checkNumber();
        computerGuess(secretNumber);
    }
    else if (mode == 2) {
        string comp_number=generateNumber();
        int f = 1;
        int attempts = 0;
        while (f == 1) 
        {
            attempts++;
            string person_number = checkNumber();
            pair<int, int>b_k = getBullsAndCows(comp_number, person_number);
            cout << person_number << endl;
            cout << b_k.first << "bulls " << b_k.second << "cows" << endl;
            if (b_k.first == 4)
            {
                cout << "you win with:" <<attempts<<" attempts"<<endl;
                f = 0;
            }
        }


    }
    else if (mode == 3)
    {
        cout << "�� ��������� ����.�� ��������!";
    }
    else  {
        cout << "�������� ����� ������." << endl;
        goto start;
    }
}
