#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex);     
bool DFS(Graph* graph, char option,  int vertex);     
bool KWANGWOON(Graph* graph, int vertex);  
bool Kruskal(Graph* graph);
bool Dijkstra(Graph* graph, char option, int vertex);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex); //Bellman - Ford
bool FLOYD(Graph* graph, char option);   //FLoyd

int find_Root(int node, int parent[]);
void union_Root(int node1, int node2, int parent[]);
void quicksort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high);
void insertionSort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high);
int partition(vector<pair<int, pair<int, int>>> *arr, int low, int high);
void find_path(int s, int e, int dist[], int prev[]);

#endif
