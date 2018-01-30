//#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;

struct Player2
{
	string name;
	int coefficient;
	Player2() {
		name = " ";
		coefficient = -1;
	}
	friend ostream& operator<<(ostream& os, const Player2 &pl) {
		if (pl.coefficient != -1)
			os << pl.name ;
		else os << "-|-";
		return os;
	}
	friend istream& operator>>(istream& is, Player2 & pl) {
		is >> pl.name >> pl.coefficient;
		return is;
	}
};

template<typename T>
class TreeFathers      // Complete Binary Тree Fathers List
{
	vector<T> info;
	vector<int> fathers;
	int numberOfLines() {     // Намира броя на редовете в файл, помощтна за задача 6
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
	TreeFathers() {           // Default конструктор
		fathers.push_back(-2);
	}
	TreeFathers(const TreeFathers<T>& tr){           // Copy конструктор
		for (int i = 0; i< tr.fathers.size(); i++) {
			info[i] = tr.info[i];
			fathers[i] = tr.fathers[i];
		}
	}
	TreeFathers& operator=(const TreeFathers& tr){   // Predefined operator =
		if (this != &tr) {
			info.clear();
			father.clear();
			for (int i = 0; i< tr.fathers.size(); i++) {
				info[i] = tr.info[i];
				fathers[i] = tr.fathers[i];
			}
		}
		return *this;
	}
	bool empty() const { return fathers[0] == -2; }  // Проверява дали дървото е празно
	T getRoot() const{    // Връща корена
		if (empty()) cout << "The tree is empty!\n";
		else return info[0];
	}
	T getFather(const T& child){   // Връща бащата на подаден елемент
		if (!empty()) {
			if (child == info[0]) 
				cout << "The child( " << child << " ) is the root of the tree and has no father!\n";
			else {
				for (int i = 1; i < fathers.size(); i++) {
					if (child == info[i])
						return info[fathers[i]];
				}
				cout << "The child( " << child << " ) has no father and is not in the tree!\n";
			}
		}
		else cout << "The tree is empty, there are no father!\n";
		return T();
	}
	void addNode(const T& elem){    // Добавя елемент на правилната позиция към дървото
		info.push_back(elem);
		if (empty()) fathers[0] = -1;
		else fathers.push_back((fathers.size()-1) / 2);
	}
	void fathersIndex(){ // Извежда индексите на бащите
		for (int i = 0; i < fathers.size(); i++)
			cout << fathers[i] << "  ";
		cout << endl;
	}
	void printInfo(){  // Извежда елементите в редица 
		for (int i = 0; i < info.size(); i++)
			cout << info[i] << '\t';
		cout << endl;
	}
	void print(){  // Извежда дурвото на нива
		int size = info.size() - 1;
		int from = 0, to = 0;
		while (from<size){
			if (to > size)to = size ;
			for (int i = from; i <= to; i++)
				cout << info[i] << "    ";
			cout << endl;
			from *= 2; from += 1;
			to *= 2; to += 2;
		}
		cout << endl;
	}
	// Задача 5
	void fillTree(vector<T> leaves){
		srand(unsigned(time(0)));
		random_shuffle(leaves.begin(), leaves.end());  // Рамешва вектора от участници
		int interRoot = leaves.size() - 1;
		for (size_t i = 0; i < interRoot; i++)
			addNode(T());
		for (int i = 0; i < leaves.size(); i++) // Запълва листата на дървото с участниците
			addNode(leaves[i]);
	}
	// Задача 6
	vector<T> getParticipants() {
		vector<T> vec;
		bool* taken = new bool[numberOfLines()]();  // Haмира броя на запълнените редове във файла
		int takenCount = 0;
		srand(time(NULL));
		int n = rand() % numberOfLines();   //  Избира random брои участници
		while (takenCount < n) {    // Избира random редове от файла
			int randLine = rand() % numberOfLines();
			if (!taken[randLine]) {
				taken[randLine] = true;
				takenCount++;
			}
			else { continue; }
		}
		int i = 0;
		Player2 line;
		ifstream myfile("participants.txt");
		if (myfile.is_open()){   
			while (myfile >> line){     // Запълва vector от random избраните участници от файла
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
		int index = fathers.size()-1;
		while (index > 1) {
			int firstCoef = info[index--].coefficient;
			int secondCoef = info[index].coefficient;
			srand(time(NULL));
			int n = rand() % (firstCoef+secondCoef);  // Избира random число от 0 до сбора от коефициентите на 2-та участника
			if (n < firstCoef)                       // Ако числото е < от коефициента на 1-вия то той е победител и продължава напред
				info[fathers[index]] = info[index + 1];
			else info[fathers[index]] = info[index];
			index--;
		}
	}
	// Задача 8
	void findpath(string name) {
		if (empty()) {
			cout << "Tree is empty!\n";
			return;
		}
		int i = info.size()-1;
		while (info[i].name != name && i >= 0) {
			i--;
			if (i < 0) {
				cout << "There no player with that name\n";
				return;
			}
		}
		while (info[fathers[i]].name == name) {     // Изкарва всички мачове които подаденият участник е спечелил
			if (name == info[fathers[i] * 2 + 1].name) 
				cout << name << " - " << info[fathers[i] * 2 + 2] << endl;
			else 
				cout << info[fathers[i] * 2 + 1] << " - " << name << endl;
			i = fathers[i];
			if (i == 0)break;
		}
		if (i == 0) return;
		if (name == info[fathers[i] * 2 + 1].name)    // Изкарва мача който е загубил или финала на турнира
			cout << name << " - " << info[fathers[i] * 2 + 2] << endl;
		else 
			cout << info[fathers[i] * 2 + 1] << " - " << name << endl;
		return;
	}
	// Задача 9
	void allTogether(){
		vector<T> theVec = getParticipants();
		fillTree(theVec);
		tournament();
		cout << "Winner: " << getRoot() << endl;
		print();
		string playerIn;
		cout << "Input Player: ";
		cin >> playerIn;
		findpath(playerIn);
		cout << endl;
	}
};

int main(){
	TreeFathers<Player2> trf1;  // Task 9 (3 times) to show its all random  
	trf1.allTogether();
	TreeFathers<Player2> trf2;
	trf2.allTogether();
	TreeFathers<Player2> trf3;
	trf3.allTogether();
	cout << "Test General (Task 9)                    -- Success !\n";

	TreeFathers<Player2> tr;
	tr.print();

	Player2 pl1, pl2, pl3;
	pl1.name = "Mike";
	pl1.coefficient = 10;
	pl2.name = "Jerry";
	pl2.coefficient = 20;
	pl3.name = "Danni";
	pl3.coefficient = 30;
	TreeFathers<Player2> tr1;
	tr1.addNode(pl1);
	tr1.addNode(pl2);
	tr1.addNode(pl3);
	tr1.print();
	cout << "Test 1 (AddNode, print)	-- Success !\n";
	tr1.printInfo();
	cout << "Test 2 (Vector of elements)	-- Success !\n";
	tr1.fathersIndex();
	cout << "Test 3 (Vector of index of fathers)	-- Success !\n";

	cout << tr1.getRoot() << endl;
	cout << "Test 4 (getRoot)	-- Success !\n";

	if (!tr1.empty()) cout << "Test 5 (empty)	-- Success !\n";
	return 0;
}