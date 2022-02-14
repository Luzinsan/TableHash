#include <iostream>
#include <fstream>
#include <exception>
#include <conio.h>
#include <string>
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
std::streambuf* redirectInput(std::ifstream* fin = NULL);
std::streambuf* redirectOutput(std::ofstream* fout = NULL);

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char choice;
    HashTable T;
    
    do {
        choice = getSymbol({ '1','2','3','4' },
            "������� ������ ����� � ������ ������:\n1) � ����������;\n2) �� �����\n3) ����������� (�� ����� input.txt � ���� output.txt)\n4) ��������� ���������\n-> ");
        if (choice == '4') break;
        
        std::string filein("input.txt");
        std::string fileout("output.txt");
        if (choice == '2') 
        {
            std::cout << "������� ��� �������� �����:\n->";
            getline(std::cin, filein);
            std::cout << "������� ��� ��������� �����:\n->";
            getline(std::cin, fileout);
        }
        
        std::ofstream fout;
        std::streambuf* original_stream = NULL;
        if (choice == '2' || choice == '3') 
        {
            std::ifstream fin(filein);
            original_stream = redirectInput(&fin);
            if (!original_stream) { choice = '4'; break; }
            while (fin)
                fin >> T;

            std::cin.rdbuf(original_stream);
            fin.close();
            original_stream = redirectOutput(&fout);
            if (!original_stream) { choice = '4'; break; }
        }
           
       
        char choice;
        while (true)
        {
            system("cls");
            choice = getSymbol({ '1','2','3','4','5'},
                "�������� ��������:\n1) ����������� ���-�������\n2) �������� ����� � ���-�������\n3) ������� ����� �� ���-�������\n4) ����� ������ ����� � ���-�������\n5) ����� �� ���������\n-> ");
            if (choice == '5') break;

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
                T.del(std::move(delword));
                break;
            }
            case '4':
            {
                std::cout << "������� �����: ";
                std::string indword;
                std::cin >> indword;
                std::cout << T.search(std::move(indword)) << " <- ������ ��������" << std::endl;
                break;
            }
            default: std::cerr << "���, ���-�� ����� ��� ���...";
            }
            system("pause");
        }
        if(choice == '2' || choice == '3') std::cout.rdbuf(original_stream);
    } while (true);
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

std::streambuf* redirectInput(std::ifstream* fin)
{
    std::streambuf* original_cin = std::cin.rdbuf();
    while (!*fin)
    {
        std::string filename;
        char choice;
        choice = getSymbol({ '1', '2' },
            "������ ���� �� ����� ���� ������, ���� �� ����������. ����������� ��� ���?\n1) ��\n2) �����\n->");
        if (choice == '1')
        {
            std::cout << "������� ��� �����:\n->";
            getline(std::cin, filename);
        }
        else return NULL;
        fin->open(filename);
    }
    //�������������� ����������� ����� ����� �� ���������� ����
    std::cin.rdbuf(fin->rdbuf());
    return original_cin;
}

std::streambuf* redirectOutput(std::ofstream* fout)
{
    std::streambuf* original_cout = std::cout.rdbuf();
    while (!*fout)
    {
        std::string filename;
        char choice;
        choice = getSymbol({ '1', '2' },
            "������ ���� �� ����� ���� ������, ���� �� ����������. ����������� ��� ���?\n1) ��\n2) �����\n->");
        if (choice == '1')
        {
            std::cout << "������� ��� �����:\n->";
            getline(std::cin, filename);
        }
        else return NULL;
        fout->open(filename);
    }
    //�������������� ����������� ����� ������ �� ���������� ����
    std::cout.rdbuf(fout->rdbuf());
    return original_cout;
}