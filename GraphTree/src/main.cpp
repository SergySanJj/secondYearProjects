#include <iostream>
#include <Graph.h>


int main() {
    GraphTree::Graph<int> g(5);
    g.print(GraphTree::Print::vertecies);
    return 0;
}