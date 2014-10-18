#include <catch.hpp>

#include "AdjacencyMatrixGraph.h"

using Graphene::AdjacencyMatrixGraph;

TEST_CASE("Basic graph manipulation") {
  SECTION("Adding and removing nodes") {
    AdjacencyMatrixGraph graph;

    REQUIRE(graph.GetNodeCount() == 0);
    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);
    graph.RemoveNode(1);
    graph.RemoveNode(4);
    REQUIRE(graph.GetNodeCount() == 2);
    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);
  }
}