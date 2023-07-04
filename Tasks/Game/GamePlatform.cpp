#pragma once
#include <iostream>
#include <fstream>
#include "GamePlatform.h"
#include "constants.h"

GamePlatform::GamePlatform()
{
	numGames = 0;
}

void GamePlatform::addGame(Game& newGame)
{
	if (numGames < MAX_GAMES)
	{
		games[numGames++] = newGame;
		std::cout << SUCCES_MSG << std:: endl;
	}
	else
	{
		std::cout << ERROR_MSG << std:: endl;
	}
}

const Game& GamePlatform::getGame(int index) const
{
	if (index >= 0 && index < numGames)
	{
		return games[index];
	}
	Game defaultGame("",0.0,0);
	return defaultGame;
}

int GamePlatform::getNumGames() const
{
	return numGames;
}

const Game& GamePlatform::getCheapestGame() const
{
	if (numGames == 0)
	{
		Game defaultGame("", 0.0, 0);;
		return defaultGame;
	}
	const Game* cheapestGame = &games[0];
	for (size_t i = 0; i < numGames; i++)
	{
		if (games[i].getPrice() < cheapestGame->getPrice())
		{
			cheapestGame = &games[i];
		}
	}
	return *cheapestGame;

	delete[] cheapestGame;
 }

const Game& GamePlatform::getMostExpensiveGame() const
{
	if (numGames == 0)
	{
		Game defaultGame("", 0.0, 0);
		return defaultGame;
	}

	const Game* mostExpensiveGame = &games[0];
	for (size_t i = 0; i < numGames; i++)
	{
		if (games[i].getPrice() > mostExpensiveGame->getPrice())
		{
			mostExpensiveGame = &games[i];
		}
	}

	return *mostExpensiveGame;
}

void GamePlatform::getFreeGames(Game* freeGames, int numFreeGames) const
{
	numFreeGames = 0;
	for (size_t i = 0; i < numGames; i++)
	{
		if (games[i].isFree()) {
			freeGames[numFreeGames] = games[i];
			numFreeGames++;
		}
	}
}

void GamePlatform::removeGame(int index)
{
	if (index >= 0 && index < numGames)
	{
		for (size_t i = index; i < numGames-1; i++)
		{
			games[i] = games[i + 1];
		}
		numGames--;
	}
}


void GamePlatform::saveToFile(const char* fileName) const
{
	std::ofstream out(fileName);
	if (!out.is_open())
	{
		std::cout << ERROR_MSG << std::endl;
		return;
	}

	for (int i = 0; i < numGames; i++)
	{
		out << i + 1 << ".";
		out << games[i] << std::endl;
	}
	out.close();
}

void GamePlatform::loadFromFile(const char* fileName) 
{
	std::ifstream in(fileName);
	if (!in.is_open()) 
	{
		std::cout << ERROR_MSG << std::endl;
		return;
	}

	int loadedNumGames;
	in >> loadedNumGames;
	for (int i = 0; i < loadedNumGames; i++)
	{
		Game loadedGame;
		in >> loadedGame;
		addGame(loadedGame);
	}
	in.close();
}