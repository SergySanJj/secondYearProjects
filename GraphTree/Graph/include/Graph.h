//
// Graph module
// Created by sergysanjj on 19.09.18.
//

#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <stack>

#include <cstdlib>

#include "../../dependencies/random.hpp"

namespace GraphTree {

    template<typename T>
    class Graph;

    template<typename T>
    class Vertex {
    public:
        // Create an empty vertex.
        Vertex<T>() : vertexData() {}

        // Create vertex with data as stored value.
        explicit Vertex<T>(T data) : vertexData(data) {}

        ~Vertex<T>() = default;

        bool operator==(const Vertex<T> &rsv) const;

        bool operator!=(const Vertex<T> &rsv) const;

        Vertex &operator=(const Vertex<T> &rsv);

        Vertex &operator=(const T &value);

        // Returns const reference to the stored value.
        T data() const;

        friend T &Graph<T>::accessVertex(Vertex<T> *v);

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

        std::vector<Vertex<T>> getVertexList();

        std::vector<std::set<std::size_t>> getAdjacencyList();

        // Gives access to data inside index vertex.
        Vertex<T> &operator[](std::size_t index);

        // Assignment operator.
        Graph &operator=(const Graph<T> &rhs);

        // Returns number of vertices.
        std::size_t size() const;

        // Returns number of edges.
        std::size_t edgeCount() const;

        // Print adjacency list with numeration. (any derived class can reimplement).
        virtual void print() const;

        // Print adjacency list with data in form defined by op function.
        template<typename OP>
        void print(OP op) const;

        // Adds new vertex. Call as .addVertex(Vertex(data));
        void addVertex(const Vertex<T> &v);

        // Connect u with v (numeration from 0, DOESN'T supports multiedges and loops).
        void addEdge(std::size_t u, std::size_t v);

        bool areConnected(std::size_t u, std::size_t v) {
            return ((adjList[u]).find(v) != (adjList[u]).end());
        }

        // Returns new graph by value that contains forest of spanning trees of the graph.
        Graph<T> getSpanningTree();

        /** Returns new graph by value that contains spanning tree of the graph that has root at startVertex.
        // WARNING: numeration of vertexes might change.
        // Result graph will be homeomorphic to one of the
        // forest span trees obtained from getSpanningTree().**/
        Graph<T> getSpanningTree(std::size_t startVertex);


        /* FRIEND to Vertex */
        T &accessVertex(Vertex<T> *v);

    private:
        // Vertex number.
        std::size_t N;
        // Edge number.
        std::size_t E;
        // Here will be stored pointers to vertices.
        std::vector<Vertex<T> > vertexList;
        // Adjacency list.
        std::vector<std::set<std::size_t> > adjList;

        // Help function that runs DFS from v vertex and adds found spanning
        // tree connections into resGraph.
        void spanningDFS(Graph<T> &resGraph, std::vector<bool> &visited, std::size_t v);

        // Help function that runs DFS from v vertex and adds found spanning
        // tree connections and vertexes into resGraph.
        void singleSpanningDFS(Graph<T> &resGraph, std::vector<bool> &visited, std::size_t v);

        // Copy vertex data into .this graph from rhs, delete any data that was in .this.
        void copyVertexData(Graph<T> *rhs);

    };

    // Returns random graph with n vertices
    template<typename T>
    Graph<T> buildRandomGraph(std::size_t n);

#include "Graph.hpp"

}


