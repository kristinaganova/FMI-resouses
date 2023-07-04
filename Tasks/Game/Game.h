#pragma once

#include <iostream>

class Game {
private:
    bool isAvailable;
    char* title;
    double price;
public:
    Game();
    Game(const char* title, double price, bool isAvailable);
    Game(const Game& other);
    Game& operator=(const Game& other);
    ~Game();

    const char* getTitle() const;
    double getPrice() const;
    bool getIsAvailable() const;

    void setTitle(const char* title);
    void setPrice(double price);
    void setIsAvailable(bool isAvailable);

    bool isFree() const;
    void print() const;

    friend std::istream& operator>>(std::istream& in, Game& game);
    friend std::ostream& operator<<(std::ostream& out, const Game& game);
};

std::istream& operator>>(std::istream& in, Game& game);
std::ostream& operator<<(std::ostream& out, const Game& game);