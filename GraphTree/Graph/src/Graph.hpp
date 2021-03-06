#include <iostream>
#include <array>
#include <vector>
#include <set>
#include <stack>

#include <cstdlib>
#include <Graph.h>

using Random = effolkronium::random_static;

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
Vertex<T> &Vertex<T>::operator=(const Vertex<T> &rsv) {
    vertexData = rsv.vertexData;
    return *this;
}

template<typename T>
Vertex<T> &Vertex<T>::operator=(const T &value) {
    vertexData = static_cast<T>(value);
    return *this;
}

template<typename T>
T Vertex<T>::data() const { return vertexData; }


template<typename T>
void Graph<T>::addEdge(std::size_t u, std::size_t v) {
    if (u < N && v < N && u != v) {
        // Won't insert once more if and create multiedge.
        if (adjList[u].find(v) == adjList[u].end()) {
            adjList[u].insert(v);
            adjList[v].insert(u);
            E++;
        }
    }
}


template<typename T>
void Graph<T>::print() const {
    if (N <= 0) {
        std::cout << "----EMPTY GRAPH----" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < N; i++) {
        std::cout << " " << i << ": ";
        if (adjList[i].empty())
            std::cout << "--empty--";
        else {
            for (auto connection : adjList[i]) {
                std::cout << connection << " ";
            }
        }
        std::cout << ";" << std::endl;
    }
}

template<typename T>
template<typename OP>
void Graph<T>::print(OP op) const {
    if (!N) {
        std::cout << "----EMPTY GRAPH----" << std::endl;
        return;
    }
    for (std::size_t i = 0; i < N; i++) {
        op(vertexList[i].data());
        std::cout << ": ";
        if (adjList[i].empty())
            std::cout << "--empty--";
        else {
            for (auto connection : adjList[i]) {
                op(vertexList[connection].data());
                std::cout << " ";
            }
        }
        std::cout << ";" << std::endl;
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
            spanningDFS(resTree, visited, i);
        }
    }

    // Return by value
    return resTree;
}

template<typename T>
Graph<T> Graph<T>::getSpanningTree(std::size_t startVertex) {
    std::vector<bool> visited(N, false);
    Graph<T> resTree(0);

    singleSpanningDFS(resTree, visited, startVertex);

    return resTree;
}

template<typename T>
void Graph<T>::spanningDFS(Graph<T> &resGraph, std::vector<bool> &visited, std::size_t v) {
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
                resGraph.addEdge(v, w);
                S.push(w);
                visited[w] = true;
            }
        }
    }

}

template<typename T>
void Graph<T>::singleSpanningDFS(Graph<T> &resGraph, std::vector<bool> &visited, std::size_t v) {
    // We will do it non-recursive.

    // Emulate recursion with stack.
    std::stack<std::size_t> S;

    std::vector<std::size_t> association(N, 0);

    association[v] = 0;
    resGraph.addVertex(Vertex(vertexList[v].data()));

    S.push(v);

    while (!S.empty()) {
        v = S.top();
        S.pop();

        if (!visited[v]) {
            visited[v] = true;
        }

        for (auto w: this->adjList[v]) {
            if (!visited[w]) {
                if (association[w] == 0) {
                    resGraph.addVertex(Vertex(vertexList[w].data()));
                    association[w] = resGraph.size() - 1;
                }
                resGraph.addEdge(association[v], association[w]);
                S.push(w);
                visited[w] = true;
            }
        }
    }

}

template<typename T>
Graph<T> &Graph<T>::operator=(const Graph<T> &rhs) {
    if (this == &rhs)
        return *this;

    vertexList.clear();
    adjList.clear();

    vertexList = rhs.vertexList;
    adjList = rhs.adjList;

    N = rhs.size();
    E = rhs.edgeCount();

    return *this;
}

template<typename T>
Vertex<T> &Graph<T>::operator[](std::size_t index) {
    if (index < N)
        return (vertexList[index]);
    else
        throw std::range_error("Graph vertex index out of range");
}

template<typename T>
std::size_t Graph<T>::size() const { return N; }

template<typename T>
std::size_t Graph<T>::edgeCount() const { return E; }

template<typename T>
T &Graph<T>::accessVertex(Vertex<T> *v) {
    return v->vertexData;
}

template<typename T>
std::vector<Vertex<T>> Graph<T>::getVertexList() { return vertexList; }

template<typename T>
std::vector<std::set<std::size_t>> Graph<T>::getAdjacencyList() { return adjList; }

template<typename T>
bool Vertex<T>::operator==(const Vertex<T> &rsv) const {
    return (vertexData == rsv.vertexData);
}

template<typename T>
bool Vertex<T>::operator!=(const Vertex<T> &rsv) const {
    return (vertexData != rsv.vertexData);
}


template<typename T>
Graph<T> buildRandomGraph(std::size_t n) {

    Graph<T> res(n);

    std::size_t edgeCount = Random::get<int>(0, ((n * n - n) / 2));
    for (std::size_t i = 0; i < edgeCount; i++) {
        std::size_t u = Random::get<int>(0, n);
        std::size_t v = Random::get<int>(0, n);
        res.addEdge(u, v);
    }
    return res;
}


// end using namespace GraphTree