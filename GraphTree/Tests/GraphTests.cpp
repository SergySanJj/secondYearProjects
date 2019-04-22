//
// Created by isara on 22-Apr-19.
//

#include "gtest/gtest.h"

#include "Graph.h"
#include "DateTime.h"
#include "DateTimeDelta.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

#include <cstdlib>

/************************************************/
/******** EXAMPLES OF PRINT HELPERS *************/
void intPrintHelper(int val) {
    std::cout << "v(" << val << ")";
}

template<typename T>
void vecPrintHelper(std::vector<T> val) {
    std::cout << "{ ";
    for (auto el : val) {
        std::cout << el << " ";
    }
    std::cout << "} ";
}

void dateTimePrintHelper(DT::DateTime val) {
    val.print();
    std::cout << " ";
}

void stringPrintHelper(std::string val) {
    std::cout << "\"" << val << "\" ";
}

void doublePrintHelper(double val) {
    std::cout.precision(3);
    std::cout << std::fixed;
    std::cout << val << " ";
}
/*-----------------------------------------------*/

/****************** SAMPLES **********************/

void intGraphSample() {

    std::cout << "\n----intGraphSample----" << std::endl;

    // To work with Graph module use GraphTree namespace.
    // Then create graph object with 0 vertexes that stores int values by:
    GraphTree::Graph<int> g1(0);

    // If you want to crate graph object with n=10 vertexes:
    std::size_t n = 10;
    GraphTree::Graph<int> g2(n);

    // To add new vertex with value newValue to the graph use:
    int newValue = 1;
    g2.addVertex(GraphTree::Vertex(newValue));

    // To initialize new graph object with values from vector use:
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    GraphTree::Graph<int> g3(values);

    // To change value stored in v vertex (numeration from 0) use:
    std::size_t v = 2;
    g3[v] = 1000; // will change 3 to 1000.

    // To copy one graph object to another use:
    g1 = g3;
    g1 = g1;

    // To get number of vertexes use:
    g1.size(); // will return 6
    g2.size(); // will return 10
    g3.size(); // will return 6

    // To add edge between two vertexes u and v use:
    // WARNING: Graph doesn't support multiedges and loops
    v = 1;
    std::size_t u = 2;
    g3.addEdge(u, v); // will connect {2} and {3}

    // Add more edges:
    g3.addEdge(4, 2);
    g3.addEdge(4, 5);
    g3.addEdge(5, 1); // here we have created a cycle chain (1-2-4-5-1)
    g3.addEdge(0, 1);

    // To get number of edges use:
    g1.edgeCount(); // will return 0
    g2.edgeCount(); // will return 0
    g3.edgeCount(); // will return 5

    // To get a spanning tree with root in vertex v from some graph g3 use:
    v = 0;
    GraphTree::Graph<int> spanTreeG3 = g3.getSpanningTree(v);

    // To get a spanning forest from graph g3 use:
    GraphTree::Graph<int> spanForestG3 = g3.getSpanningTree();

    /*--PRINTING--*/

    // To print graph g3 to the iostream console use .print()
    // it will print adjacency list with vertex numbers.
    std::cout << "\ng3 in number form:" << std::endl;
    g3.print();

    // To print graph g3 adjacency list with data stored in vertexes
    // you first need to implement the function that will be called for each vertex
    // and print it in any form you want. As an example we use intPrintHelper() function.
    // After that use:
    std::cout << "\ng3 in special form:" << std::endl;
    g3.print(intPrintHelper);

    std::cout << "\nspanTreeG3 in number form:" << std::endl;
    spanTreeG3.print();

    std::cout << "\nspanForestG3 in number form:" << std::endl;
    spanForestG3.print();

    // To build random connection graph with n vertexes use:
    n = 10;
    GraphTree::Graph<int> rndG = GraphTree::buildRandomGraph<int>(n);

    std::cout << "\nrndG in number form:" << std::endl;
    rndG.print();

}

void vectorGraphSample() {
    std::cout << "\n--vectorGraphSample--" << std::endl;

    // You can store any class/type in Graph datastruct unless it has:
    // -constructor
    // -destructor
    // -assignment operator

    // Next sample shows how to use Graph that stores vectors as values in vertexes:
    // innit with vector of vectors:
    GraphTree::Graph<std::vector<int> > vecG({{1,    3, 3, 7},
                                              {19,   -91},
                                              {0,    0, 0, 0, 0},
                                              {1000, 1}});

    // add one more vector:
    vecG.addVertex(GraphTree::Vertex(std::vector({1, 1, 1, 1, 1, 1, 1})));

    // add some edges:
    vecG.addEdge(0, 2);
    vecG.addEdge(0, 1);
    vecG.addEdge(3, 4);

    // replace last vertex value with {1,2,3}
    vecG[vecG.size() - 1] = std::vector({1, 2, 3});
    // replace last vertex value with {3,2,1}
    vecG[0] = std::vector({3, 2, 1});

    // print
    std::cout << "\nvecG in number form:" << std::endl;
    vecG.print();

    // print in special form:
    std::cout << "\nvecG in special form:" << std::endl;
    vecG.print(vecPrintHelper<int>);

}



void DateGraphSample() {

    std::cout << "\n--DateGraphSample--" << std::endl;
    // Make vector of random DateTimes:
    std::vector<DT::DateTime> dtVec;
    DT::DateTime startdt(DT::Date(1, 1, 1), DT::Time(0, 0, 0));
    DT::DateTime enddt(DT::Date(28, 12, 9999), DT::Time(23, 59, 59));
    for (std::size_t i = 0; i < 10; i++) {
        dtVec.push_back(DT::DateTime(DT::randomDate(startdt.getDate(), enddt.getDate()),
                                     DT::randomTime(startdt.getTime(), enddt.getTime())));
    }

    // init graph with dtVec.
    GraphTree::Graph<DT::DateTime> gDates(dtVec);
    gDates.print(dateTimePrintHelper);

}

void GraphStringSample() {

    std::cout << "\n--GraphStringSample--" << std::endl;

    std::vector<std::string> strVec = {"aa", "ab", "ba", "bb"};

    GraphTree::Graph<std::string> strG(strVec);
    std::string lft = "~(@-@~)";
    std::string rgh = "(~@-@)~";

    strG[0] = lft;
    strG[1] = rgh;

    strG[3] = "lab 1 var (8,7) ~(*-*)~";
    strG[2] = strG[2]; // won't change
    strG.addEdge(0, 1);
    strG.print(stringPrintHelper);

}


void doubleGraphSample() {
    std::cout << "\n--doubleGraphSample--" << std::endl;

    // innit graph g with double vector values
    std::vector<double> doubleVec = {2.33234, 64.434, 1.0, 343.01, 12.332, 11, 0101, 10, 01};
    GraphTree::Graph<double> g(doubleVec);

    g.addEdge(0, 1);
    g.addEdge(2, 1);
    g.addEdge(3, 1);
    g.addEdge(5, 2);
    g.addEdge(0, 1);

    // print double valued graph with format defined by doublePrintHelper().
    g.print(doublePrintHelper);
}