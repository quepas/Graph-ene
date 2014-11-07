#pragma once

#include "BaseGraph.h"

namespace Graphene {

typedef std::vector<std::vector<int>> vector2d;

void Floyd_Warshall(const BaseGraph& graph, vector2d& dist, vector2d& predecessors);

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension);
void FillVector2d(vector2d& vector, int value);

}
// ~~ Graphene::GraphAlgorithm
