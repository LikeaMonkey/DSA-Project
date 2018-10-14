#pragma once

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "TemplateTree.h"

template<class T>
class RootCBTree : public Tree<T>
{
public:
	RootCBTree() : root(T()), left(NULL), right(NULL)
	{}

	~RootCBTree()
	{
		delete left;
		delete right;
	}

	RootCBTree(const T& val) : root(val), left(NULL), right(NULL)
	{}

	RootCBTree(const RootCBTree<T>& other)
	{
		CopyTree(other);
	}

	RootCBTree<T>& operator=(const RootCBTree<T>& other)
	{
		if (this != &other)
		{
			delete left;
			delete right;
			CopyTree(other);
		}

		return *this;
	}

	// Returns the root value of the current tree.
	const T& GetRoot() const noexcept override { return root; }

	// Check if the tree is empty
	bool Empty() const noexcept { return (root == T() || left == NULL); }

	// Returns the left subtree of the current tree.
	RootCBTree<T>& GetLeft() const noexcept { return *left; }
	// Returns the right subtree of the current tree.
	RootCBTree<T>& GetRight() const noexcept { return *right; }

	void AddNode(const T& elem) override
	{
		if (left == NULL)
		{
			left = new RootCBTree<T>(elem);
		}
		else if (right == NULL)
		{
			right = new RootCBTree<T>(elem);
		}
		else
		{
			std::queue<RootCBTree<T>*> children;
			children.push(left);
			children.push(right);
			RootCBTree<T> *temp;
			while (true)
			{
				temp = children.front();
				if (temp->left)
				{
					children.push(temp->left);
				}
				else
				{
					temp->left = new RootCBTree<T>(elem);
					break;
				}

				if (temp->right)
				{
					children.push(temp->right);
				}
				else
				{
					temp->right = new RootCBTree<T>(elem);
					break;
				}

				children.pop();
			}
		}
	}

	void Print() const noexcept override
	{
		if (left)
			left->Print();

		if (right)
			right->Print();

		std::cout << root << " | ";
	}

	Tree<T>& GetParent(T elem) const noexcept
	{
		if (left == NULL)
			return;

		if (left->root.name == elem.name)
			return *this;

		if (right == NULL)
			return;

		if (right->root.name == elem.name)
			return *this;
	}

	// Task 7
	void Tournament() override
	{
		if (left == NULL)
			return;

		if (right == NULL)
		{
			root.name = left->root.name;
			root.coefficient = left->root.coefficient;
			return;
		}

		left->Tournament();
		right->Tournament();
		srand(static_cast<unsigned>(time(0)));
		int firstCoef = left->root.coefficient;
		int secondCoef = right->root.coefficient;
		int random = rand() % (firstCoef + secondCoef);
		if (random < firstCoef) 
		{
			root.name = left->root.name;
			root.coefficient = left->root.coefficient;
		}
		else 
		{
			root.name = right->root.name;
			root.coefficient = right->root.coefficient;
		}
	}
	// Task 8
	void Findpath(const std::string& name) const noexcept override
	{
		if (!left && left->root.name == name) 
		{
			left->Findpath(name);
			std::cout << left->root.name << " - " << right->root.name << "   ";
		}
		else if (!right && right->root.name == name)
		{
			right->Findpath(name);
			std::cout << right->root.name << " - " << left->root.name << "   ";
		}
		else 
		{
			if (!left)
				left->Findpath(name);
			else
				return;

			if (!right)
				right->Findpath(name);
		}
	}

private:
	T root;
	RootCBTree<T> *left;
	RootCBTree<T> *right;

	void CopyTree(const RootCBTree<T>& other)
	{
		root = other.root;
		if (other.left)
		{
			left = new Tree<T>;
			GetLeft().CopyTree(other.GetLeft());
		}

		if (other.right)
		{
			right = new Tree<T>;
			GetRight().CopyTree(other.GetRight());
		}
	}
};