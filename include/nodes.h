#ifndef NODES_H
#define NODES_H

#include <cmath>
#include <array>
#include <vector>
#include <map>


class Node
{
    public:
        Node(int x = 0, int y = 0, double g = 0.0, double h = 0.0, int id = 0, int pid = 0);
        Node operator+(const Node& n) const;
        Node operator-(const Node& n) const;
        bool operator==(const Node& n) const;
        bool operator!=(const Node& n) const;

        int x_, y_;
        double g_,h_;
        int id_, pid_;
};

class NodeIdAsHash
{
    public:
        size_t operator()(const Node& n) const;
};

struct compare_cost
{
    bool operator()(const Node& n1, const Node& n2) const;
};

struct compare_coordinates
{
    bool operator()(const Node& n1, const Node& n2) const;
};

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

#endif