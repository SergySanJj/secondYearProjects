//
// Created by isara on 22-Apr-19.
//
#include "Graph.h"

#include "gtest/gtest.h"

#include <vector>
#include <string>



TEST(VertexTests, CreationAndAccess) {
    GraphTree::Vertex<int> v1;
    ASSERT_EQ(0, v1.data());

    GraphTree::Vertex<int> v2(11);
    ASSERT_EQ(11, v2.data());

    GraphTree::Vertex<int> v3(11);
    ASSERT_EQ(11, v3.data());
    ASSERT_TRUE(v2 == v3);

    v1 = v2;
    ASSERT_TRUE(v1 == v3);
}

template<typename T>
bool operator==(const std::set<T> &lhs, const std::set<T> &rhs) {
    for (auto &el:lhs) {
        if (rhs.find(el) == rhs.end())
            return false;
    }
    return true;
}

template<typename T>
::testing::AssertionResult VecEq(const std::vector<T> &v1, const std::vector<T> &v2) {
    if (v1.size() != v2.size())
        return ::testing::AssertionFailure();
    for (int i = 0; i < v1.size(); i++)
        if (v1[i] != v2[i])
            return ::testing::AssertionFailure();
    return ::testing::AssertionSuccess();
}

TEST(GraphTests, CreationAndDataAssignment) {
    // You can store any class/type in Graph datastruct unless it has:
    // -constructor
    // -destructor
    // -assignment operator

    // To work with Graph module use GraphTree namespace.
    // Then create graph object with 0 vertexes that stores int values by:
    GraphTree::Graph<int> g1(0);
    std::vector<GraphTree::Vertex<int>> v1 = {};
    // To get number of vertexes use:
    ASSERT_EQ(0, g1.size());
    // To get number of edges use:
    ASSERT_EQ(0, g1.edgeCount());
    EXPECT_TRUE(VecEq(v1, g1.getVertexList()));

    // If you want to crate graph object with n=5 vertexes:
    GraphTree::Graph<int> g2(5);
    std::vector<GraphTree::Vertex<int>> v2(5);
    ASSERT_EQ(5, g2.size());
    ASSERT_EQ(0, g2.edgeCount());
    EXPECT_TRUE(VecEq(v2, g2.getVertexList()));

    // To initialize new graph object with values from vector use:
    GraphTree::Graph<int> g3({1, 2, 3});
    std::vector<GraphTree::Vertex<int>> v3 = {GraphTree::Vertex(1),
                                              GraphTree::Vertex(2),
                                              GraphTree::Vertex(3)};
    ASSERT_EQ(3, g3.size());
    ASSERT_EQ(0, g3.edgeCount());
    EXPECT_TRUE(VecEq(v3, g3.getVertexList()));
    ASSERT_EQ(2, g3[1].data());

    g3.addVertex(GraphTree::Vertex(4));
    v3.push_back(GraphTree::Vertex(4));
    ASSERT_EQ(4, g3.size());
    ASSERT_EQ(0, g3.edgeCount());
    EXPECT_TRUE(VecEq(v3, g3.getVertexList()));
    ASSERT_EQ(4, g3[3].data());

    // To change value stored in v vertex (numeration from 0) use:
    g3[3] = 100;
    ASSERT_EQ(100, g3[3].data());

    ASSERT_THROW(g3[100500], std::range_error);
}

TEST(GraphTests, EdgeCreation) {
    GraphTree::Graph<std::string> g1(5);
    ASSERT_EQ(0, g1.edgeCount());

    g1.addEdge(0, 4);
    ASSERT_EQ(1, g1.edgeCount());
    ASSERT_TRUE(g1.areConnected(0, 4));

    std::vector<std::set<std::size_t>> adj = {{4},
                                              {},
                                              {},
                                              {},
                                              {0}};
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));

    // Graph class doesn't support multiedges or loops
    g1.addEdge(0, 4);
    g1.addEdge(0, 0);
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));

    g1.addEdge(0, 1);
    g1.addEdge(3, 1);
    adj = {{4, 1},
           {0, 3},
           {},
           {1},
           {0}};
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));

    auto g2 = g1;
    ASSERT_TRUE(VecEq(adj, g2.getAdjacencyList()));
}

TEST(GraphTests, SpanningTreeLine) {
    GraphTree::Graph<int> g1(5);
    // Line graph
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    std::vector<std::set<std::size_t>> adj = {{1},
                                              {0, 2},
                                              {1, 3},
                                              {2, 4},
                                              {3}};
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));

    g1 = g1.getSpanningTree();
    // Spanning tree invariant: spanning tree graph with n vert will have n-1 edges
    ASSERT_EQ(g1.size() - 1, g1.edgeCount());
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));
}

TEST(GraphTests, SpanningTreeK5) {
    GraphTree::Graph<int> g1(5);
    // Line graph
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            // we can't create multiedges and loops so everything is Ok
            g1.addEdge(i, j);
        }
    }
    std::vector<std::set<std::size_t>> adj = {{1, 2, 3, 4},
                                              {0, 2, 3, 4},
                                              {0, 1, 3, 4},
                                              {0, 1, 2, 4},
                                              {0, 1, 2, 3}};
    ASSERT_TRUE(VecEq(adj, g1.getAdjacencyList()));

    g1 = g1.getSpanningTree();
    // Spanning tree invariant: spanning tree graph with n vert will have n-1 edges
    ASSERT_EQ(g1.size() - 1, g1.edgeCount());
}