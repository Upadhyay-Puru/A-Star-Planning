#include "map.h"
#include <iostream>


Map::Map(sf::RenderWindow* window, unsigned int rows, unsigned int cols, unsigned int cellSize)
    :  window_(window) ,rows_(rows), cols_(cols), cellSize_(cellSize)
{
    setupEnv();
}

bool Map::createNewEnv()
{
    bool res = setupEnv();

    return res;
}

bool Map::setupEnv()
{
    std::cout<<"Choose Star Location and press Enter"<<std::endl;
    bool closeLoop = false;
    while (!closeLoop) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
                closeLoop = true;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Get the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

                // Determine which cell was clicked
                int col = mousePos.x / cellSize_;
                int row = mousePos.y / cellSize_;

                if (col >= 0 && col < cols_ && row >= 0 && row < rows_) {
                    start_ = {col,row};
                    isStartInitialized_ = true;
                }
            }
        }

        draw();
    }

    std::cout<<"Choose goal position and press enter"<<std::endl;

    closeLoop = false;
    while (!closeLoop) {
        sf::Event event;
        while (window_->pollEvent(event)) {
            if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
                closeLoop = true;

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Get the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

                // Determine which cell was clicked
                int col = mousePos.x / cellSize_;
                int row = mousePos.y / cellSize_;

                if (col >= 0 && col < cols_ && row >= 0 && row < rows_) {
                    goal_ = {col,row};
                    isGoalInitialized_ = true;
                }
            }
        }

        draw();
    }

    std::cout<<"Setup Obstacles and press enter"<<std::endl;

    closeLoop = false;
    while(!closeLoop)
    {
        sf::Event event;
        while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
                closeLoop = true;

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
                // Get the mouse position
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window_);

                // Determine which cell was clicked
                int col = mousePos.x / cellSize_;
                int row = mousePos.y / cellSize_;

                if (col >= 0 && col < cols_ && row >= 0 && row < rows_) {
                    obstacle_list_.insert({col,row});
                    isObstacleInitialized_ = true;
                }
        }
        }
        draw();
    }
    return true;
}

void Map::draw()
{
    window_->clear(sf::Color::White);

    for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
        sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
        cell.setPosition(j * cellSize_, i * cellSize_);

        cell.setOutlineColor(sf::Color::Black);
        cell.setOutlineThickness(1);
        cell.setFillColor(sf::Color::Transparent);

        window_->draw(cell);
        }
    }

    if(isStartInitialized_)
    {
        sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
        cell.setPosition(start_.first * cellSize_, start_.second * cellSize_);
        cell.setFillColor(sf::Color::Green);
        window_->draw(cell);
    }

    if(isGoalInitialized_)
    {
        sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
        cell.setPosition(goal_.first * cellSize_, goal_.second * cellSize_);
        cell.setFillColor(sf::Color::Red);
        window_->draw(cell);
    }

    if(isObstacleInitialized_)
    {
        for(auto obstacle : obstacle_list_)
        {
            sf::RectangleShape cell(sf::Vector2f(cellSize_, cellSize_));
            cell.setPosition(obstacle.first * cellSize_, obstacle.second * cellSize_);
            cell.setFillColor(sf::Color::Black);
            window_->draw(cell);
        }
    }
    window_->display();
}

std::pair<int,int> Map::get_start()
{
    return start_;
}

std::pair<int,int> Map::get_goal()
{
    return goal_;
}

std::unordered_set<std::pair<int,int>, hashFunction> Map::get_obstalces()
{
    return obstacle_list_;
}
