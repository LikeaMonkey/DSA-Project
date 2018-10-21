#pragma once

#include <string>
#include <fstream>

struct Player
{
	std::string name;
	int coefficient;

	Player() : coefficient(-1) {}
	Player(const std::string& _name, int coef) : name(_name), coefficient(coef){}
	Player(const Player& other) = default;
	Player& operator=(const Player& other) = default;

	Player(Player&& other) noexcept
	{
		name = std::move(other.name);
		coefficient = other.coefficient;
	}

	Player& operator=(Player&& other) noexcept
	{
		name = std::move(other.name);
		coefficient = other.coefficient;

		return *this;
	}

	bool operator==(const Player& pl) const noexcept
	{
		return (name == pl.name && coefficient == pl.coefficient);
	}

	friend std::ostream& operator<<(std::ostream& os, const Player& pl)
	{
		os << ((pl.coefficient != -1) ? pl.name : "-|-");
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Player& pl)
	{
		is >> pl.name >> pl.coefficient;
		return is;
	}
};