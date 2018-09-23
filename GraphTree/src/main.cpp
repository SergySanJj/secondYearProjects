#include <iostream>
#include <Graph.h>

void intPrintHelper(int val)
{
    std::cout << "v(" << val << ")";
}

int main() {
    GraphTree::Graph<int> g(10);
    g.addVertex(GraphTree::Vertex(213));
    //g.print(GraphTree::Print::vertices);

    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(5, 3);
    g.addEdge(3, 6);



    g.print();
    std::cout << "\n";
    g.print(intPrintHelper);
    GraphTree::Graph<int>*  spanG = g.getSpanningTree();

    return 0;
}