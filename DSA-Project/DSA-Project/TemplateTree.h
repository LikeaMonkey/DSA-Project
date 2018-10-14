#pragma once

#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>

#include "Player.h"

#define FILE_NAME "participants.txt"

template<class T>
class Tree
{
public:
	virtual void AddNode(const T& elem) = 0;
	virtual const T& GetRoot() const noexcept = 0;
	virtual void Print() const noexcept = 0;
	// Task 7
	virtual void Tournament() = 0;
	// Task 8
	virtual void Findpath(const std::string& name) const noexcept = 0;

	// Task 5
	void FillTree(std::vector<T> leaves)
	{
		srand(static_cast<unsigned>(time(0)));
		random_shuffle(leaves.begin(), leaves.end());
		size_t leavesSize = leaves.size();
		for (size_t i = 0; i < leavesSize - 1; ++i)
		{
			AddNode(T());
		}

		for (size_t i = 0; i < leavesSize; ++i)
		{
			AddNode(leaves[i]);
		}
	}

	// Task 9
	void AllTogether()
	{
		FillTree(getParticipants());
		Tournament();
		Print();
		std::cout << "\nThe winner is: " << GetRoot() << '\n';
		std::string name;
		std::cout << "Enter player: ";
		std::cin >> name;
		Findpath(name);
		std::cout << '\n';
	}

protected:
	int numberOfLines() const noexcept
	{
		FILE *fd = NULL;
		int num = 0;
		char ch;
		fd = fopen(FILE_NAME, "r");
		if (fd == NULL)
		{
			perror(FILE_NAME);
			return 0;
		}

		while (EOF != (ch = fgetc(fd)))
		{
			if (ch == '\n')
				++num;
		}

		fclose(fd);

		return num;
	}

	// Task 6
	std::vector<T> getParticipants() const noexcept
	{
		int numLines = numberOfLines();
		bool taken[32];
		for (int i = 0; i < numLines; ++i)
			taken[i] = false;

		srand(static_cast<unsigned>(time(0)));
		int randomLines = rand() % numLines;
		for (int takenCount = 0; takenCount < randomLines;)
		{
			int randLine = rand() % numLines;
			if (taken[randLine] == false)
			{
				taken[randLine] = true;
				++takenCount;
			}
		}

		std::ifstream myfile(FILE_NAME);
		std::vector<T> participants;
		if (myfile.is_open())
		{
			int i = 0;
			Player line;
			while (myfile >> line)
			{
				if (taken[i])
					participants.push_back(line);
				++i;
			}

			myfile.close();
		}

		return std::move(participants);
	}
};