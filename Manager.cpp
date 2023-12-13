#include "Manager.h"
#include "GraphMethod.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_BUFFER_SIZE 1024
#define MAX_INPUT_LENGTH 128

Manager::Manager()	
{
    graph = nullptr;
    fout.open("log.txt", ios::app);
    load = 0;	//Anything is not loaded
}

Manager::~Manager()
{
    if(load)	//if graph is loaded, delete graph
        delete graph;
    if(fout.is_open())	//if fout is opened, close file
        fout.close();	//close log.txt File
}

void Manager::run(const char* command_txt){
    ifstream fin;	//Command File Input File Stream
    fin.open(command_txt, ios_base::in);//File open with read mode
    
    if(!fin) { //If command File cannot be read, Print error
        fout << "==========ERROR=========" << endl;
        fout << "Command File Open error" << endl;
        fout << "========================" << endl;
        return;	//Return
    }
    
    char *command, *param1, *param2;
    char buffer[MAX_INPUT_LENGTH] = {0};
    
    while (fin.getline(buffer, MAX_INPUT_LENGTH - 1)) { // Read line and parse command and parameters
        command = strtok(buffer, " ");
        param1 = strtok(NULL, " ");
        param2 = strtok(NULL, " ");
        
        if (!command && !param1 && !param2) // Case No input
            continue;
        
        if (strcmp(command, "EXIT") == 0) { // Case EXIT
            break;
        } else if (strcmp(command, "LOAD") == 0) { // CASE LOAD
            if (!param1) {
                printErrorCode(100);
                continue;
            } if (LOAD(param1)) {
                fout << "==========LOAD==========" << endl;
                fout << "Success" << endl;
                fout << "========================" << endl;
            } else {
                printErrorCode(100);
                continue;
            }
        } else if (strcmp(command, "PRINT") == 0) { // Case PRINT
            if (!load) {
                printErrorCode(200);
                continue;
            } if (graph) {
                PRINT();
            } else {
                printErrorCode(200);
                continue;
            }
        } else if (strcmp(command, "BFS") == 0) { // Case BFS
            if (!load) {
                printErrorCode(300);
                continue;
            } if (!param1 || !param2) {
                printErrorCode(300);
                continue;
            } if (!mBFS(param1[0], stoi(param2))) {
                printErrorCode(300);
                continue;
            }
        } else if (strcmp(command, "DFS") == 0) { // Case DFS
            if (!load) {
                printErrorCode(400);
                continue;
            } if (!param1 || !param2) {
                printErrorCode(400);
                continue;
            } if (!mDFS(param1[0], stoi(param2))) {
                printErrorCode(400);
                continue;
            }
        } else if (strcmp(command, "KRUSKAL") == 0) { // Case KRUSKAL
            if (!load) {
                printErrorCode(600);
                continue;
            } if (!mKRUSKAL()) {
                printErrorCode(600);
                continue;
            }
        } else if (strcmp(command, "DIJKSTRA") == 0) { // Case DIJKSTRA
            if (!load) {
                printErrorCode(700);
                continue;
            } if (!param1 || !param2) {
                printErrorCode(700);
                continue;
            } if (!mDIJKSTRA(param1[0], stoi(param2))) {
                printErrorCode(700);
                continue;
            }
        } else if (strcmp(command, "BELLMANFORD") == 0) { // Case BELLMANFORD
            if (!load) {
                printErrorCode(800);
                continue;
            }
            
            char *param3;
            param3 = strtok(NULL, " ");
            
            if (!param1 || !param2 || !param3) {
                printErrorCode(800);
                continue;
            } if (!mBELLMANFORD(param1[0], stoi(param2), stoi(param3))) {
                printErrorCode(800);
                continue;
            }
        } else if (strcmp(command, "FLOYD") == 0) { // Case FLOYD
            if (!load) {
                printErrorCode(900);
                continue;
            } if (!mFLOYD(param1[0])) {
                printErrorCode(900);
                continue;
            }
        } else if (strcmp(command, "KWANGWOON") == 0) { // Case KWANGWOON
            if (!load) {
                printErrorCode(500);
                continue;
            } if (!mKwoonWoon(stoi(param1))) {
                printErrorCode(500);
                continue;
            }
        }
    }
    fin.close();
    return;
}

bool Manager::LOAD(const char* filename)
{
    ifstream fin;
    fin.open(filename);
    
    if (!fin)
        return false;
    
    if (load)
        delete graph;
    
    load = true;
    char buffer[MAX_BUFFER_SIZE];
    char type;
    int size;
    
    fin.getline(buffer, MAX_BUFFER_SIZE);
    type = buffer[0];
    
    fin.getline(buffer, MAX_BUFFER_SIZE);
    size = stoi(buffer);
    
    if (type == 'L') {
        int idx = 0;
        graph = new ListGraph(0, size);
        
        while (!fin.eof()) {
            fin.getline(buffer, MAX_BUFFER_SIZE);
            
            char *buf1, *buf2;
            buf1 = strtok(buffer, " ");
            buf2 = strtok(NULL, "");
            
            if (!buf2) {
                if(!buf1)
                    continue;
                idx = atoi(buf1);
            } else {
                graph->insertEdge(idx, stoi(buf1), stoi(buf2));
            }
        }
    } else if (type == 'M') {
        graph = new MatrixGraph(1, size);
        
        int idx = 0;
        while (!fin.eof()) {
            char *buf;
            fin.getline(buffer, MAX_BUFFER_SIZE);
            buf = strtok(buffer, " ");
            
            if (!buf)
                continue;
            
            graph->insertEdge(idx, 0, stoi(buf));
            
            for (int j = 1; j < size; j++) {
                buf = strtok(NULL, " ");
                graph->insertEdge(idx, j, stoi(buf));
            }
            idx++;
        }
    } else {
        return false;
    }
    
    return true;
}

bool Manager::PRINT()	
{
    return graph->printGraph(&fout);
}

bool Manager::mBFS(char option, int vertex)	
{
    return BFS(graph, option, vertex);
}

bool Manager::mDFS(char option, int vertex)	
{
    return DFS(graph, option, vertex);
}

bool Manager::mDIJKSTRA(char option, int vertex)	
{
    return Dijkstra(graph, option, vertex);
}

bool Manager::mKRUSKAL()
{
    return Kruskal(graph);
}

bool Manager::mBELLMANFORD(char option, int s_vertex, int e_vertex) 
{
    return Bellmanford(graph, option, s_vertex, e_vertex);
}

bool Manager::mFLOYD(char option)
{
    return FLOYD(graph, option);
}

bool Manager::mKwoonWoon(int vertex) {
    return KWANGWOON(graph, vertex);
}

void Manager::printErrorCode(int n)
{
    fout << "========ERROR=======" << endl;
    fout << n << endl;
    fout << "====================" << endl << endl;
}


