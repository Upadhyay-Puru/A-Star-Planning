#include "global_planner.h"

namespace global_planner
{
    GlobalPlanner::GlobalPlanner(int nx, int ny)
    {
        nx_ = nx;
        ny_ = ny;
        ns_ = nx * ny;
    }

    int GlobalPlanner::grid2Index(int x, int y)
    {
        return x + nx_ * y;
    }

    std::vector<Node> GlobalPlanner::getMotion()
    {
        return { Node(0, 1, 1),
                Node(1, 0, 1),
                Node(0, -1, 1),
                Node(-1, 0, 1),
                Node(1, 1, std::sqrt(2)),
                Node(1, -1, std::sqrt(2)),
                Node(-1, 1, std::sqrt(2)),
                Node(-1, -1, std::sqrt(2)) };
    }

    double GlobalPlanner::dist(const Node& node1, const Node& node2)
    {
        return std::hypot(node1.x_ - node2.x_, node1.y_ - node2.y_);
    }

    double GlobalPlanner::angle(const Node& node1, const Node& node2)
    {
        return atan2(node2.y_ - node1.y_, node2.x_ - node1.x_);
    }

    std::vector<Node> GlobalPlanner::_convertClosedListToPath(
                    std::unordered_set<Node, NodeIdAsHash, compare_coordinates>& closed_list, const Node& start, const Node& goal)
    {
        auto current = *closed_list.find(goal);
        
        std::vector<Node> path;
        while (current != start)
        {
            path.push_back(current);
            auto it = closed_list.find(Node(current.pid_ % nx_, current.pid_ / nx_, 0, 0, current.pid_));
            if (it != closed_list.end())
            current = *it;
            else
            return {};
        }
        path.push_back(start);

        return path;
    }
}