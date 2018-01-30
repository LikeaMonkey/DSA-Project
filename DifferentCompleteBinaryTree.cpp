//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;

struct Player1
{
	string name;
	int coefficient;
	Player1() {
		name = "";
		coefficient = -1;
	}
	friend ostream& operator<<(ostream& os, const Player1 &pl) {
		if (pl.coefficient != -1)
			os << pl.name;
		else os << "-|-";
		return os;
	}
	friend istream& operator >> (istream& is, Player1 & pl) {
		is >> pl.name >> pl.coefficient;
		return is;
	}
};

template<class T>
class DifferentTree
{
	vector<vector<T>> graph;
	void copy(vector<vector<T>> const& other) {
		graph = other.graph;
	}
public:
	DifferentTree() {}
	DifferentTree(const DifferentTree& tr) { copy(tr.graph); }
	DifferentTree& operator=(const DifferentTree& tr) {
		if (this != &tr) {
			graph.clear();
			copy(tr.graph);
		}
		return *this;
	}
	bool empty()const { return !graph.size(); }
	void addNode(T const elem) {
		if (empty()) {
			vector<T> root;
			root.push_back(elem);
			graph.push_back(root);
		}
		else {
			int size = graph.size();
			auto i = graph.rbegin();
			int lastLevel = round(pow(2, size - 1));
			if (i->size()<lastLevel)
				i->push_back(elem);
			else {
				vector<T> level;
				level.push_back(elem);
				graph.push_back(level);
			}
		}
	}
	void printUpsideDown() const {
		for (auto i = graph.rbegin(); i != graph.rend(); i++) {
			for (auto j = i->begin(); j != i->end(); j++)
				cout << *j << '\t';
			cout << endl;
		}
	}
	void print()const {
		for (auto i = graph.begin(); i != graph.end(); i++) {
			for (auto j = i->begin(); j != i->end(); ++j)
				cout << *j << '\t';
			cout << endl;
		}
	}
	// Задача 5
	void fillTree(vector<T> leaves) {
		srand(unsigned(time(0)));
		random_shuffle(leaves.begin(), leaves.end());    //shuffle vector
		int interRoot = leaves.size() - 1;
		for (int i = 0; i < interRoot; i++)
			addNode(T());
		for (int i = 0; i < leaves.size(); i++)         //fill the leaves of the tree
			addNode(leaves[i]);
	}
	int numberOfLines() {
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
		vector<T> vec;
		bool* taken = new bool[numberOfLines()]();
		int takenCount = 0;
		srand(time(NULL));
		int n = rand() % numberOfLines();
		while (takenCount < n) {
			int randLine = rand() % numberOfLines();
			if (!taken[randLine]) {
				taken[randLine] = true;
				takenCount++;
			}
			else { continue; }
		}
		int i = 0;
		Player1 line;
		ifstream myfile("participants.txt");
		if (myfile.is_open()) {
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
		for (auto i = graph.rbegin(); i + 1 != graph.rend(); i++) {
			int counter = 0;
			for (auto j = i->begin(); j != i->end(); j++){
				srand(time(0));
				int random = rand() % (j->coefficient + (++j)->coefficient);
				auto k = i + 1;
				auto z = k->begin();
				z += (counter / 2);
				if ((j - 1)->coefficient > random){
					z->name = (j - 1)->name;
					z->coefficient = (j - 1)->coefficient;
				}
				else {
					z->name = j->name;
					z->coefficient = j->coefficient;
				}
				counter += 2;
			}
		}
	}
	// Задача 8
	void findpath(string name)
	{
		int count = 0;
		bool flag = false;
		for (auto i = graph.rbegin(); i+1 != graph.rend(); i++){
			flag = (findAndPrint(name, *i) || flag);
			count++;
			if (count == 2 && !flag)return;
		}
	}
	bool findAndPrint(string name, vector<T> participants) 
	{
		for (int i = 0; i < participants.size(); i++) {
			if (participants[i].name == name) {
				if (i % 2==1) 
					cout << participants[i-1].name<< " - " << participants[i].name << '\t';
				else
					cout << participants[i].name << " - " << participants[i+1].name << '\t';
				return true;
			}
		}
		return false;
	}
	// Задача 9
	void allTogether() {
		vector<T> vec = getParticipants();
		fillTree(vec);
		tournament();
		print();
		cout << endl;
		string name;
		cout << "Input Player's name: ";
		getline(cin, name);
		findpath(name);
		cout << "\n\n";
	}
};

int main() {
	DifferentTree<Player1> tr1;  // Task 9 (3 times) to show its all random  
	tr1.allTogether();
	DifferentTree<Player1> tr2;
	tr2.allTogether();
	DifferentTree<Player1> tr3;
	tr3.allTogether();
	cout << "Test General (Task 9)                    -- Success !\n";

	return 0;
}