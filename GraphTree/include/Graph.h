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

    enum Errors {BadAlloc=0};

    // Graph node that contains some data.
    template<typename T> class Vertex;

    // Structure to work with numerated Graphs.
    template<typename T> class Graph;


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
        Graph(std::size_t n=0);

        ~Graph();

        // TODO: write copy constructor, assigment operator

        // Call as .addVertex(Vertex(data));
        void addVertex(const Vertex<T>& v);

        void addEdge(const Vertex<T>& u, const Vertex<T>& v);
        void addOrientedEdge(const Vertex<T>& u, const Vertex<T>& v);

        std::shared_ptr<Graph<T>> getSpanningTree();

    private:

    protected:
        // Vertex number.
        std::size_t N;
        // Here will be stored pointers to verts.
        std::vector< std::shared_ptr< Vertex<T> > > vertexList;
        // Adjacency list.
        std::vector< std::set< std::size_t > > adjList;  // TODO: think once more about using hash map insted
    };

/********--------Implementation--------********/

    template<typename T>
    Graph<T>::Graph(std::size_t n): N(n) {

        try
        {
            vertexList.resize(N);
            adjList.resize(N);

        }
        catch (std::bad_alloc& ba)
        {
            std::cerr << "bad_alloc caught: " << ba.what() << '\n';
            throw Errors::BadAlloc;
        }

        for (auto vert = vertexList.begin(); vert != vertexList.end(); vert++)
        {
            vert(new Vertex<T>());
        }
    }

}





#endif //GRAPHTREE_GRAPH_H
