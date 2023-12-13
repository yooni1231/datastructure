#include "ListGraph.h"
#include <iostream>
#include <utility>

ListGraph::ListGraph(bool type, int size) : Graph(type, size)
{
    m_Type = type;
    m_List = new map<int, int>[size];
}

ListGraph::~ListGraph()	
{
    delete[] m_List;
}

void ListGraph::getAdjacentEdges(int vertex, map<int, int>* m)	 //Definition of getAdjacentEdges(No Direction == Undirected)
{
    for (int i = 0; i < m_Size; i++) {
        for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++) {
            if (vertex == it_->first)
                m[vertex].insert(make_pair(i, it_->second));
            if (vertex == i)
                m[vertex].insert(make_pair(it_->first, it_->second));
        }
    }
}

void ListGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)	//Definition of getAdjacentEdges(Directed graph)
{
    for (auto it_ = m_List[vertex].begin(); it_ != m_List[vertex].end(); it_++) {
        m[vertex].insert(make_pair(it_->first, it_->second));
    }
}

void ListGraph::insertEdge(int from, int to, int weight) //Definition of insertEdge
{
    m_List[from].insert(make_pair(to, weight));
}

bool ListGraph::printGraph(ofstream *fout)	//Definition of print Graph
{
    (*fout) << "==========PRINT==========" << endl;
    
    for (int i = 0; i < m_Size; i++) {
        (*fout) << "[" << i << "]";
        for (auto it_ = m_List[i].begin(); it_ != m_List[i].end(); it_++) {
            (*fout) << " -> " << "(" << it_->first << "," << it_->second << ")";
        }
        (*fout) << endl;
    }
    (*fout) << "=========================" << endl << endl;
    
    return 1;
}
