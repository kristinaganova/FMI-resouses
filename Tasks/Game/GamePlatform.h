#pragma once
#include "Game.h"
#include "constants.h"

class GamePlatform {

private:
    Game games[MAX_GAMES];
    int numGames;

    //void swapGames(int index1, int index2);
public:
    GamePlatform();

    void addGame( Game& game);
    const Game& getGame(int index) const;
    int getNumGames() const;
    const Game& getCheapestGame() const;
    const Game& getMostExpensiveGame() const;
    void getFreeGames(Game* games, int numFreeGames) const;
    void removeGame(int index);
    void saveToFile(const char* fileName) const;
    void loadFromFile(const char* fileName);

};