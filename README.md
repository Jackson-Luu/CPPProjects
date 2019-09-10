# CPPProjects
Amalgamation of various C++ projects.

# Dynamic Graph

Implementation for a Generic Directed Weighted graph (GDWG) with value-like semantics in C++. Both the data stored at a node and the weight stored at an edge will be of generic types. Both generic types may be different. For example, here is a graph with nodes storing std::string and edges weighted by int:

  gdwg::Graph<<std::string,int>> g;
  
Formally, this directed weighted graph G=(N,E) will consist of a set of nodes N and a set of weighted edges E. All nodes in the graph are unique. Between any two nodes (or a node and itself), all edges must be unique.

The implementation includes constructors, destructors, operator overloads, methods as well as a custom iterator for iterating over the graph.
