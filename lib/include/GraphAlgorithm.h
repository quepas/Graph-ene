#pragma once

#include "BaseGraph.h"

namespace Graphene {

typedef std::vector<std::vector<int>> vector2d;

void Floyd_Warshall(const BaseGraph& graph, vector2d& dist, vector2d& predecessors);
void Bellman_Ford(const BaseGraph& graph, std::vector<int>& distances_vec, std::vector<int>& predecessors, unsigned source);
int Ford_Fulkerson(const BaseGraph& graph, unsigned source, unsigned target);

void FindFirstPathBFS(const BaseGraph& graph, unsigned source, unsigned target, std::vector<Edge>& path);
void RetrivePathFromBFS(int*& parents, int start, int end, std::vector<unsigned>& path);
void PathToEdgePath(const BaseGraph& graph, const std::vector<unsigned>& path, std::vector<Edge>& out_path);

void ResizeVector2d(vector2d& vector, unsigned first_dimension, unsigned second_dimension);
template<typename T>
void Initialize2DArray(T**& array, unsigned size, T value)
{
  array = new T*[size];
  for (unsigned i = 0; i < size; ++i) {
    array[i] = new T[size];
  }
  for (unsigned i = 0; i < size; ++i) {
    for (unsigned j = 0; j < size; ++j) {
      array[i][j] = value;
    }
  }
}

template<typename T>
void Delete2DArray(T**& array, unsigned size) {
  for (unsigned i = 0; i < size; ++i) {
    delete [] array[i];
  }
  delete [] array;
}

}
// ~~ Graphene::GraphAlgorithm
