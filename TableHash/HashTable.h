#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#define INDEX_NOT_FOUND -1

class HashTable
{
private:
	std::vector<std::pair<std::string, bool>> _table;

public:
	HashTable() 
	{
	}

	size_t size() const
	{
		return _table.size();
	}
	HashTable& resize(size_t size) 
	{
		_table.resize(size);
		return *this;
	}
	
	static unsigned string_to_int(std::string string)
	{
		unsigned stringInt = 0;
		for (auto it = string.begin(); it != string.end(); it++)
			stringInt += *it;
		return stringInt;
	}
	unsigned hash(std::string element) const { return string_to_int(element) % _table.size(); }
	unsigned hashLinear(std::string element, unsigned index) const { return (hash(element) + index) % _table.size();}
	unsigned hashQuadratic(std::string element, unsigned index) const { return (hash(element) + index * index) % _table.size(); }
	unsigned hashDouble(std::string element, unsigned index) const { return (hash(element) + index * (1 + hash(element))) % _table.size(); }


	const std::string& operator[](int index) const
	{
		return _table[index].first;
	}
	std::string& operator[](int index)
	{
		return _table[index].first;
	}
	HashTable& insert(std::string string) 
	{
		for (int i = 0; i != _table.size(); i++)
		{
			int index = hashQuadratic(string, i);
			if (_table[index].first == "")
			{
				_table[index].first = string;
				_table[index].second = true;
				std::cout << "���������� ����: " << i << std::endl;
				return *this;
			}
		}
		_table.push_back(std::pair(string,true));
	}
	HashTable& del(std::string string)
	{
		int index = search(string);
		if (index != INDEX_NOT_FOUND)
		{
			_table[index].first = "";
			_table[index].second = false;
		}
		else std::cerr << "������ ����� �� ������� � ���-�������";
		return *this;
	}
	int search(std::string string)
	{
		int index, i = 0;
		do {
			index = hashQuadratic(string, i);
			if (_table[index].first == string)
			{
				std::cout << "���������� ����: " << i << std::endl;
				return index;
			}
			i++;
		} while ((_table[index].first != "" || _table[index].second == false) && i < _table.size());
		return INDEX_NOT_FOUND;
	}



	friend std::ostream& operator<<(std::ostream& out, const HashTable& T)
	{
		for (int i = 0; i < T.size(); i++)
			out << i << ": " << T[i] << std::endl;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, HashTable& T)
	{
		std::string word;
		in >> word;
		if (!word.empty())
			T.insert(word);
		return in;
	}

	friend std::ofstream& operator<<(std::ofstream& out, const HashTable& T)
	{
		for (int i = 0; i < T.size(); i++)
			out << i << ": " << T[i] << std::endl;

		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, HashTable& T)
	{
		std::string word;
		in >> word;
		if (!word.empty())
			T.insert(word);
		return in;
	}
};

