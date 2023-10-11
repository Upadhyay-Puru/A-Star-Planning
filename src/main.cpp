#include <iostream>

#include <SFML/Graphics.hpp>
#include "map.h"
#include "a_star.h"

int main()
{
    
    unsigned int rows = 20;
    unsigned int cols = 30;

    unsigned int cellSize = 40;

    sf::RenderWindow window(sf::VideoMode(cols * cellSize, rows * cellSize), "SFML Grid");

    Map map(&window, rows, cols, cellSize);


    AStar planner(&window, rows, cols, cellSize);

    std::pair<int,int> start = map.get_start();
    std::pair<int,int> goal = map.get_goal();

    std::vector<Node> path;

    auto obstacles = map.get_obstalces();
    planner.plan(start, goal, path, obstacles);

    std::cout<<"Path Length: "<<path.size()<<std::endl;

    for(auto node : path)
    {
        sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
        cell.setPosition(node.x_ * cellSize,  node.y_ * cellSize);
        cell.setFillColor(sf::Color::Yellow);
        window.draw(cell);
    }

    window.display();
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
    }

}