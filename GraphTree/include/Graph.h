//
// Created by sergysanjj on 19.09.18.
//

#ifndef GRAPHTREE_GRAPH_H
#define GRAPHTREE_GRAPH_H

#include <stdlib.h>
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <set>
#include <memory>


namespace GraphTree {

    // TODO: separate errors handler/message printer to a different file/class.
    // TODO: mb add Error return value from functions.
    enum Errors {
        BadAlloc = 0,
        NoSuchVertexNumber = 1
    };

    enum Print {
        vertecies = 0,
        data = 1
    };


    // Inherit from this class and rewrite print() method.
    class Printable{
    public:
        Printable() {}
        ~Printable() {}

        virtual void print() = 0;
    private:
    protected:

    };

    // Example for inherited from Printed.
    template <typename T>
    class DataType: public Printable{
    public:
        DataType(const int& data) {}
        ~DataType() {}
        virtual void print() { std::cout << data; }

    private:
        T data;
    };

    template<typename T>
    class Vertex {

    public:
        Vertex<T>() {}

        explicit Vertex<T>(T data) : vertexData(data) {}

        ~Vertex<T>() {}

    private:

        T vertexData;
    };


    template<typename T>
    class Graph {

    public:

        // Create an empty graph with n verticies.
        explicit Graph(std::size_t n = 0);

        ~Graph();

        // TODO: write copy constructor, assigment operator

        std::size_t size() const { return N; }
        std::size_t edgeCount() const  { return E; }

        void print(Print option);

        // Call as .addVertex(Vertex(data));
        void addVertex(const Vertex<T> &v);

        // Connect u wirh v (numeration from 0, DOESN'T supports multiedges).
        void addEdge(std::size_t  u, std::size_t v);

        // Add oriented edge from u to v (numeration from 0).
        void addOrientedEdge(std::size_t  u, std::size_t v);

        // Returns pointer to the new graph that contains Spanning Tree forest of .self
        std::shared_ptr<Graph<T>> getSpanningTree();

    private:

    protected:

        void copyVertexData(const Graph<T>& rhs);

        // Vertex number.
        std::size_t N;
        // Edge number.
        std::size_t E;
        // Here will be stored pointers to verts.
        std::vector< Vertex<T> > vertexList;
        // Adjacency list.
        std::vector<std::set<std::size_t> > adjList;  // TODO: think once more about using hash map insted
    };

/********--------Implementation--------********/

    template<typename T>
    Graph<T>::Graph(std::size_t n): N(n), E(0) {
        vertexList.resize(N);
        adjList.resize(N);

        for (auto vert : vertexList) {
            vert = Vertex<T>();
        }
    }


    template<typename T>
    Graph<T>::~Graph() {
    }


    template <typename T>
    void Graph<T>::addVertex(const GraphTree::Vertex<T> &v) {
        vertexList.push_back(v);
        adjList.resize(adjList.size()+1);
        N++;
    }


    template <typename T>
    void Graph<T>::addOrientedEdge(std::size_t u, std::size_t v) {
        if (u<N && v<N){
            // Won't insert once more if and create multiedge due to SET datastructure.
            adjList[u].insert(v);
            E++;
        } else{
            std::cerr << "\nError: u or v vert not in graph.\n";
        }
    }


    template <typename T>
    void Graph<T>::addEdge(std::size_t u, std::size_t v) {
        addOrientedEdge(u,v);
        addOrientedEdge(v,u);
    }


    template <typename T>
    void Graph<T>::print(Print option) {
        if (option == Print::vertecies){
            std::cout << "Adjecency list:\n";
            for (std::size_t i=0;i<N;i++)
            {
                std::cout << " " << i << ": ";
                if (adjList[i].empty())
                    std::cout << "--empty--";
                else {
                    for (auto connection : adjList[i])
                    {
                        std::cout << connection << " ";
                    }
                }
                std::cout << ";\n";
            }
        } else {
            // TODO: implement calss Printable and put print() func here for each vert.
        }
    }

    template <typename T>
    void Graph<T>::copyVertexData(const GraphTree::Graph<T> &rhs) {
        vertexList.clear();
        vertexList = rhs.vertexList;
        adjList.clear();
        adjList.resize(rhs.size());
        N=rhs.size();
        E=0;

    }

    template <typename T>
    std::shared_ptr<Graph<T>> Graph<T>::getSpanningTree() {
        using std::vector, std::array;
        array<bool,N> visited(0);
        std::shared_ptr<Graph<T>> resTree = Graph<T>();
        resTree.copyVertexData(this);

        for(std::size_t i=0;i<N;i++)
        {
            if(!visited[i]){
                // TODO start here
            }
        }
    }



}


#endif //GRAPHTREE_GRAPH_H
