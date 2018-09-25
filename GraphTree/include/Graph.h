//
// Graph module
// Created by sergysanjj on 19.09.18.
//

#ifndef GRAPHTREE_GRAPH_H
#define GRAPHTREE_GRAPH_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <stack>
#include <type_traits>
#include <typeinfo>


namespace GraphTree {

    template<typename T>
    class Vertex {
    public:
        Vertex<T>() : vertexData() {}

        explicit Vertex<T>(T data) : vertexData(data) {}

        ~Vertex<T>() = default;

        Vertex &operator=(const Vertex<T> &rsv) {
            vertexData = rsv.vertexData;
            return *this;
        }

        Vertex &operator=(const T &value) {
            vertexData = static_cast<T>(value);
            return *this;
        }

        T &accessData() { return vertexData; }

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
        virtual void print() const;

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

/********--------Implementation--------********/

    template<typename T>
    Graph<T>::Graph(std::size_t n): N(n), E(0) {
        vertexList.resize(N);
        adjList.resize(N);
    }

    template<typename T>
    Graph<T>::Graph(const std::vector<T> &values): N(values.size()), E(0) {
        vertexList.reserve(values.size());
        adjList.resize(values.size());

        for (std::size_t i = 0; i < N; i++) {
            vertexList.push_back(Vertex(values[i]));
        }
    }


    template<typename T>
    void Graph<T>::addVertex(const GraphTree::Vertex<T> &v) {
        vertexList.push_back(v);
        adjList.resize(adjList.size() + 1);
        N++;
    }


    template<typename T>
    void Graph<T>::addEdge(std::size_t u, std::size_t v) {
        try {
            if (u < N && v < N && u != v) {
                // Won't insert once more if and create multiedge.
                if (adjList[u].find(v) == adjList[u].end()) {
                    adjList[u].insert(v);
                    adjList[v].insert(u);
                    E++;
                }
            } else {
                if (u != v)
                    throw ("\nError: u or v vertex not in graph.\n");
                else
                    throw ("\nError: graph data structure can't contain loops.\n");
            }
        } catch (const char *msg) {
            std::cerr << msg << '\n';
        }
    }


    template<typename T>
    void Graph<T>::print() const {
        for (std::size_t i = 0; i < N; i++) {
            std::cout << " " << std::setw(3) << i << ": ";
            if (adjList[i].empty())
                std::cout << "--empty--";
            else {
                for (auto connection : adjList[i]) {
                    std::cout << connection << " ";
                }
            }
            std::cout << ";\n";
        }
    }

    template<typename T>
    template<typename OP>
    void Graph<T>::print(OP op) {
        for (std::size_t i = 0; i < N; i++) {
            std::cout << " ";
            op(vertexList[i].accessData());
            std::cout << ": ";
            if (adjList[i].empty())
                std::cout << "--empty--";
            else {
                for (auto connection : adjList[i]) {
                    op(vertexList[connection].accessData());
                    std::cout << " ";
                }
            }
            std::cout << ";\n";
        }
    }

    template<typename T>
    void Graph<T>::copyVertexData(Graph<T> *rhs) {
        vertexList.clear();
        vertexList = rhs->vertexList;
        adjList.clear();
        adjList.resize(rhs->size());
        N = rhs->size();
        E = 0;

    }

    template<typename T>
    Graph<T> Graph<T>::getSpanningTree() {
        std::vector<bool> visited(N, false);
        Graph<T> resTree(0);
        resTree.copyVertexData(this);

        for (std::size_t i = 0; i < N; i++) {
            if (!visited[i]) {
                spanningDFS(&resTree, visited, i);
            }
        }

        // Return by value
        return resTree;
    }

    template<typename T>
    void Graph<T>::spanningDFS(Graph<T> *resGraph, std::vector<bool> &visited, std::size_t v) {
        // We will do it non-recursive.

        // Emulate recursion with stack.
        std::stack<std::size_t> S;
        S.push(v);

        while (!S.empty()) {
            v = S.top();
            S.pop();

            if (!visited[v]) {

                visited[v] = true;
            }

            for (auto w: this->adjList[v]) {
                if (!visited[w]) {
                    resGraph->addEdge(v, w);
                    S.push(w);
                    visited[w] = true;
                }
            }
        }

    }


    template<typename T>
    Graph<T> &Graph<T>::operator=(const Graph<T> &rhs) {
        vertexList.clear();
        adjList.clear();

        vertexList = rhs.vertexList;
        adjList = rhs.adjList;

        N = rhs.size();
        E = rhs.edgeCount();


        return *this;
    }

    template<typename T>
    T &Graph<T>::operator[](std::size_t index) {

        if (index < vertexList.size())
            return (vertexList[index].accessData());
        else {
            std::cerr << "\n out of range";
            static_assert(1, "oor");
        }
    }

}

#endif //GRAPHTREE_GRAPH_H
