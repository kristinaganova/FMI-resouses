#pragma once
#include "Game.h"
#pragma warning (disable:4996)

Game::Game() : isAvailable(false), title(nullptr), price(0.0) {}

Game::Game(const char* title, double price, bool isAvailable)
    : isAvailable(isAvailable), title(nullptr), price(price) 
{
    setTitle(title);
}

Game::Game(const Game& other)
    : isAvailable(other.isAvailable), title(nullptr), price(other.price) 
{
    setTitle(other.title);
}

Game& Game::operator=(const Game& other) 
{
    if (this != &other) {
        setIsAvailable(other.isAvailable);
        setPrice(other.price);
        setTitle(other.title);
    }
    return *this;
}

Game::~Game() 
{
    delete[] title;
}

const char* Game::getTitle() const 
{
    return title;
}

double Game::getPrice() const 
{
    return price;
}

bool Game::getIsAvailable() const
{
    return isAvailable;
}

void Game::setTitle(const char* title) 
{
    delete[] this->title;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
}

void Game::setPrice(double price)
{
    this->price = price;
}

void Game::setIsAvailable(bool isAvailable) 
{
    this->isAvailable = isAvailable;
}

bool Game::isFree() const 
{
    return price == 0.0;
}

void Game::print() const
{
    std::cout << "Title: " << getTitle() << ", Price: " << getPrice() << ", Available: " << std::boolalpha << getIsAvailable() << std::endl;
}

std::istream& operator>>(std::istream& in, Game& game) 
{
    char title[100];
    double price;
    bool isAvailable;

    in >> title;
    in >> price;
    in >> isAvailable;

    game.setTitle(title);
    game.setPrice(price);
    game.setIsAvailable(isAvailable);

    return in;
}

std:: ostream& operator<<(std::ostream& out, const Game& game) 
{
    out << "Title: " << game.getTitle() << ", Price: " << game.getPrice() << ", Available: " << std::boolalpha << game.getIsAvailable();
    return out;
}

