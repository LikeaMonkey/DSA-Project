#include "stdafx.h"

#include <iostream>
#include <string>

#include "CompleteBinaryTreeFathers.h"
#include "RootCompleteBinaryTree.h"
#include "CompleteChainBinaryTree.h"
#include "DifferentCompleteBinaryTree.h"

void TestCompleteBinaryTreeFathers()
{
	// Task 9 (3 times) to show its all random
	TreeFathers<Player> trf1;
	trf1.AllTogether();
	TreeFathers<Player> trf2;
	trf2.AllTogether();
	TreeFathers<Player> trf3;
	trf3.AllTogether();
	std::cout << "Test General (Task 9)\t\t\t\t\t-- Success !\n";

	TreeFathers<Player> tr;
	tr.Print();
	
	std::string name1 = "Mike";
	std::string name2 = "Jerry";
	std::string name3 = "Danni";
	Player pl1 (name1, 10);
	Player pl2 (name2, 20);
	Player pl3 (name3, 30);
	
	TreeFathers<Player> tr1;
	tr1.AddNode(pl1);
	tr1.AddNode(pl2);
	tr1.AddNode(pl3);
	tr1.Print();
	std::cout << "Test 1 (AddNode, print)\t\t\t\t\t-- Success !\n";
	tr1.PrintInfo();
	std::cout << "Test 2 (Vector of elements)\t\t\t\t\t-- Success !\n";
	tr1.FathersIndex();
	std::cout << "Test 3 (Vector of index of fathers)\t\t\t\t\t-- Success !\n";

	std::cout << tr1.GetRoot() << '\n';
	std::cout << "Test 4 (getRoot)\t\t\t\t\t-- Success !\n";

	if (!tr1.Empty()) 
		std::cout << "Test 5 (empty)\t\t\t\t\t-- Success !\n";
}

void TestRootCompleteBinaryTree()
{
	// Task 9 (3 times) to show its all random
	RootCBTree<Player> tr1;
	tr1.AllTogether();
	RootCBTree<Player> tr2;
	tr2.AllTogether();
	RootCBTree<Player> tr3;
	tr3.AllTogether();
	std::cout << "Test General (Task 9)\t\t\t\t\t-- Success !\n";
}

void TestCompleteChainBinaryTree()
{
	// Task 9 (3 times) to show its all random
	CBCT<Player> tr1; 
	tr1.AllTogether();
	CBCT<Player> tr2;
	tr2.AllTogether();
	CBCT<Player> tr3;
	tr3.AllTogether();
	std::cout << "Test General (Task 9)\t\t\t\t\t-- Success !\n";
}

void TestDifferentCompleteBinaryTree()
{
	// Task 9 (3 times) to show its all random 
	DifferentTree<Player> tr1; 
	tr1.AllTogether();
	DifferentTree<Player> tr2;
	tr2.AllTogether();
	DifferentTree<Player> tr3;
	tr3.AllTogether();
	std::cout << "Test General (Task 9)\t\t\t\t\t-- Success !\n";
}

int main()
{
	//TestCompleteBinaryTreeFathers();
	//TestRootCompleteBinaryTree();
	//TestCompleteChainBinaryTree();
	//TestDifferentCompleteBinaryTree();

    return 0;
}

