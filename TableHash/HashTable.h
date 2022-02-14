#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
class HashTable
{
private:
	std::vector<std::string> _table;

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

	const std::string& operator[](int index) const
	{
		return _table[index];
	}
	std::string& operator[](int index)
	{
		return _table[index];
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
			T._table.push_back(word);
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
		if(!word.empty())
			T._table.push_back(word);
		return in;
	}
};

