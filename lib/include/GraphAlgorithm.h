#pragma once

#include "BaseGraph.h"

namespace Graphene {

typedef std::vector<std::vector<int>> vector2d;

void Floyd_Warshall(const BaseGraph& graph, vector2d& dist, vector2d& predecessors);
void Bellman_Ford(const BaseGraph& graph, std::vector<int>& distances_vec, std::vector<int>& predecessors, unsigned source);
void Ford_Fulkerson(const BaseGraph& graph, unsigned source, unsigned target, unsigned**& capacity, unsigned**& floating);

void Breadth_First_Search(const BaseGraph& graph, unsigned source, int*& parents);
void FindBFSPath(int*& parents, int start, int end, std::vector<unsigned>& path);

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension);

}
// ~~ Graphene::GraphAlgorithm
