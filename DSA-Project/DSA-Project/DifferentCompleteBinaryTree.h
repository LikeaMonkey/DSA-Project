#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "TemplateTree.h"

template<class T>
class DifferentTree : public Tree<T>
{
public:
	DifferentTree() = default;
	DifferentTree(const DifferentTree& tr) { Copy(tr.m_graph); }
	DifferentTree& operator=(const DifferentTree& tr) 
	{
		if (this != &tr)
		{
			m_graph.clear();
			Copy(tr.m_graph);
		}

		return *this;
	}

	bool Empty() const noexcept { return !m_graph.size(); }

	void AddNode(const T& elem) override
	{
		if (Empty()) 
		{
			std::vector<T> root;
			root.push_back(elem);
			m_graph.emplace_back(root);
		}
		else 
		{
			auto i = m_graph.rbegin();
			int size = static_cast<int>(m_graph.size());
			int lastLevel = static_cast<int>(round(pow(2, size - 1)));
			if (static_cast<int>(i->size()) < lastLevel)
			{
				i->push_back(elem);
			}
			else 
			{
				std::vector<T> level;
				level.push_back(elem);
				m_graph.emplace_back(level);
			}
		}
	}

	const T& GetRoot() const noexcept override 
	{
		if (Empty())
		{
			std::cout << "The tree is empty!\n";
			return T();
		}

		return *(m_graph.begin()->begin());
	}

	void Print() const noexcept override
	{
		for (auto i : m_graph)
		{
			for (const auto& j : i)
				std::cout << j << '\t';

			std::cout << '\n';
		}
	}

	void PrintUpsideDown() const noexcept
	{

		for (auto i = m_graph.rbegin(); i != m_graph.rend(); ++i)
		{
			for (const auto& j : i)
				std::cout << j << '\t';

			std::cout << '\n';
		}
	}

	// Task 7
	void Tournament() override 
	{
		int counter;
		int random;
		for (auto i = m_graph.rbegin(); i + 1 != m_graph.rend(); ++i) 
		{
			counter = 0;
			for (auto j = i->begin(); j != i->end(); ++j) 
			{
				srand(static_cast<unsigned>(time(0)));
				random = rand() % (j->coefficient + (++j)->coefficient);
				auto k = i + 1;
				auto z = k->begin();
				z += (counter / 2);
				if ((j - 1)->coefficient > random)
				{
					z->name = (j - 1)->name;
					z->coefficient = (j - 1)->coefficient;
				}
				else 
				{
					z->name = j->name;
					z->coefficient = j->coefficient;
				}

				counter += 2;
			}
		}
	}

	// Task 8
	void Findpath(const std::string& name) const noexcept override
	{
		int count = 0;
		bool flag = false;
		for (auto i = m_graph.rbegin(); i != m_graph.rend(); ++i) 
		{
			flag = (FindAndPrint(name, *i) || flag);
			++count;
			if (count == 2 && !flag)
				return;
		}
	}

private:
	std::vector<std::vector<T>> m_graph;

	void Copy(const std::vector<std::vector<T>>& other) { m_graph = other.m_graph; }

	bool FindAndPrint(const std::string& name, const std::vector<T>& participants) const noexcept
	{
		size_t size = participants.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (participants[i].name == name)
			{
				if (i % 2 == 1)
					std::cout << participants[i-1].name << " - " << participants[i].name << '\t';
				else
					std::cout << participants[i].name << " - " << participants[i+1].name << '\t';

				return true;
			}
		}

		return false;
	}
};
