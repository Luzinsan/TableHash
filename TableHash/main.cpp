#include <iostream>
#include <fstream>
#include <exception>
#include <conio.h>
#include "HashTable.h"
#include <windows.h>
// Написать программу, 
// которая реализует метод закрытого хеширования 
// с квадратичной последовательностью проб 
// и хеш - функцией, основанной на методе деления с остатком.
// 
// Хеш - таблица ориентирована на хранение символьной информации.
// Данные в хеш - таблицу заносятся из файла.
// Файл должен содержать не менее 15 слов.
// 
// Вывести построенную хеш - таблицу на экран
// (вместе с количеством выполненных проб).
// 
// Организовать поиск и удаление данных в хеш - таблице.
// 
// Результаты поиска данных вывести на экран.
// 
// Также вывести количество проб, которые были затрачены при поиске.
char getSymbol(std::initializer_list<char> list,
    std::string notification_message = "",
    std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::string filename;
    filename = "input.txt";
    std::ifstream fin(filename);
    if (!fin)
        throw std::exception((filename + " не может быть открыт либо не найден\n").c_str());

    HashTable T;
    while (fin)
        fin >> T;
    fin.close();
    std::cout << T;

    filename = "output.txt";
    char choice;
    while (true)
    {
        choice = getSymbol({ '1','2','3','4','5' },
            "Выберите действие:\n1) просмотреть хеш-таблицу\n2) вставить слово в хеш-таблицу\n3) удалить слово из хеш-таблицы\n4) найти индекс слова в хеш-таблице\n5) напечатать хеш-таблицу в файле output.txt\n6) выйти из программы\n-> ");
        if (choice == '6') break;

        switch (choice)
        {
        case '1':
            std::cout << T;
            break;
        case '2':
        {
            std::cout << "Введите слово: ";
            std::string newword;
            std::cin >> newword;
            T.insert(std::move(newword));
            break;
        }
        case '3':
        {
            std::cout << "Введите слово: ";
            std::string delword;
            std::cin >> delword;
            T.del(delword);
            break;
        }
        case '4':
        {
            std::cout << "Введите слово: ";
            std::string indword;
            std::cin >> indword;
            T.search(indword);
            break;
        }
        case '5':
        {
            std::ofstream fout(filename, 'a');
            fout << T;
            fout.close();
            break; 
        }
        default: std::cerr << "Упс, что-то пошло нет так...";
        }
    }
}
char getSymbol(std::initializer_list<char> list,
    std::string notification_message,
    std::string error_message)
{
    char choice = NULL;
    std::cout << notification_message;

    bool flag = true;
    do {
        choice = _getche();
        std::cout << std::endl;
        for (auto it = list.begin(); it != list.end(); it++)
            if (it[0] == choice) { flag = false; break; }

        if (flag) std::cerr << error_message;
    } while (flag);
    return choice;
}