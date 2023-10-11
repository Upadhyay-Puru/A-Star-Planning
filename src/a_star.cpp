#include "a_star.h"
#include "map.h"
#include <queue>
AStar::AStar(sf::RenderWindow* window, unsigned int rows, unsigned int cols, unsigned int cellSize)
    : window_(window), rows_(rows), cols_(cols), global_planner::GlobalPlanner(cols, rows)
{

}

bool AStar::plan(std::pair<int,int> start, std::pair<int,int> goal, std::vector<Node>& path, std::unordered_set<std::pair<int,int>, hashFunction> obstacles)
{

    Node start_node(start.first, start.second, 0, 0, grid2Index(start.first, start.second), 0);
    Node goal_node(goal.first, goal.second, 0, 0, grid2Index(goal.first, goal.second), 0);

    path.clear();

    std::priority_queue<Node, std::vector<Node>, compare_cost> open_list;
    std::unordered_set<Node, NodeIdAsHash, compare_coordinates> closed_list;

    open_list.push(start_node);

    const std::vector<Node> motion = getMotion();

    while(!open_list.empty())
    {
        Node current = open_list.top();
        // std::cout<<current.x_<<" "<<current.y_<<std::endl;
        // std::cout<<"---"<<std::endl;
        open_list.pop();

        if (closed_list.find(current) != closed_list.end())
            continue;
        
        closed_list.insert(current);

        if (current == goal_node)
        {
            path = _convertClosedListToPath(closed_list, start_node, goal_node);
            return true;
        }

        for (const auto& m : motion)
        {
            Node node_new = current + m;

            if (closed_list.find(node_new) != closed_list.end())
                continue;

            node_new.id_ = grid2Index(node_new.x_, node_new.y_);
            node_new.pid_ = current.id_;


            if ((node_new.id_ < 0) || (node_new.id_ >= ns_) ||  obstacles.find({node_new.x_, node_new.y_}) != obstacles.end() )
                continue;

            node_new.h_ = dist(node_new, goal_node);
            // std::cout<<node_new.x_<<" "<<node_new.y_<<std::endl;
            open_list.push(node_new);
        }

}
return true;
}
