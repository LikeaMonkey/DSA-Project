#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;

struct Player
{
	string name;
	int coefficient;
	Player() {
		name = "";
		coefficient = -1;
	}
	bool operator==(const Player& pl){return name == pl.name && coefficient == pl.coefficient;}
	friend ostream& operator<<(ostream& os, const Player &pl) {
		if (pl.coefficient != -1)
		os << pl.name;
		else os << "-|-";
		return os;
	}
	friend istream& operator>>(istream& is, Player & pl) {
		is >> pl.name >> pl.coefficient;
		return is;
	}
};

template <class T>
class CBCT        //  Complete Binary Chain Tree
{   
private:
	vector<T> data;
	vector<int> left, right;
	void copy(CBCT const& cbct) {
		for (int i = 0; i<cbct.data.size(); i++) {
			data[i] = cbct.data[i];
			left[i] = cbct.left[i];
			right[i] = cbct.right[i];
		}
	}
	int numberOfLines()       // Намира броя на редовете в файл, помощтна за задача 6
	{
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
public:
	CBCT()    // Default конструктор
	{}
	CBCT(CBCT const& cbct)    // Copy конструктор
	{
		copy(cbct);
	}
	CBCT& operator=(CBCT const& cbct)    // Predefined operator =
	{
		if (this != &cbct) {
			data.clear();
			left.clear(); right.clear();
			copy(cbct);
		}
		return *this;
	}
	void addNode(T key)    // Добавя елемент на правилната позиция към дървото
	{
		data.push_back(key);
		for (int i = 0; i<left.size(); i++) {
			if (left[i] == -1) {
				left[i] = data.size() - 1;
				break;
			}
			if (right[i] == -1) {
				right[i] = data.size() - 1;
				break;
			}
		}
		left.push_back(-1);
		right.push_back(-1);
	}
	vector<T> getLeaves()    // Връща вектор от листата на дървото
	{
		vector<T> leaves;
		for (int i = 0; i<data.size(); i++)
			if (left[i] == -1 && right[i] == -1)leaves.push_back(data[i]);
		return leaves;
	}
	bool isLeaf(int i)    // Проверява дали елемента е листо
	{
		return left[i] == -1 && right[i] == -1;
	}
	void printLevels()    // Извежда дървото на нива
	{
		vector<int> nodes;
		nodes.push_back(0);   //  root position
		while (!nodes.empty()) {
			vector<int>children;
			for (vector<int>::iterator i = nodes.begin(); i != nodes.end(); i++){
				cout << data[*i] << '\t';
				if (left[*i]>0)children.push_back(left[*i]);
				if (right[*i]>0)children.push_back(right[*i]);
			}
			cout << endl;
			nodes = children;
		}
	}
	int getParent(T child)    // Връща индекса на бащата на подадения елемент 
	{
		for (int i = 0; i<data.size(); i++) {
			if (data[left[i]] == child || data[right[i]] == child)return i;
		}
		cerr << child << " is not a node inside the tree" << endl;

		for (int i = 0; i<data.size(); i++) {
			if (data[left[i]] == child || data[right[i]] == child)return i;
		}
		cerr << child << " is not a node inside the tree" << endl;
		return -1;
	}
	// Задача 5
	void fillTree(vector<T> leaves){
		srand(unsigned(time(0)));
		random_shuffle(leaves.begin(), leaves.end());   // Рамешва вектора от участници
		int interRoot = leaves.size() - 1;
		for (size_t i = 0; i < interRoot; i++)
			addNode(T());
		for (int i = 0; i < leaves.size(); i++)    // Запълва листата на дървото с участниците
				addNode(leaves[i]);
	}
	// задача 6
	vector<T> getParticipants() {
		vector<T> vec;
		bool* taken = new bool[numberOfLines()](); // Haмира броя на запълнените редове във файла
		int takenCount = 0;
		srand(time(NULL));
		int n = rand() % numberOfLines();  //  Избира random брои участници
		while (takenCount < n) {           // Избира random редове от файла
			int randLine = rand() % numberOfLines();
			if (!taken[randLine]) {
				taken[randLine] = true;
				takenCount++;
			}
			else { continue; }
		}
		int i = 0;
		Player line;
		ifstream myfile("participants.txt");
		if (myfile.is_open()) {
			while (myfile >> line) {    // Запълва vector от random избраните участници от файла
				if (taken[i])
					vec.push_back(line);
				i++;
			}
			myfile.close();
		}
		return vec;
	}
	// Задача 7
	void tournament(){
		int index = data.size() - 1;
		while (index > 1) {  
			int firstCoef = data[index--].coefficient;
			int secondCoef = data[index].coefficient;
			srand(time(NULL));
			int n = rand() % (firstCoef + secondCoef);  // Избира random число от 0 до сбора от коефициентите на 2-та участника
			if (n < firstCoef)                          // Ако числото е < от коефициента на 1-вия то той е победител и продължава напред 
				data[getParent(data[index+1])] = data[index + 1];
			else data[getParent(data[index])] = data[index];
			index--;
		}
	}
	// Задача 8
	void findpath(string name) {
		if (!data.size()) {
			cout << "Tree is empty!\n";
			return;
		}
		int i = data.size() - 1;
		while (data[i].name != name && i >= 0) {
			i--;
			if (i < 0) {
				cout << "There no player with that name\n";
				return;
			}
		}
		if (i == 0)return;
		int father = (i - 1) / 2;
		while (data[father].name == name) {    // Изкарва всички мачове които подаденият участник е спечелил
			if (father == 0) return;
			if (name == data[left[father]].name)
				cout << name << " - " << data[right[father]] << endl;
			else
				cout << data[left[father]] << " - " << name << endl;
			father = (father - 1) / 2;
			if (father == 0)break;
		}
		if (name == data[left[father]].name)    // Изкарва мача който е загубил или финала на турнира
			cout << name << " - " << data[right[father]] << endl;
		else
			cout << data[left[father]] << " - " << name << endl;
		cout << endl;
		return;
	}
	// Задача 9
	void allTogether(){
		vector<T> theVec = getParticipants();
		fillTree(theVec);
		tournament();
		cout << "Winner: " << data[0].name << endl;
		printLevels();
		cout << endl;
		string playerIn;
		cout << "Input Player: ";
		cin >> playerIn;
		findpath(playerIn);
	}
};

int main() {
	CBCT<Player> tr1;      // Task 9 (3 times) to show its all random 
	tr1.allTogether();
	CBCT<Player> tr2;
	tr2.allTogether();
	CBCT<Player> tr3;
	tr3.allTogether();
	cout << "Test General (Task 9)                    -- Success !\n";

	return 0;
}
