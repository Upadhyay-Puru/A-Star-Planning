#ifndef GLOBAL_PLANNER_H
#define GLOBAL_PLANNER_H

#include <unordered_set>
#include "nodes.h"
#include "map.h"
namespace global_planner
{
    class GlobalPlanner
    {
        public:

            GlobalPlanner(int nx, int ny);

            virtual ~GlobalPlanner() = default;

            virtual bool plan(std::pair<int,int> start, std::pair<int,int> goal, std::vector<Node>& path , std::unordered_set<std::pair<int,int>, hashFunction> obstacles) = 0;

            std::vector<Node> getMotion();

            double dist(const Node& node1, const Node& node2);

            double angle(const Node& node1, const Node& node2);

            int grid2Index(int x, int y);

        protected:

            std::vector<Node> _convertClosedListToPath(std::unordered_set<Node, NodeIdAsHash, compare_coordinates>& closed_list,
                                             const Node& start, const Node& goal);

            int nx_, ny_, ns_;
    };
}

#endif