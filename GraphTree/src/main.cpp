//
// DEMO MAIN
// Created by sergei on 21.09.18.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "Graph.h"
#include "DateTime.h"

#define RUN_SAMPLES 1

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
/*-----------------------------------------------*/

/****************** SAMPLES **********************/

void intGraphSample() {

    std::cout << "\n----intGraphSample----\n";

    /// To work with Graph module use GraphTree namespace.
    /// Then create graph object with 0 verticies that stores int values by:
    GraphTree::Graph<int> g1(0);

    /// If you want to crate graph object with n=10 verticies:
    std::size_t n = 10;
    GraphTree::Graph<int> g2(n);

    /// To add new vertex with value newValue to the graph use:
    int newValue = 1;
    g2.addVertex(GraphTree::Vertex(newValue));

    /// To initialize new graph object with values from vector use:
    std::vector<int> values = {1, 2, 3, 4, 5, 6};
    GraphTree::Graph<int> g3(values);

    /// To change value stored in v vertex (numeration from 0) use:
    std::size_t v = 2;
    g3[v] = 1000; // will change 3 to 1000.

    /// To copy one graph object to another use:
    g1 = g3;
    g1 = g1;

    /// To get number of verticies use:
    g1.size(); // will return 6
    g2.size(); // will return 10
    g3.size(); // will return 6

    /// To add edge between two verticies u and v use:
    /// WARNING: Graph doesn't support multiedges and loops
    v = 1;
    std::size_t u = 2;
    g3.addEdge(u, v); // will connect {2} and {3}

    /// Add more edges:
    g3.addEdge(4, 2);
    g3.addEdge(4, 5);
    g3.addEdge(5, 1); // here we have created a cycle chain (1-2-4-5-1)
    g3.addEdge(0, 1);

    /// To get number of edges use:
    g1.edgeCount(); // will return 0
    g2.edgeCount(); // will return 0
    g3.edgeCount(); // will return 5

    /// To get a spanning tree with root in vertex v from some graph g3 use:
    v = 0;
    GraphTree::Graph<int> spanTreeG3 = g3.getSpanningTree(v);

    /// To get a spanning forest from graph g3 use:
    GraphTree::Graph<int> spanForestG3 = g3.getSpanningTree();

    /*--PRINTING--*/

    /// To print graph g3 to the iostream console use .print()
    /// it will print adjacency list with vertex numbers.
    std::cout << "\ng3 in number form:\n";
    g3.print();

    /// To print graph g3 djacency list with data stored in verticies
    /// you first need to implement the function that will be called for each vertex
    /// and print it in any form you want. As an example we use intPrintHelper() function.
    /// After that use:
    std::cout << "\ng3 in special form:\n";
    g3.print(intPrintHelper);

    std::cout << "\nspanTreeG3 in number form:\n";
    spanTreeG3.print();

    std::cout << "\nspanForestG3 in number form:\n";
    spanForestG3.print();

    /// To build random connection graph with n verticies use:
    n = 10;
    GraphTree::Graph<int> rndG = GraphTree::buildRandomGraph<int>(n);

    std::cout << "\nrndG in number form:\n";
    rndG.print();

}

void vectorGraphSample() {
    std::cout << "\n--vectorGraphSample--\n";

    /// You can store any class/type in Graph datastruct unless it has:
    /// -constructor
    /// -destructor
    /// -assignment operator

    /// Next sample shows how to use Graph that stores vectors as values in verticies:
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
    std::cout << "\nvecG in number form:\n";
    vecG.print();

    // print in special form:
    std::cout << "\nvecG in special form:\n";
    vecG.print(vecPrintHelper<int>);

}

void DateTimeSample() {
    std::cout << "\n--DateTimeSample--\n";

    /// To work with Graph module use DT namespace.

    /// To create Date object use:
    /// where values are ordered dd/mm/yy
    /// WARNING: works with dates from 01/01/0000 to 31/12/9999
    DT::Date date1(29, 9, 2018);

    /// To create Time object use:
    /// where values are ordered h/m/s
    DT::Time time1(10, 25, 56);

    /// To create DateTime object use:
    DT::DateTime dt1(date1, time1);
    /// Or simply:
    DT::DateTime dt2(DT::Date(29, 9, 2018), DT::Time(10, 25, 56));
    DT::DateTime dt3(DT::Date(31, 12, 2018), DT::Time(23, 59, 59)); // yeah 1 sec before NY

    /// Use .print() to print stored values.
    /// Use .println() to print stored values and move to the next line.

    date1.println();
    time1.println();
    dt1.println();

    /// To validate date use:
    DT::validateDate(29, 9, 2018);

    /// To get number of week day use:
    std::cout << "\n" << dt1.dayOfWeek() << "\n";
    std::cout << DT::getDayOfWeek(29, 9, 2018) << "\n";

    /// To get day of week string use:
    std::cout << "\n" << dt1.dayOfWeekString() << "\n";
    std::cout << DT::toDayOfWeek(DT::getDayOfWeek(29, 9, 2018)) << "\n";

    /// To get month,day,year,hour,minute,second from
    /// DateTime, Time or Date use .Month(), .Year() .. etc.
    date1.Month();
    time1.Seconds(); // Note Seconds NOT Second.

    /*---operations---*/

    /// To store date time difference use DateTimeDelta class
    DT::DateTimeDelta toNY = dt3 - dt2;
    /// Usage of DateTimeDelta clas:
    std::cout << "\nTo NY from 29/09/2018 10:25:56:    ";
    toNY.print();
    std::cout << "\n";
    std::cout << "delta in days :" << toNY.TotalDays() << "\n";
    std::cout << "delta in seconds :" << toNY.TotalSeconds() << "\n";

    /// To add/subtract delta from DateTime use:
    /// WARNING: if after subtracting Date goes below 1/1/0000
    /// result will be 1/1/0000 00:00:00
    DT::DateTime addDT = dt1 + toNY;
    DT::DateTime subDT = dt1 - toNY;
    DT::DateTime zeroDate = dt1 - (DT::DateTime() - dt3); // overlap through 1/1/0 00/00/00
    std::cout << "addDT :";
    addDT.println();
    std::cout << "subDT :";
    subDT.println();
    std::cout << "zeroDate :";
    zeroDate.println();


    /// You can also use ==, !=, <, > for Date, Time, DateTime and DateTimeDelta
    /// to compare same type values.
}

void DateGraphSample() {

    std::cout << "\n--DateGraphSample--\n";
    /// Make vector of random DateTimes:
    std::vector<DT::DateTime> dtVec;
    DT::DateTime startdt(DT::Date(1, 1, 1), DT::Time(0, 0, 0));
    DT::DateTime enddt(DT::Date(28, 12, 9999), DT::Time(23, 59, 59));
    for (std::size_t i = 0; i < 10; i++) {
        dtVec.push_back(DT::DateTime(DT::randomDate(startdt.getDate(), enddt.getDate()),
                                     DT::randomTime(startdt.getTime(), enddt.getTime())));
    }

    // iinit graph with dtVec.
    GraphTree::Graph<DT::DateTime> gDates(dtVec);
    gDates.print(dateTimePrintHelper);

}

std::string GraphStringSample() {

    std::cout << "\n--GraphStringSample--\n";


    std::vector<std::string> strVec = {static_cast<std::string>("aa"),
                                       static_cast<std::string>("ab"),
                                       static_cast<std::string>("ba")};

    GraphTree::Graph<std::string> strG(strVec);
    std::string lft = "~(@-@~)";
    std::string rgh = "(~@-@)~";
    strG[0] = lft;
    strG[1] = rgh;

    strG.addEdge(0, 1);
    strG.print(stringPrintHelper);

}

/*-----------------------------------------------*/
/*-----------------------------------------------*/

int main() {
#if RUN_SAMPLES

    intGraphSample();

    vectorGraphSample();

    DateTimeSample();

    DateGraphSample();

    GraphStringSample();

#endif
    return 0;
}