//reference
//lab 08 graph code
// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#ifndef GRAPH_H
#define GRAPH_H


typedef struct GraphRep *Graph;

Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int   maxVertices(Graph map);

#endif