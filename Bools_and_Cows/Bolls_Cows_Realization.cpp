
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


// Функция генерирует все возможные комбинации чисел для игры

void generateCombinations(string prefix, string available, vector<string>& combinations) {
    if (prefix.length() == 4) {
        combinations.push_back(prefix);
        return;
    }
    for (int i = 0; i < available.length(); i++) {
        generateCombinations(prefix + available[i], available.substr(0, i) + available.substr(i + 1), combinations);
    }
}

// функция удаляет вектора возможных комбинаций все лишние на основе количества быков и коров

vector<string> filterCombinations(const vector<string>& possibleCombinations, const string& guess, int bulls, int cows) {
    vector<string> filtered;
    for (const string& combo : possibleCombinations) {
        if (getBullsAndCows(guess, combo) == std::make_pair(bulls, cows)) {
            filtered.push_back(combo);
        }
    }
    return filtered;
}

// функция берет комбинацию по середине вектора, получает подсказки для фильтрации и вызывает фильтр: пока не угадает

void computerGuess(const string& secret) {
    string available = "0123456789";
    vector<string> possibleCombinations;
    generateCombinations("", available, possibleCombinations);
    int attempts = 0;

    while (!possibleCombinations.empty()) {
        string guess = possibleCombinations[possibleCombinations.size() / 2]; 
        attempts++;
        cout << "Компьютер предполагает: " << guess << endl;

        pair<int, int>b_k = getBullsAndCows(secret, guess);
        int bulls = b_k.first;
        int cows = b_k.second;
        if (bulls == 4) { 
            cout << "Компьютер угадал число " << guess << " за " << attempts << " попыток!" << endl;
            break;
        }

        possibleCombinations = filterCombinations(possibleCombinations, guess, bulls, cows);
    }
}

//для второго режима генерирует случайное подходящее число

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

// вычисляет быков и коров

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

// проверяет валидность введенного числа

string checkNumber()
{
    string secretNumber;
    cout << "Введите четырехзначное число (цифры не могут повторяться): ";
    cin >> secretNumber;

    while (secretNumber.length() != 4 || !isdigit(secretNumber[0]) ||
        (secretNumber[0] == '0') ||
        (secretNumber[1] == secretNumber[0]) ||
        (secretNumber[2] == secretNumber[0]) ||
        (secretNumber[3] == secretNumber[0]) ||
        (secretNumber[2] == secretNumber[1]) ||
        (secretNumber[3] == secretNumber[1]) ||
        (secretNumber[3] == secretNumber[2])) {
        cout << "Неверный ввод. Пожалуйста, введите четырехзначное число (цифры не могут повторяться): ";
        cin >> secretNumber;
    }
    return secretNumber;
}

// запускает игру 

void startGame() {
    cout << "Добро пожаловать в игру 'Быки и Коровы'!" << endl;
    start:
    cout << "Выберите режим игры:" << endl;
    cout << "1. Игрок загадывает число, компьютер угадывает." << endl;
    cout << "2. Компьютер загадывает число, игрок угадывает." << endl;
    cout << "3. Выход" << endl;

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
        cout << "Вы закончили игру.До Свидания!";
    }
    else  {
        cout << "Неверный выбор режима." << endl;
        goto start;
    }
}
