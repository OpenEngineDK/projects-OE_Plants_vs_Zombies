#ifndef _OE_PLANTS_BOARD_CLASS_H_
#define _OE_PLANTS_BOARD_CLASS_H_

#include <string>
#include <vector>

#include "Plant.h"
#include "Zombie.h"
#include "Pea.h"
#include "Listener.h"

class Board
{
    //---------
    //Functions
    public:
        Board();
        Board(unsigned int x, unsigned int y);

        // Update the board
        void update();

        // Restart the game
        void newGame();

        // Return the number of lines
        unsigned int numLines() const;
        unsigned int numColumns() const;

        // Return plant board
        const std::vector<Plant*> getPlantBoard() const;
        const std::vector<Plant*> getPlantLine(unsigned int line) const;
        const Plant* getPlant(unsigned int line, unsigned int id) const;

        // Return zombie board
        const std::vector<Zombie*> getZombieBoard() const;
        const std::vector<Zombie*> getZombieLine(unsigned int line) const;

        // Return pea board
        const std::vector<Pea*> getPeaBoard() const;
        const std::vector<Pea*> getPeaLine(unsigned int line) const;

        unsigned int numPlantsTotal() const;
        unsigned int numPlants(unsigned int line) const;

        unsigned int numZombiesTotal() const;
        unsigned int numZombies(unsigned int line) const;

        // Return the peas board
        unsigned int numPeasTotal() const;
        unsigned int numPeas(unsigned int line) const;

        // Check if the game is over
        bool isGameOver();

        // Parse the entered move.
        // Return true if valid, false otherwise */ 
        bool parse_move(std::string s);
        // Execute a valid move.
        bool make_move(std::string s);

        void addValidPlant(Plant *p);

        void addZombie(Zombie *z);
        void addListener(Listener *l);
    private:
        bool setPlant(Plant *p);

        int regex_check_move(std::string s);
        bool hitting(float x1, float y1, float x2, float y2, float min_distance);
    protected:
    //---------
    //Variables
    public:
    private:
        // Map size
        unsigned int x, y;
        // A vector representing the squares
        // (Map size, where each can possibly hold a plant).
        // That is a vector of lines, which each hold a number of squares
        std::vector<Plant*> board;
        std::vector<Plant*> valid_plants;
        // The Zombies and Peas on this map
        std::vector<Zombie*> zombies;
        std::vector<Pea*> peas;
        // A vector of listeners
        std::vector<Listener*> listeners;
    protected:
};

#endif //_OE_PLANTS_BOARD_CLASS_H_
