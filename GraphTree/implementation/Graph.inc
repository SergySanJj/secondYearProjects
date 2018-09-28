#include "Graph.h"

// start using namespace GraphTree

using namespace GraphTree;


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
T &Vertex<T>::accessData() { return vertexData; }


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
    if (!N) {
        std::cout << "----EMPTY GRAPH----\n";
        return;
    }
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
    if (!N) {
        std::cout << "----EMPTY GRAPH----\n";
        return;
    }
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


// end using namespace GraphTree