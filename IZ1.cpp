// ЮФУ ИКТИБ МОП ЭВМ
// Программирование и Основы Теории Алгоритмов 2
// Индивидульное задания №1
// КТбо1-7 Черноусов Даниил Владимирович 
// 27.10.2022

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//структура для хранения таблицы переходов
struct TransitionTable
    {
    int numStates;   // переменная, определяющая количество состояний в автомате;

    int** nextState; // двумерный массив, где строки
                     // соответствуют текущему состоянию автомата,
                     // а столбцы - входным символам
    };


//-----------------------------------------------------------------------------
// Функция проверяет строку на корректность
// Вх. данные: введенная строка
// Результат: true, если удовлетворяет условиям, иначе false
//-----------------------------------------------------------------------------
bool isValidInput(string input) {
    for (char c : input) {
        if (c < '0' || c > '4') {
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------------
// Функция инициализирует (заполняет) таблицу переходов для конечного автомата
// Вх. данные: заполняемая таблица
// Результат: заполненная таблица
//-----------------------------------------------------------------------------
void initTransitionTable(TransitionTable& tt)
    {
    ifstream fin("input.txt");
    fin >> tt.numStates;

    tt.nextState = new int* [tt.numStates];
    for (int i = 0; i < tt.numStates; i++)
        {
        tt.nextState[i] = new int[tt.numStates];
        for (int j = 0; j < tt.numStates; j++)
            {
            fin >> tt.nextState[i][j];
            }
        }
    }


//-----------------------------------------------------------------------------
// Функция переводит число из пятеричной СС в десятеричную
// Вх. данные: число из входной строки
// Результат: переведенное число
//-----------------------------------------------------------------------------
int from5to10(string input)
    {
    int result = 0;
    int base = 1;
    for (int i = input.size() - 1; i >= 0; i--)
        {
        result += (input[i] - '0') * base;
        base *= 5;
        }
    return result;
    }
//-----------------------------------------------------------------------------
// Функция проверяет, делится ли входное число на 7
// Вх. данные: число из входной строки
// Результат: выясняет, делится ли введенное число на 7
//-----------------------------------------------------------------------------
void isDivisibleBySeven(string input) {
    TransitionTable tt;
    initTransitionTable(tt);
    int decimal = from5to10(input);//
    (decimal % 7 == 0) ? cout << "Yes" << endl : cout << decimal << " No\nОстаток от деления на 7: " << (decimal % 7) << endl;
    
}


int main() {
    setlocale(LC_ALL, "Russian");
    string input;
    char choice;
    bool flag;
    TransitionTable tt;
    initTransitionTable(tt);
    do
        {
        cout << "Введите входное слово: ";
        cin >> input;

        if (!isValidInput(input))
            {
            cout << "Неверный ввод. Введите пятеричное число (0, 1, 2, 3, 4):" << endl;
            cout << "Хотите ввести другое число? (y/n) ";
            cin >> choice;
            (choice == 'n' || choice == 'N') ? flag = false : flag = true;
            continue;
            }

        int state = 0;
        for (int i = 0; i < input.length(); i++)
            {
            int digit = input[i] - '0';
            int nextState = tt.nextState[state][digit];
            cout << i + 1 << " q" << state << " -> q" << nextState << endl;
            state = nextState;
            }

        isDivisibleBySeven(input);

        cout << "Хотите ввести другое число? (y/n) ";
        cin >> choice;

        (choice == 'n' || choice == 'N') ? flag = false : flag = true;
        } while (flag);

    return 0;
}
