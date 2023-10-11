#ifndef A_STAR_H
#define A_STAR_H

#include <SFML/Graphics.hpp>
#include "nodes.h"
#include "global_planner.h"


class AStar : public global_planner::GlobalPlanner
{

    public:

        AStar(sf::RenderWindow* window, unsigned int rows, unsigned int cols, unsigned int cellSize);

        virtual bool plan(std::pair<int,int> start, std::pair<int,int> goal, std::vector<Node>& path , std::unordered_set<std::pair<int,int>, hashFunction> obstacles);

    private:
        sf::RenderWindow* window_;
        unsigned int rows_;
        unsigned int cols_;
        unsigned int cellSize_;

};


#endif