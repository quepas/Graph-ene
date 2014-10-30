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

  SECTION("Adding and removing edges") {
    AdjacencyMatrixGraph graph;

    graph.AddNode(1);
    graph.AddNode(2);
    graph.AddNode(3);
    REQUIRE(graph.GetNodeCount() == 3);

    graph.AddEdge(1, 3, 100);
    graph.AddEdge(2, 3, 150);
    REQUIRE(graph.GetNodeCount() == 3);
    REQUIRE(graph.GetEdgeCount() == 2);

    graph.RemoveEdge(1, 3);
    REQUIRE(graph.GetEdgeCount() == 1);
    graph.RemoveEdge(3, 1);
    REQUIRE(graph.GetEdgeCount() == 1);
  }
}