//
// Graph module
// Created by sergysanjj on 19.09.18.
//

#ifndef GRAPHTREE_GRAPH_H
#define GRAPHTREE_GRAPH_H

#include <cstdlib>
#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <iomanip>
#include <memory>
#include <stack>


namespace GraphTree {

    template<typename T>
    class Vertex {
    public:
        Vertex<T>() : vertexData() {}

        explicit Vertex<T>(T data) : vertexData(data) {}

        ~Vertex<T>() = default;

        Vertex &operator=(const Vertex<T> &rsv);

        Vertex &operator=(const T &value);

        T &accessData();

    private:
        T vertexData;
    };


    template<typename T>
    class Graph {
    public:

        // Create an empty graph with n vertices.
        explicit Graph(std::size_t n);

        // Create an empty graph.
        explicit Graph() : N(0), E(0) {}

        // Create graph with data in vertices from values vector.
        explicit Graph(const std::vector<T> &values);

        // As we don't store any heap data.
        ~Graph() = default;

        // Gives access to data inside index vertex.
        T &operator[](std::size_t index);

        // Assignment operator.
        Graph &operator=(const Graph<T> &rhs);

        // Returns number of vertices.
        std::size_t size() const { return N; }

        // Returns number of edges.
        std::size_t edgeCount() const { return E; }

        // Print adjacency list with numeration. (any derived class can reimplement)
        void print() const;

        // Print adjacency list with data in form defined by op function.
        template<typename OP>
        void print(OP op);

        // Adds new vertex. Call as .addVertex(Vertex(data));
        void addVertex(const Vertex<T> &v);

        // Connect u with v (numeration from 0, DOESN'T supports multiedges and loops).
        void addEdge(std::size_t u, std::size_t v);

        // Returns by value new graph that contains Spanning Tree forest of .self
        Graph<T> getSpanningTree();

    private:
        void spanningDFS(Graph<T> *resGraph, std::vector<bool> &visited, std::size_t v);

        void copyVertexData(Graph<T> *rhs);

    protected:

        // Vertex number.
        std::size_t N;
        // Edge number.
        std::size_t E;
        // Here will be stored pointers to verts.
        std::vector<Vertex<T> > vertexList;
        // Adjacency list.
        std::vector<std::set<std::size_t> > adjList;
    };


#include "Graph.inc"

}

#endif //GRAPHTREE_GRAPH_H
