#include "Game.h"

#include <Core/Exceptions.h>

#include <iostream>

Game::Game()
: player(0), board(0)
{
}

void Game::newGame()
{
    board->newGame();
}

void Game::update()
{
    if(board==0 or player==0)
    {
        throw OpenEngine::Core::Exception("Invalid Game Setup");
    }
    player->update();
    board->update();

    if(board->isGameOver())
    {
        std::cout << "GAME IS OVER!" << std::endl;
        //board->newGame();
    }
}

void Game::seedPlayer(Player *p)
{
    player = p;
    if(board!=0)
    {
        player->seedBoard(board);
    }
}

void Game::unseedPlayer()
{
    player = 0;
}

void Game::seedBoard(Board *b)
{
    board = b;
    if(player!=0)
    {
        player->seedBoard(board);
    }
}

void Game::unseedBoard()
{
    board = 0;
}
