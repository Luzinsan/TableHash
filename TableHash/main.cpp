#include <iostream>
#include <fstream>
#include <exception>
#include <conio.h>
#include "HashTable.h"
#include <windows.h>
// �������� ���������, 
// ������� ��������� ����� ��������� ����������� 
// � ������������ ������������������� ���� 
// � ��� - ��������, ���������� �� ������ ������� � ��������.
// 
// ��� - ������� ������������� �� �������� ���������� ����������.
// ������ � ��� - ������� ��������� �� �����.
// ���� ������ ��������� �� ����� 15 ����.
// 
// ������� ����������� ��� - ������� �� �����
// (������ � ����������� ����������� ����).
// 
// ������������ ����� � �������� ������ � ��� - �������.
// 
// ���������� ������ ������ ������� �� �����.
// 
// ����� ������� ���������� ����, ������� ���� ��������� ��� ������.
char getSymbol(std::initializer_list<char> list,
    std::string notification_message = "",
    std::string error_message = "������������ ��������, ���������� ��� ���.\n->");

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::string filename;
    filename = "input.txt";
    std::ifstream fin(filename);
    if (!fin)
        throw std::exception((filename + " �� ����� ���� ������ ���� �� ������\n").c_str());

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
            "�������� ��������:\n1) ����������� ���-�������\n2) �������� ����� � ���-�������\n3) ������� ����� �� ���-�������\n4) ����� ������ ����� � ���-�������\n5) ���������� ���-������� � ����� output.txt\n6) ����� �� ���������\n-> ");
        if (choice == '6') break;

        switch (choice)
        {
        case '1':
            std::cout << T;
            break;
        case '2':
        {
            std::cout << "������� �����: ";
            std::string newword;
            std::cin >> newword;
            T.insert(std::move(newword));
            break;
        }
        case '3':
        {
            std::cout << "������� �����: ";
            std::string delword;
            std::cin >> delword;
            T.del(delword);
            break;
        }
        case '4':
        {
            std::cout << "������� �����: ";
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
        default: std::cerr << "���, ���-�� ����� ��� ���...";
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