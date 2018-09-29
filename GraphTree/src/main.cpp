//
// Demo main.
// Created by sergei on 21.09.18.
//

#include <iostream>
#include <vector>
#include <iomanip>

#include "../Graph/include/Graph.h"
#include "tests.cpp"
#include "../DateTime/include/DateTime.h"

void intPrintHelper(int val) {
    std::cout << "v(" << val << ")";
}

template<typename T>
void vecPrintHelper(std::vector<T> val) {
    std::cout << "{ ";
    for (auto el : val) {
        std::cout << el << " ";
    }
    std::cout << "},";
}


int main() {
    std::cout << DateTime::getDayOfWeek(9,25,2018) << "\n";
    std::cout << DateTime::getDayOfWeek(10,10,2018) << "\n";
    std::cout << DateTime::getDayOfWeek(10,10,2042) << "\n"; // Is invalid date due to UNIX time.

    GraphTree::Graph<int> zero(0);
    zero.print();


    GraphTree::Graph<int> g(3);
    g.addVertex(GraphTree::Vertex(213));
    g.addVertex(GraphTree::Vertex(324));
    g.addVertex(GraphTree::Vertex(883));
    g.addVertex(GraphTree::Vertex(364));
    g.addVertex(GraphTree::Vertex(43));
    g.addVertex(GraphTree::Vertex(394));
    g.addVertex(GraphTree::Vertex(8));
    g.addVertex(GraphTree::Vertex(2214));

    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(5, 3);
    g.addEdge(3, 6);

    g[2] = 666;

    std::cout << "\n";
    g.print();
    std::cout << "\n";
    g.print(intPrintHelper);


    GraphTree::Graph<int> spG = g.getSpanningTree();


    std::cout << "\n\nSpan Graph\n";
    std::cout << "\n";
    spG.print();
    return 0;
}