#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "TemplateTree.h"

template <class T>
class CBCT : public Tree<T>	//  Complete Binary Chain Tree
{
public:
	CBCT() = default;
	CBCT(const CBCT& cbct)
	{
		Copy(cbct);
	}

	CBCT& operator=(const CBCT& cbct)
	{
		if (this != &cbct) 
		{
			m_data.clear();
			m_left.clear();
			m_right.clear();
			Copy(cbct);
		}

		return *this;
	}

	void AddNode(const T& elem) override
	{
		m_data.push_back(elem);
		size_t size = m_left.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (m_left[i] == -1) 
			{
				m_left[i] = static_cast<int>(m_data.size()) - 1;
				break;
			}

			if (m_right[i] == -1) 
			{
				m_right[i] = static_cast<int>(m_data.size()) - 1;
				break;
			}
		}

		m_left.emplace_back(-1);
		m_right.emplace_back(-1);
	}

	const T& GetRoot() const noexcept override { return m_data[0]; }

	const std::vector<T>& GetLeaves() const noexcept
	{
		std::vector<T> leaves;
		size_t size = m_data.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (m_left[i] == -1 && m_right[i] == -1)
			{
				leaves.push_back(m_data[i]);
			}
		}

		return leaves;
	}

	bool IsLeaf(int index) const noexcept
	{
		return (m_left[index] == -1 && m_right[index] == -1);
	}

	void Print() const noexcept override
	{
		std::vector<int> nodes;
		nodes.push_back(0); // Root position
		std::vector<int>children;
		while (!nodes.empty()) 
		{
			for (const auto& node : nodes)
			{
				std::cout << m_data[node] << '\t';
				if (m_left[node] > 0)
					children.push_back(m_left[node]);

				if (m_right[node] > 0)
					children.push_back(m_right[node]);
			}

			std::cout << '\n';
			nodes = std::move(children);
		}
	}

	int GetParent(const T& child) const noexcept
	{
		int size = static_cast<int>(m_data.size());
		for (int i = 0; i < size; ++i)
		{
			if (m_data[m_left[i]] == child || m_data[m_right[i]] == child)
				return i;
		}

		std::cerr << child << " is not a node inside the tree\n";

		return -1;
	}

	// Task 7
	void Tournament() override 
	{
		int firstCoef;
		int secondCoef;
		int randomCoef;
		int child;
		int index = static_cast<int>(m_data.size()) - 1;
		while (index > 1)
		{
			firstCoef = m_data[index].coefficient;
			--index;
			secondCoef = m_data[index].coefficient;
			srand(static_cast<unsigned>(time(0)));
			randomCoef = rand() % (firstCoef + secondCoef);
			child = index + (randomCoef < firstCoef);
			m_data[GetParent(m_data[child])] = m_data[child];
			--index;
		}
	}
	// Task 8
	void Findpath(const std::string& name) const noexcept
	{
		if (!m_data.size()) 
		{
			std::cout << "Tree is empty!\n";
			return;
		}

		size_t i = m_data.size() - 1;
		while (i >= 0 && m_data[i].name != name)
		{
			--i;
			if (i < 0)
			{
				std::cout << "There no player with that name\n";
				return;
			}
		}

		if (i == 0)
			return;

		size_t father = (i - 1) / 2;
		while (m_data[father].name == name) 
		{
			if (father == 0) 
				return;

			if (name == m_data[m_left[father]].name)
				std::cout << name << " - " << m_data[m_right[father]] << '\n';
			else
				std::cout << m_data[m_left[father]] << " - " << name << '\n';

			father = (father - 1) / 2;
			if (father == 0)
				break;
		}

		if (name == m_data[m_left[father]].name)
			std::cout << name << " - " << m_data[m_right[father]] << '\n';
		else
			std::cout << m_data[m_left[father]] << " - " << name << '\n';

		std::cout << '\n';
	}

private:
	std::vector<T> m_data;
	std::vector<int> m_left;
	std::vector<int> m_right;

	void copy(const CBCT& cbct)
	{
		size_t size = cbct.m_data.size();
		for (size_t i = 0; i < size; ++i)
		{
			m_data[i] = m_cbct.data[i];
			m_left[i] = m_cbct.left[i];
			m_right[i] = m_cbct.right[i];
		}
	}
};