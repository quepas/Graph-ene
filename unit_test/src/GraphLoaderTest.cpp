#include <catch.hpp>

#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "GraphLoader.h"

using Graphene::AdjacencyListGraph;
using Graphene::AdjacencyMatrixGraph;
using Graphene::LoadGraph;

TEST_CASE("Loading graph into matrix-based graph structure") {
  SECTION("Loading small file") {
    AdjacencyMatrixGraph graph;
    LoadGraph("data/small_graph.txt", graph);

    REQUIRE(graph.GetNodeCount() == 20);
    REQUIRE(graph.GetEdgeCount() == 100);
  }

  SECTION("Loading big file") {
    AdjacencyMatrixGraph graph;
    LoadGraph("data/big_graph.txt", graph);

    REQUIRE(graph.GetNodeCount() == 1000);
    REQUIRE(graph.GetEdgeCount() == 100000);
  }
}

TEST_CASE("Loading graph into list-based graph structure") {
  SECTION("Loading small file") {
    AdjacencyListGraph graph;
    LoadGraph("data/small_graph.txt", graph);

    REQUIRE(graph.GetNodeCount() == 20);
    REQUIRE(graph.GetEdgeCount() == 100);
  }
  
  SECTION("Loading big file") {
    AdjacencyListGraph graph;
    LoadGraph("data/big_graph.txt", graph);

    REQUIRE(graph.GetNodeCount() == 1000);
    REQUIRE(graph.GetEdgeCount() == 100000);
  }
}
