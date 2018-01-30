//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <queue>
using namespace std;

struct Player3
{
	string name;
	int coefficient;

	Player3() {
		name = "";
		coefficient = -1;
	}
	friend ostream& operator<<(ostream& os, const Player3 &pl) {
		if (pl.coefficient != -1)
			os << pl.name;
		else os << "|";
		return os;
	}
	bool operator==(Player3 const& p3) {
		if (name == p3.name) { return true; }
		return false;
	}
	friend istream& operator>>(istream& is, Player3 & pl) {
		is >> pl.name >> pl.coefficient;
		return is;
	}
};

template<class T>
class Tree 
{
private:
	T root;
	Tree<T> *left, *right;

	void CopyTree(Tree<T> const &other) {
		root = other.root;

		if (other.left) {
			left = new Tree<T>;
			GetLeft().CopyTree(other.GetLeft());
		}
		if (other.right) {
			right = new Tree<T>;
			GetRight().CopyTree(other.GetRight());
		}
	}
public:
	Tree() {    // Default constructor
		root = T();
		left = right = NULL;
	}
	~Tree() {    // Destructor
		if (left) { delete left; }
		if (right) { delete right; }
	}
	Tree(Tree<T> const &other) {   // Copy constructor
		CopyTree(other);
	}
	Tree<T>& operator=(Tree<T> const &other) {  // Predifined operator =
		if (this != &other) {
			if (left) { delete left; }
			if (right) { delete right; }
			CopyTree(other);
		}
		return *this;
	}
	Tree(T val) { // Constructor with parameter
		root = val;
		left = right = NULL;
	}
	T GetRoot() { return root; }						// Returns the root value of the current tree.
	bool empty() const { return (root == T() || left == NULL); }  // Check if the tree is empty
	Tree<T>& GetLeft() const { return *left; }			// Returns the left subtree of the current tree.
	Tree<T>& GetRight() const { return *right; }		// Returns the right subtree of the current tree. 
	void addNode(T val) {                       // Add element to the tree
		if (left == NULL) { left = new Tree<T>(val); }
		else if (right == NULL) { right = new Tree<T>(val); }
		else {
			queue<Tree<T>*> children;
			children.push(left);
			children.push(right);
			Tree<T> *temp;
			while (true) {
				temp = children.front();
				if (temp->left) { children.push(temp->left); }
				else {
					temp->left = new Tree<T>(val);
					break;
				}
				if (temp->right) { children.push(temp->right); }
				else {
					temp->right = new Tree<T>(val);
					break;
				}
				children.pop();
			}
		}
	}
	void print() const {   
		if (left) { left->print(); }
		if (right) { right->print(); }
		cout << root << " | ";
	}
	Tree<T>& getParent(T elem) {  // Return the father of the element
		if (left == NULL) { return; }
		if (left->root.name == elem.name) { return *this; }
		if (right == NULL) { return; }
		if (right->root.name == elem.name) { return *this; }
	}
	// Задача 5
	void fillTree(vector<T> leaves){
		srand(unsigned(time(0)));
		random_shuffle(leaves.begin(), leaves.end()); //shuffle vector
		int interRoot = leaves.size() - 2;
		for (int i = 0; i < interRoot; i++)
			addNode(T());
		for (int i = 0; i < leaves.size(); i++) //fill the leaves of the tree
			addNode(leaves[i]);
	}
	int numberOfLines() {   // Return the number of the file lines
		int num = 0;
		string line;
		ifstream myfile("participants.txt");
		if (myfile.is_open()) {
			while (!myfile.eof()) {
				getline(myfile, line);
				num++;
			}
			myfile.close();
		}
		return num;
	}
	// Задача 6
	vector<T> getParticipants() {
		bool* taken = new bool[numberOfLines()]();
		int takenCount = 0;
		srand(time(NULL));
		int n = rand() % numberOfLines();
		while (takenCount < n) {
			int randLine = rand() % numberOfLines();
			if (taken[randLine] == false) {
				taken[randLine] = true;
				takenCount++;
			}
			else { continue; }
		}

		ifstream myfile("participants.txt");
		vector<T> vec;
		if (myfile.is_open()) {
			int i = 0;
			Player3 line;
			while (myfile >> line) {
				if (taken[i])
					vec.push_back(line);
				i++;
			}
			myfile.close();
		}
		return vec;
	}
	// Задача 7
	void tournament() {
		if (left == NULL) { return; }
		else if (right == NULL) {
			root.name = left->root.name;
			root.coefficient = left->root.coefficient;
			return;
		}
		left->tournament();
		right->tournament();
		srand(time(NULL));
		int firstCoef = left->root.coefficient;
		int secondCoef = right->root.coefficient;
		int random = rand() % (firstCoef + secondCoef);
		if (random < firstCoef) {
			root.name = left->root.name;
			root.coefficient = left->root.coefficient;
		}
		else {
			root.name = right->root.name;
			root.coefficient = right->root.coefficient;
		}
	}
	// Задача 8
	void findpath(string name) {
		if (left == NULL) { return; }
		else if (left->root.name == name) {
			left->findpath(name);
			cout << left->root.name << " - ";
			cout << right->root.name << "   ";
		}
		else if (right == NULL) { return; }
		else if (right->root.name == name) {
			right->findpath(name);
			cout << right->root.name << " - ";
			cout << left->root.name << "   ";
		}
		else {
			if (left == NULL) { return; }
			left->findpath(name);
			if (right == NULL) { return; }
			right->findpath(name);
		}
	}
	// Задача 9
	void allTogether(){
		vector<T> theVec = getParticipants();
		fillTree(theVec);
		tournament();
		print();
		cout << "\nThe winner is: " << GetRoot() << endl;
		string name;
		cout << "Enter player: ";
		cin >> name;
		findpath(name);
		cout << endl;
	}
};

int main()
{
	Tree<Player3> tr1;    // Test: Task 9 (3 times to show its all random)               => Passed
	tr1.allTogether();    
	Tree<Player3> tr2;
	tr2.allTogether();
	Tree<Player3> tr3;
	tr3.allTogether();

	Tree<int> tr;										// Test: Default Constructor	=> Passed
	cout << !tr.empty() << endl;						// Test: empty()				=> Passed
	for (int i = 1; i < 25; i++) { tr.addNode(i); }		// Test: addNode(val)			=> Passed
	tr.print();											// Test: print()				=> Passed

	system("pause");

	// Test: GetLeft(), GetRight(), GetRoot()											=> Passed
	cout << tr.GetRoot() << '\t' << tr.GetLeft().GetRoot() << '\t' << tr.GetRight().GetRoot() << endl;

	system("pause");

	// Test: Copy Constructor															=> Passed
	Tree<int> a(tr);
	a.print();
	cout << endl;

	system("pause");

	// Test: operator=																	=> Passed
	Tree<int> c, b;
	c = b = a;
	b.print();
	cout << endl;
	c.print();
	cout << endl;

	system("pause");
	
	Tree<Player3> scheme;
	cout << scheme.numberOfLines();						// Test: numberOfLines()		=> Passed

	vector<Player3> theVec = scheme.getParticipants();	// Test: getParticipants()		=> Passed
	scheme.fillTree(theVec);							// Test: filltree(vector)		=> Passed		
	scheme.tournament();								// Test: tournament()			=> Passed
	scheme.print();										
	cout << endl;
	cout << "The winner is: " << scheme.GetRoot() << endl;

	string name;
	cout << "Enter player: ";
	cin >> name;
	scheme.findpath(name);								// Test: findpath(name)			=> Passed

	system("pause");
	return 0;
}