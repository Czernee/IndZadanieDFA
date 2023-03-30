// ЮФУ ИКТИБ МОП ЭВМ
// Программирование и Основы Теории Алгоритмов 2
// Индивидульное задания №1
// КТбо1-7 Черноусов Даниил Владимирович 
// 30.10.2022

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

//структура для хранения таблицы переходов состояний
struct Condition
    {
    string name; //имя состояния (q0 - q6)
    unordered_map<int, Condition*> transitions; //таблица переходов, связывающая состояния конечного автомата
    };


//----------------------------------------------------------------------------
// Функция устанавливает таблицу переходов между состояниями (инициализирует)
// Входные данные не трубуются
// Результат: инициализированная таблица переходов
//----------------------------------------------------------------------------
Condition* initTransitionTable()
    {
    Condition* q0 = new Condition{ "q0" };
    Condition* q1 = new Condition{ "q1" };
    Condition* q2 = new Condition{ "q2" };
    Condition* q3 = new Condition{ "q3" };
    Condition* q4 = new Condition{ "q4" };
    Condition* q5 = new Condition{ "q5" };
    Condition* q6 = new Condition{ "q6" };

    q0->transitions = { {0, q0}, {1, q1}, {2, q2}, {3, q3}, {4, q4} };
    q1->transitions = { {0, q5}, {1, q6}, {2, q0}, {3, q1}, {4, q2} };
    q2->transitions = { {0, q3}, {1, q4}, {2, q5}, {3, q6}, {4, q0} };
    q3->transitions = { {0, q1}, {1, q2}, {2, q3}, {3, q4}, {4, q5} };
    q4->transitions = { {0, q6}, {1, q0}, {2, q1}, {3, q2}, {4, q3} };
    q5->transitions = { {0, q4}, {1, q5}, {2, q6}, {3, q0}, {4, q1} };
    q6->transitions = { {0, q2}, {1, q3}, {2, q4}, {3, q5}, {4, q6} };

    return q0;
    }

//----------------------------------------------------------------------------
// Функция проверяет корректность вводимой цепочки символов
// Вх. данные: вводимая цепочка символов
// Результат: true, если цепочка корректно записана, и false в ином случае
//----------------------------------------------------------------------------
bool isValidInput(const string& input)
    {
    for (char c : input)
        {
        if (c < '0' || c > '4')
            {
            return false;
            }
        }
    return true;
    }

//----------------------------------------------------------------------------
// Функция производит переход из одного состояния в следующее
// Вх. данные: состояние, из которого производится переход, вводимый символ, получаемый автоматом
// Результат: следующее состояние, в который перешел автомат, получив определенный символ из вводимой цепочки
//----------------------------------------------------------------------------
Condition* transition(Condition* current_state, int digit)
    {
    return current_state->transitions[digit];
    }

int main()
    {
    setlocale(LC_ALL, "Russian");
    Condition* current_state = initTransitionTable();
    string input;
    char choice;
    bool flag;
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

        current_state = initTransitionTable();
        for (char c : input)
            {
            int digit = c - '0';
            Condition* next_state = transition(current_state, digit);
            cout << digit << " " << current_state->name << " -> " << next_state->name << endl;
            current_state = next_state;
            }

        if (current_state->name == "q0")
            {
            cout << "Yes" << endl;
            cout << "Хотите ввести другое число? (y/n)" << endl;
            cin >> choice;
            (choice == 'n' || choice == 'N') ? flag = false : flag = true;
            }
        else
            {
            cout << "No" << endl;
            cout << "Хотите ввести другое число? (y/n)" << endl;
            cin >> choice;
            (choice == 'n' || choice == 'N') ? flag = false : flag = true;
            }
        } while (flag);

    //очистка памяти
    delete initTransitionTable()->transitions[0]->transitions[0]->transitions[0]->transitions[0]->transitions[0]->transitions[0];
    delete initTransitionTable()->transitions[0]->transitions[0]->transitions[0]->transitions[0]->transitions[0];
    delete initTransitionTable()->transitions[0]->transitions[0]->transitions[0]->transitions[0];
    delete initTransitionTable()->transitions[0]->transitions[0]->transitions[0];
    delete initTransitionTable()->transitions[0]->transitions[0];
    delete initTransitionTable()->transitions[0];
    delete initTransitionTable();

    return 0;
    }

