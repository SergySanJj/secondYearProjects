# Graph

 Graph is a simple C++ module that implements graph datasructure and different 
methods that can help you to easily imlement your own derived graph class.

# DateTime

 DateTime is a sample class that contains data about date and time in Unix date
format and can convert in in two sides.

## Usage of Graph module


 To use Graph class you need to include '''Graph.h''' from include/ directory.

 To create Graph object use namespace GraphTree with any constructor that satisfies 
your needs:
```c++
// Create graph g with some_type type values stored in vertices
// and n Vertex number (n can be 0 and must be 0 IF you want an empty graph).
GraphTree::Graph<some_type> g(n); 

// Create graph g that stores some_type
// and innit g with vectorOfValues.
std::vector<std::vector<some_type> > vectorOfValues = {...};
GraphTree::Graph<some_type> g(vectorOfValues);
```

 You can also add new vertices to the graph by:
```c++
some_type newVal = ...;
g.addVertex(GraphTree::Vertex(newVal));
```

 To change value of some vertex with number v simply:
```c++
some_type newVal = ...;
g[v] = newVal;
```

 Now we can move to adding edges between vertices:
```c++
// Adds edge between vertices with numbers u and v (numeration from 0).
g.addEdge(u, v);
```

 You have two options of how to print out your graph (by numeration or by values 
stored in vertices).
 To print graph by numeration simply call:
```c++
g.print();
```

 To print by value you first need to implement helper function with signature
void (*)(some_type) that will be passed as argument to the print function to 
print each element in the way you want. As an example:
```c++
// Function that will be passed, you need to replace int type with your some_type.
void intPrintHelper(int val) {
    std::cout << "v(" << val << ")";
}

// And call print of g.
g.print(intPrintHelper);
```

 Graph module also has method to create a spanning tree of your graph:
```c++
GraphTree::Graph<some_type> spanG = g.getSpanningTree();
//..usage..//
```

#### Feel free to post issues, fork, star etc.
 
