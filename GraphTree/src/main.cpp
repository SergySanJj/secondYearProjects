#include <iostream>
#include <vector>
#include <iomanip>

#include "Graph.h"

void intPrintHelper(int val) {
    std::cout << "v(" << val << ")";
}

// TODO: aligned output.
template<typename T>
void vecPrintHelper(std::vector<T> val) {
    std::cout << "{ ";
    for (auto el : val) {
        std::cout << el << " ";
    }
    std::cout << "},";
}

int main() {
    GraphTree::Graph<int> g(0);
    g.addVertex(GraphTree::Vertex(213));
    g.addVertex(GraphTree::Vertex(324));
    g.addVertex(GraphTree::Vertex(883));
    g.addVertex(GraphTree::Vertex(364));
    g.addVertex(GraphTree::Vertex(43));
    g.addVertex(GraphTree::Vertex(394));
    g.addVertex(GraphTree::Vertex(8));
    g.addVertex(GraphTree::Vertex(2214));
    //g.print(GraphTree::Print::vertices);

    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(5, 3);
    g.addEdge(3, 6);

    g[2] = 666;

    g.print();
    g.print(intPrintHelper);


    GraphTree::Graph<int> *spanG = g.getSpanningTree();
    std::cout << "\n\nSpan Graph\n";
    spanG->print();
    spanG->print(intPrintHelper);
    std::cout << "\n\nVector Graph\n";
    std::vector<std::vector<int> > setOfvec = {
            {1, 2, 3, 4},
            {5, 3, 5, 6},
            {2, 2, 8},
            {1, 3, 3, 7},
            {4, 2, 0},
            {1488}
    };
    GraphTree::Graph<std::vector<int> > gVec(setOfvec);
    gVec[0] = {0,0,0,0};
    gVec.addEdge(0, 2);
    gVec.addEdge(2, 1);
    gVec.addEdge(1, 4);
    gVec.print(vecPrintHelper<int>);
    delete spanG;
    return 0;
}