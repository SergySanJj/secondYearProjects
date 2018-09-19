//
// Created by sergei on 19.09.18.
//

#ifndef GRAPHTREE_GRAPH_H
#define GRAPHTREE_GRAPH_H

#include <stdlib.h>
namespace GraphTree {

    template <typename T>
    class Vertex{

    public:
        explicit Vertex<T>(T data): vertexData(data) {}
        ~Vertex<T>() {}

    private:
        T vertexData;
    };



    template <typename T>
    class Graph{

    public:


    private:


        // Vertex number.
        size_t N;


    };
}

#endif //GRAPHTREE_GRAPH_H
