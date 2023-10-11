#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>

struct hashFunction 
{ 
  size_t operator()(const std::pair<int ,  
                    int> &x) const
  { 
    return x.first ^ x.second; 
  } 
}; 

class Map
{
    public:

        Map(sf::RenderWindow* window, unsigned int rows, unsigned int cols, unsigned int cellSize);

        bool createNewEnv();

      std::pair<int,int> get_start();

      std::pair<int,int> get_goal();

      std::unordered_set<std::pair<int,int>, hashFunction> get_obstalces();

      void draw();
    private:

        bool setupEnv();

        unsigned int rows_;
        unsigned int cols_;
        unsigned int cellSize_;
        sf::RenderWindow* window_;
        bool initialized_;

        std::pair<int,int> start_;
        std::pair<int,int> goal_;
        std::unordered_set<std::pair<int,int>, hashFunction> obstacle_list_;

        bool isStartInitialized_{false};
        bool isGoalInitialized_{false};
        bool isObstacleInitialized_{false};
    
};

#endif