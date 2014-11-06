#include "AdjacencyListGraph.h"

using std::size_t;
using std::vector;

namespace Graphene {

bool AdjacencyListGraph::AddNode(unsigned node)
{
  return false;
}

bool AdjacencyListGraph::RemoveNode(unsigned node)
{
  return false;
}

bool AdjacencyListGraph::AddEdge(unsigned base_node, unsigned target_node, int weight)
{
  return false;
}

bool AdjacencyListGraph::RemoveEdge(unsigned base_node, unsigned target_node)
{
  return false;
}

vector<unsigned> AdjacencyListGraph::GetAdjacentNodes(unsigned node) const
{
  return vector<unsigned>();
}

vector<Edge> AdjacencyListGraph::GetIncidentEdges(unsigned node) const
{
  return vector<Edge>();
}

int AdjacencyListGraph::GetEdgeValue(unsigned base_node, unsigned target_node) const
{
  return -1;
}

size_t AdjacencyListGraph::GetEdgeCount() const
{
  return -1;
}

size_t AdjacencyListGraph::GetNodeCount() const
{
  return -1;
}

bool AdjacencyListGraph::IsNodeExsist(unsigned node) const
{
  return false;
}

bool AdjacencyListGraph::IsEdgeExsist(unsigned base_node, unsigned target_node) const
{
  return false;
}

}
// ~~ Graphene::AdjacencyListGraph
