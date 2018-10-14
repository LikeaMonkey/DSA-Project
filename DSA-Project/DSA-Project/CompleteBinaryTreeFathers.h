#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "TemplateTree.h"

template<typename T>
class TreeFathers : public Tree<T>	// Complete Binary Тree Fathers List
{
public:
	TreeFathers() { fathers.push_back(-2); }

	TreeFathers(const TreeFathers<T>& tr)
	{
		size_t size = tr.fathers.size();
		for (size_t i = 0; i < size; ++i)
		{
			info[i] = tr.info[i];
			fathers[i] = tr.fathers[i];
		}
	}

	TreeFathers& operator=(const TreeFathers& tr)
	{
		if (this != &tr)
		{
			info.clear();
			father.clear();
			size_t size = tr.fathers.size();
			for (size_t i = 0; i < size; ++i)
			{
				info[i] = tr.info[i];
				fathers[i] = tr.fathers[i];
			}
		}

		return *this;
	}

	bool Empty() const noexcept { return fathers[0] == -2; }

	const T& GetRoot() const noexcept override
	{
		if (Empty())
		{
			std::cout << "The tree is empty!\n";
			return T();
		}

		return info[0];
	}

	const T& GetFather(const T& child) const noexcept
	{
		if (!Empty())
		{
			if (child == info[0])
			{
				std::cout << "The child( " << child << " ) is the root of the tree and has no father!\n";
			}
			else
			{
				size_t size = fathers.size()
				for (size_t i = 1; i < size; ++i)
				{
					if (child == info[i])
						return info[fathers[i]];
				}

				std::cout << "The child( " << child << " ) has no father and is not in the tree!\n";
			}
		}
		else
			std::cout << "The tree is empty, there are no father!\n";

		return T();
	}

	void AddNode(const T& elem) override
	{
		info.push_back(elem);
		if (Empty())
		{
			fathers[0] = -1;
		}
		else
		{
			fathers.push_back((static_cast<int>(fathers.size()) - 1) / 2);
		}
	}

	void FathersIndex() const noexcept
	{
		for (const auto& elem : fathers)
			std::cout << elem << "  ";

		std::cout << '\n';
	}

	void PrintInfo() const noexcept
	{
		for (const auto& elem : info)
			std::cout << elem << "  ";

		std::cout << '\n';
	}

	void Print() const noexcept
	{
		int size = static_cast<int>(info.size()) - 1;
		int from = 0;
		int to = 0;
		while (from < size)
		{
			if (to > size)
				to = size;

			for (int i = from; i <= to; ++i)
			{
				std::cout << info[i] << "    ";
			}

			std::cout << '\n';
			from = (2 * from + 1);
			to = (2 * to + 2);
		}

		std::cout << '\n';
	}

	// Task 7
	void Tournament() override
	{
		int index = static_cast<int>(fathers.size()) - 1;
		int firstCoef;
		int secondCoef;
		int randomCoef;
		while (index > 1) 
		{
			firstCoef = info[index].coefficient;
			--index;
			secondCoef = info[index].coefficient;
			srand(static_cast<unsigned int>(time(0)));
			randomCoef = rand() % (firstCoef + secondCoef);
			info[fathers[index]] = info[index + (randomCoef < firstCoef)];
			--index;
		}
	}
	// Task 8
	void Findpath(const std::string& name) const noexcept override
	{
		if (Empty()) 
		{
			std::cout << "Tree is empty!\n";
			return;
		}

		int i = static_cast<int>(info.size()) - 1;
		while (i > -1 && info[i].name != name)
		{
			--i;
			if (i < 0)
			{
				std::cout << "There no player with that name\n";
				return;
			}
		}

		while (info[fathers[i]].name == name) 
		{
			if (name == info[fathers[i] * 2 + 1].name)
				std::cout << name << " - " << info[fathers[i] * 2 + 2];
			else
				std::cout << info[fathers[i] * 2 + 1] << " - " << name;
			std::cout << '\n';

			i = fathers[i];
			if (i == 0)
				break;
		}

		if (i == 0)
			return;

		if (name == info[fathers[i] * 2 + 1].name)
			std::cout << name << " - " << info[fathers[i] * 2 + 2];
		else
			std::cout << info[fathers[i] * 2 + 1] << " - " << name;

		std::cout << '\n';
	}

private:
	std::vector<T> info;
	std::vector<int> fathers;
};
