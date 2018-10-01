

## Lab 1 var(8,7)
## Tested on Ubuntu 18.04

## How to run
1) Install CMake 3.8.0 and higher and C++ compiler that supports C++17
2) Go to the directory where you have cloned Graph-master
3) Then run next commands in terminal:
```
cd GraphTree
cmake .
make
```
4) To run type:
```
./GraphTree
```

# Graph

 Graph is a C++ module that implements graph datasructure and provides different 
methods that can help you to easily work with graphs.

# DateTime

 DateTime is a class that contains data about date and time date and provides
 methods to solve different tasks that can appear during working with dates.

## Usage of Graph module
#### usage is shown in samples part of demo main file (intGraphSample):
<a href="https://github.com/secondYearProjects/Graph/blob/master/GraphTree/src/main.cpp">DEMO MAIN</a>

To use Graph class you need to include '''Graph.h''' from Graphinclude/ directory.

To work with Graph module use GraphTree namespace.Then create graph object with 0 verticies 
that stores int values by:
```c++
    GraphTree::Graph<int> g1(0);
```

If you want to crate graph object with n=10 verticies:
```c++
std::size_t n = 10;
GraphTree::Graph<int> g2(n);
```

To add new vertex with value newValue to the graph use:
```c++
int newValue = 1;
g2.addVertex(GraphTree::Vertex(newValue));
```
To initialize new graph object with values from vector use:
```c++
std::vector<int> values = {1, 2, 3, 4, 5, 6};
GraphTree::Graph<int> g3(values);
```
To change value stored in v vertex (numeration from 0) use:
```c++
std::size_t v = 2;
g3[v] = 1000; // will change 3 to 1000.
```
To copy one graph object to another use:
```c++
g1 = g3;
g1 = g1;
```

To get number of verticies use:
```c++
g1.size(); // will return 6
g2.size(); // will return 10
g3.size(); // will return 6
```

To add edge between two verticies u and v use:
#### WARNING: Graph doesn't support multiedges and loops
```c++
    v = 1;
    std::size_t u = 2;
    g3.addEdge(u, v); // will connect {2} and {3}
```

Add more edges:
```c++
g3.addEdge(4, 2);
g3.addEdge(4, 5);
g3.addEdge(5, 1); // here we have created a cycle chain (1-2-4-5-1)
g3.addEdge(0, 1);
```

To get number of edges use:
```c++
g1.edgeCount(); // will return 0
g2.edgeCount(); // will return 0
g3.edgeCount(); // will return 5
```

To get a spanning tree with root in vertex v from some graph g3 use:
```c++
v = 0;
GraphTree::Graph<int> spanTreeG3 = g3.getSpanningTree(v);
```
To get a spanning forest from graph g3 use:
```c++
GraphTree::Graph<int> spanForestG3 = g3.getSpanningTree();
```

#### PRINTING

To print graph g3 to the iostream console use .print()it will print adjacency list
with vertex numbers.
```c++
std::cout << "\ng3 in number form:\n";
g3.print();
```

To print graph g3 djacency list with data stored in verticies
you first need to implement the function that will be called for each vertex
and print it in any form you want. As an example we use intPrintHelper() function.
Helper function with signature void ()(some_type) that will be passed as argument
to the print function to print each element in the way you want.
After that use:
```c++
std::cout << "\ng3 in special form:\n";
g3.print(intPrintHelper);

std::cout << "\nspanTreeG3 in number form:\n";
spanTreeG3.print();

std::cout << "\nspanForestG3 in number form:\n";
spanForestG3.print();
```

To build random connection graph with n verticies use:
```c++
n = 10;
GraphTree::Graph<int> rndG = GraphTree::buildRandomGraph<int>(n);

std::cout << "\nrndG in number form:\n";
rndG.print();
```

#### usage with std::vector<> and analogically any class is shown in (vectorGraphSample):
You can store any class/type in Graph datastruct unless it has:
    -constructor
    -destructor
    -assignment operator

Next sample shows how to use Graph that stores vectors as values in verticies:
innit with vector of vectors:
```c++
    GraphTree::Graph<std::vector<int> > vecG({{1,    3, 3, 7},
                                              {19,   -91},
                                              {0,    0, 0, 0, 0},
                                              {1000, 1}});
```

add one more vector:
```c++
    vecG.addVertex(GraphTree::Vertex(std::vector({1, 1, 1, 1, 1, 1, 1})));
```

add some edges:
```c++
    vecG.addEdge(0, 2);
    vecG.addEdge(0, 1);
    vecG.addEdge(3, 4);

    //replace last vertex value with {1,2,3}
    vecG[vecG.size() - 1] = std::vector({1, 2, 3});
    // replace last vertex value with {3,2,1}
    vecG[0] = std::vector({3, 2, 1});

    // print
    std::cout << "\nvecG in number form:\n";
    vecG.print();

    // print in special form:
    std::cout << "\nvecG in special form:\n";
    vecG.print(vecPrintHelper<int>);
```

## Usage of DateTime module

#### usage is shown in samples part of demo main file (DateTimeSample):
<a href="https://github.com/secondYearProjects/Graph/blob/master/GraphTree/src/main.cpp">DEMO MAIN</a>

To work with Graph module use DT namespace.

To create Date object use:
where values are ordered dd/mm/yy
WARNING: works with dates from 01/01/0000 to 31/12/9999
```c++
    DT::Date date1(29, 9, 2018);
```

To create Time object use:
where values are ordered h/m/s
```c++
    DT::Time time1(10, 25, 56);
```
To create DateTime object use:
```c++
    DT::DateTime dt1(date1, time1);
```
Or simply:
```c++
    DT::DateTime dt2(DT::Date(29, 9, 2018), DT::Time(10, 25, 56));
    DT::DateTime dt3(DT::Date(31, 12, 2018), DT::Time(23, 59, 59)); // yeah 1 sec before NY
```

Use .print() to print stored values.
Use .println() to print stored values and move to the next line.
```c++
    date1.println();
    time1.println();
    dt1.println();
```

To validate date use:
```c++
    DT::validateDate(29, 9, 2018);
```

To get number of week day use:
```c++
    std::cout << "\n" << dt1.dayOfWeek() << "\n";
    std::cout << DT::getDayOfWeek(29, 9, 2018) << "\n";
```

To get day of week string use:
```c++
    std::cout << "\n" << dt1.dayOfWeekString() << "\n";
    std::cout << DT::toDayOfWeek(DT::getDayOfWeek(29, 9, 2018)) << "\n";
```

To get month,day,year,hour,minute,second from
DateTime, Time or Date use .Month(), .Year() .. etc.
```c++
    date1.Month();
    time1.Seconds(); // Note Seconds NOT Second.
```
#### operations

To store date time difference use DateTimeDelta class
```c++
    DT::DateTimeDelta toNY = dt3 - dt2;
```
Usage of DateTimeDelta clas:
```c++
    std::cout << "\nTo NY from 29/09/2018 10:25:56:    ";
    toNY.print();
    std::cout << "\n";
    std::cout << "delta in days :" << toNY.TotalDays() << "\n";
    std::cout << "delta in seconds :" << toNY.TotalSeconds() << "\n";
```

To add/subtract delta from DateTime use:
WARNING: if after subtracting Date goes below 1/1/0000
result will be 1/1/0000 00:00:00
```c++
    DT::DateTime addDT = dt1 + toNY;
    DT::DateTime subDT = dt1 - toNY;
    DT::DateTime zeroDate = dt1 - (DT::DateTime() - dt3); // overlap through 1/1/0 00/00/00
    std::cout << "addDT :";
    addDT.println();
    std::cout << "subDT :";
    subDT.println();
    std::cout << "zeroDate :";
    zeroDate.println();
```

You can also use ==, !=, <, > for Date, Time, DateTime and DateTimeDelta
to compare same type values.

## Watch other samples in:
<a href="https://github.com/secondYearProjects/Graph/blob/master/GraphTree/src/main.cpp">Other samples</a>

#### Feel free to post issues, fork, star etc.
 
