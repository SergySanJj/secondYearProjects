#include <iostream>
#include <Graph.h>

using GraphTree::Printable, GraphTree::Vertex;

// Example for inherited from Printed.
class DataType : public Printable<int> {
public:

    explicit DataType(const int &data): Printable<int>(data) {}

    ~DataType() = default;
    void print() final { std::cout << "v(" << Printable<int>::getData() << ")"; }
};

int main() {
/*    GraphTree::Graph<int> g(10);
    g.addVertex(GraphTree::Vertex(213));
    //g.print(GraphTree::Print::vertices);

    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(5, 3);
    g.addEdge(3, 6);



    g.print(GraphTree::Print::vertices);

    GraphTree::Graph<int>*  spanG = g.getSpanningTree();

    std::cout << "\n Tree of g:\n";
    spanG->print(GraphTree::Print::vertices);*/
    DataType r(2);
    std::cout << (typeid(Printable<int>) == typeid(GraphTree::Empt)) << '\n';

    std::cout << "\n\nPRINTABLE\n";
    GraphTree::Graph<DataType> pr = GraphTree::Graph<DataType>();
    pr.addVertex(Vertex(DataType(2)));
    pr.addVertex(Vertex(DataType(3)));

    pr.print(GraphTree::Print::data);

    pr.print(GraphTree::Print::vertices);

    return 0;
}