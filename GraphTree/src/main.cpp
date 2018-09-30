//
// Demo main.
// Created by sergei on 21.09.18.
//

#include <iostream>
#include <vector>
#include <iomanip>

#include "Graph.h"
#include "DateTime.h"

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

void dateTimePrintHelper(DT::DateTime val) {
    val.print();
    std::cout << " ";
}


int main() {
    DT::DateTime d1(DT::Date(2, 10, 2018), DT::Time(10, 12, 1));
    DT::DateTime d2(DT::Date(3, 10, 2018), DT::Time(23, 13, 3));
    DT::DateTime zeroYear(DT::Date(3, 1, 0), DT::Time(0, 0, 0));
    DT::DateTimeDelta dd = d2 - d1;
    dd.println();

    (d2 + dd).println();

    (d2 - dd).println();

    GraphTree::Graph<DT::DateTime> dtG(0);
    dtG.addVertex(GraphTree::Vertex(d1));
    dtG.addVertex(GraphTree::Vertex(d2));
    dtG.addVertex(GraphTree::Vertex(zeroYear));

    dtG.addEdge(0,2);

    dtG.print(dateTimePrintHelper);

    for (std::uint16_t i = 20; i <= 31; i++)
        std::cout << i << " " << DT::getDayOfWeek(i, 9, 2080) << "\n";

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
    std::cout << "RANDOM:\n";

    GraphTree::Graph<int> rndG = GraphTree::buildRandomGraph<int>(10);
    rndG.print();
    std::cout << "\n Span rnd: \n";
    (rndG.getSpanningTree()).print();

    return 0;

    // TODO: think more about types
}