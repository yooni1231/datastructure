#include "MatrixGraph.h"
#include <iostream>
#include <vector>
#include <string>

MatrixGraph::MatrixGraph(bool type, int size) : Graph(type, size)
{
    m_Mat = new int *[size];
    for (int i = 0; i < size; i++) {
        m_Mat[i] = new int[size];
        memset(m_Mat[i], 0, sizeof(int) * size);
    }
}

MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < getSize(); i++) {
        delete[] m_Mat[i];
    }
    delete[] m_Mat;
}

void MatrixGraph::getAdjacentEdges(int vertex, map<int, int>* m)
{	
    for(int i=0;i<m_Size;i++){
        for(int j=0;j<m_Size;j++){
            if(m_Mat[i][j]!=0&&j==vertex)
                m[vertex].insert(std::make_pair(i,m_Mat[i][j]));
            if(m_Mat[i][j]!=0&&i==vertex)
                m[vertex].insert(std::make_pair(j,m_Mat[i][j]));
        }
    }
}

void MatrixGraph::getAdjacentEdgesDirect(int vertex, map<int, int>* m)
{
    for(int i=0;i<m_Size;i++){
        if(m_Mat[vertex][i]!=0)
            m[vertex].insert(std::make_pair(i,m_Mat[vertex][i]));
    }
}

void MatrixGraph::insertEdge(int from, int to, int weight)	
{
    m_Mat[from][to] = weight;
}

bool MatrixGraph::printGraph(ofstream *fout)	
{
    if (m_Size < 0)
        return 0;
    
    (*fout) << "==========PRINT==========" << endl;
    
    (*fout) << "   ";
    for (int i = 0; i < m_Size; i++) {
        (*fout).width(3);
        (*fout) << "[" << i << "]";
    }
    (*fout) << endl;
    
    for (int i = 0; i < m_Size; i++) {
        (*fout) << "[" << i << "]";
        for (int j = 0; j < m_Size; j++) {
            (*fout).width(5);
            (*fout) << m_Mat[i][j];
        }
        (*fout) << endl;
    }
    (*fout) << "=========================" << endl << endl;
    
    return 1;
}
