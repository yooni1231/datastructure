#include <iostream>
#include <vector>
#include "GraphMethod.h"
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <list>
#include <utility>

using namespace std;

bool BFS(Graph* graph, char option, int vertex)
{
    if (vertex >= graph->getSize())
        return false;
    
    map<int, int> *tmp;
    tmp = new map<int, int>[graph->getSize()];//generate new map to get value from graph
    
    bool *visited = new bool[graph->getSize()];
    queue<int> q;//queue
    q.push(vertex);//push q with value vertex
    visited[vertex] = true;
    ofstream fout;
    
    fout.open("log.txt", ios::app);
    fout << "==========BFS===========" << endl;
    if (option == 'Y')
        fout << "Directed Graph BFS result" << endl;
    else
        fout << "Undirected Graph BFS result" << endl;
    fout << "startvertex: " << vertex << endl;
    
    while (!q.empty()) {
        int cur = q.front();
        q.pop();//pop q with rule of FIFO
        if (cur == vertex) {//if start vertex
            fout << cur;
        } else {
            fout << " -> " << cur;
        }
        
        graph->getAdjacentEdges(cur, tmp);//get cur vertex adjacent edges
        for (auto iter = tmp[cur].begin(); iter != tmp[cur].end(); iter++) {
            if (!visited[iter->first]) {
                q.push(iter->first);//push q with iter's first value
                visited[iter->first] = true;//set iter's first value visited
            }
        }
    }
    
    fout << "\n========================" << endl << endl;
    
    delete []visited;
    delete []tmp;
    return true;
}

bool DFS(Graph* graph, char option, int vertex)
{
    if (vertex >= graph->getSize())//if vertex is out of range
        return false;
    
    map<int, int> *tmp;//tmp is for each vertex which connect other vertex
    tmp = new map<int, int>[graph->getSize()];
    
    bool* visited = new bool[graph->getSize()];
    stack<int> s;//stack
    s.push(vertex);//push first vertex
    visited[vertex] = true;
    ofstream fout;
    
    fout.open("log.txt", ios::app);
    fout << "==========DFS===========" << endl;
    if (option == 'Y')
        fout << "Directed Graph DFS result" << endl;
    else
        fout << "Undirected Graph DFS result" << endl;
    
    fout << "startvertex: " << vertex << endl;
    fout << vertex;
    
    while (!s.empty()) {
        int cur = s.top();//cur is stack top
        s.pop();//pop s with rule of LIFO
        graph->getAdjacentEdges(cur, tmp);//get cur vertex adjacent edges
        for (auto iter = tmp[cur].begin(); iter != tmp[cur].end(); iter++) {
            int next = iter->first;
            if (!visited[next]) {
                fout << " -> " << next;
                s.push(cur);//push s with cur value
                s.push(next);//push s with cur next
                visited[next] = true;
                break;
            }
        }
    }
    fout << "\n========================" << endl << endl;
    
    delete[]visited;
    delete[]tmp;
    return true;
}

bool Kruskal(Graph* graph)
{
    map<int, int> *tmp, *tmp2;
    tmp = new map<int, int>[graph->getSize()];//generate new map
    
    ofstream fout;
    fout.open("log.txt", ios::app);
    
    int parent[1024];
    int cost = 0;//total cost
    int vertex = graph->getSize();//vertex_size
    
    for (int i = 0; i < vertex; i++) {
        parent[i] = i;
    }
    
    vector<pair<int, pair<int, int>>> sort_tmp;
    //get all weight(each edges twice)
    for (int i = 0; i < vertex; i++) {
        graph->getAdjacentEdges(i, tmp);//get i vertex adjacent edges
        
        if (tmp[i].empty() && graph->getSize() != 1) {
            delete []tmp;
            return false;
        }
        for (auto iter = tmp[i].begin(); iter != tmp[i].end(); iter++) {
            sort_tmp.push_back({iter->second, {i, iter->first}});//
        }
    }
    
    quicksort(&sort_tmp, 0, (int)sort_tmp.size() - 1);//sort by quicksort or insertion sort
    tmp2 = new map<int, int>[vertex];
    
    for (int i = 0; i < sort_tmp.size(); i++) {
        int tmp_cost = sort_tmp[i].first;
        int node1 = sort_tmp[i].second.first;//arrival node
        int node2 = sort_tmp[i].second.second;//destination node
        if (find_Root(node1, parent) != find_Root(node2, parent)) {//if node1's and node2's root is not equal
            union_Root(node1, node2, parent);//union each tree
            cost += tmp_cost;
            tmp2[node1].insert(std::make_pair(node2, sort_tmp[i].first));//tmp2[node1] insert pair of vertex and weight
            tmp2[node2].insert(std::make_pair(node1, sort_tmp[i].first));//tmp2[node2] insert pair of vertex and weight
        }
    }
    
    //print of kruskal
    fout << "=========Kruskal========" << endl;
    for (int i = 0; i < vertex; i++) {
        fout << "[" << i << "] ";
        for (auto it_ = tmp2[i].begin(); it_ != tmp2[i].end(); it_++) {
            fout << it_->first << "(" << it_->second << ") ";
        }
        fout << endl;
    }
    fout << "\ncost: " << cost << endl;
    fout << "========================" << endl << endl;
    
    delete []tmp;
    delete []tmp2;
    return true;
}

int find_Root(int node, int parent[]) {//find root function
    if (node == parent[node])
        return node;
    else
        return parent[node] = find_Root(parent[node], parent);//recursion
}

void union_Root(int node1, int node2, int parent[]) {
    node1 = find_Root(node1, parent);//get root
    node2 = find_Root(node2, parent);//get root
    if (node1 < node2)//if node2>node1 node node2's parent is node1
        parent[node2] = node1;
    else
        parent[node1] = node2;
}

void quicksort(vector<pair<int, pair<int, int>>> *arr, const int low, const int high) {
    if (low < high) {
        if (high - low + 1 <= 6) {//if range of sort is less than 7
            insertionSort(arr, low, high);//insertion sort
        } else {
            int pivot = partition(arr, low, high);//pivot is partition number
            quicksort(arr, low, pivot - 1);//recursion of lower
            quicksort(arr, pivot + 1, high);//recursion of higher
        }
    }
}

void insertionSort(vector<pair<int, pair<int, int>>> *arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        auto tmp = arr->at(i);//tmp is for change
        for (int j = i - 1; j >= low; j--) {
            if (arr->at(j).first > tmp.first) {//if arr's weight is greater than tmp
                arr->at(j + 1) = arr->at(j);//move to right
            } else {
                break;
            }
            arr->at(j) = tmp;//set tmp to arr->at(j)
        }
    }
}

int partition(vector<pair<int, pair<int, int>>> *arr, int low, int high) {//make partition for quick sort
    int pivot = arr->at(low).first;//pivot is most left arr
    int i = low + 1;
    int j = high;
    
    while (i < j) {
        while (pivot >= arr->at(i).first) {//if pivot>=arr->at(i)'s first value i++
            i++;
            if(i>high)
                break;
        }
        while (pivot < arr->at(j).first) {//if pivot<arr->at(j)'s first value j--
            j--;
            if(j<low)
                break;
        }
        if (i < j) {
            //for swap
            auto tmp = arr->at(i);
            arr->at(i) = arr->at(j);
            arr->at(j) = tmp;
        }
        
    }
    
    //swap high most left arr and pivot;
    auto tmp2 = arr->at(low);
    arr->at(low) = arr->at(j);
    arr->at(j) = tmp2;
    
    return j;
}


bool Dijkstra(Graph* graph, char option, int vertex)
{
    if (vertex >= graph->getSize())//if vertex is out of range
        return false;
    
    map<int, int> *tmp;
    tmp = new map<int, int>[graph->getSize()];//generate new map
    
    ofstream fout;
    fout.open("log.txt", ios::app);
    
    int *distance = new int[graph->getSize()];//generate new array
    int *prev = new int[graph->getSize()];//generate new array
    priority_queue<pair<int, int>> visited;//priority queue for visited vertex
    
    for (int i = 0; i < graph->getSize(); i++) {
        graph->getAdjacentEdgesDirect(i, tmp);//get all directed edges
        distance[i] = 999999;//set all 999999INITY
        prev[i] = 999999;//set all 999999INITY
    }
    
    //check negative number
    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it_ = tmp[i].begin(); it_ != tmp[i].end(); it_++) {
            if (it_->second < 0) {
                delete []tmp;
                delete []distance;
                delete []prev;
                return false;
            }
        }
    }
    
    distance[vertex] = 0;//k=0
    visited.push(make_pair(vertex, 0));
    //loop while visited.empty()
    
    while (!visited.empty()) {
        int cur = visited.top().first;
        int cost = -visited.top().second;
        visited.pop();//pop visited
        for (auto it_ = tmp[cur].begin(); it_ != tmp[cur].end(); it_++) {
            int to = it_->first;
            int to_cost = it_->second + cost;
            if (to_cost < distance[to]) {
                distance[to] = to_cost;//to is destination vertex
                prev[to] = cur;//cur is arrival vertex
                visited.push(make_pair(to, -to_cost));//make pair and push
            }
        }
    }
    
    //print for Dijkstra
    fout << "========Dijkstra========" << endl;
    if (option == 'Y')
        fout << "Directed Graph Dijkstra result" << endl;
    else
        fout << "Undirected Graph Dijkstra result" << endl;
    
    fout << "startvertex: " << vertex << endl;
    
    for (int i = 0; i < graph->getSize(); i++) {
        if (i == vertex)
            continue;
        
        fout << "[" << i << "] ";
        if (distance[i] == 999999) {
            fout << "x" << endl;
        } else {
            fout << vertex;
            fout.close();
            find_path(vertex, i, distance, prev);
            fout.open("log.txt", ios::app);
            fout << " (" << distance[i] << ")" << endl;
        }
    }
    
    fout << "========================" << endl << endl;
    fout.close();
    
    delete []tmp;
    delete []distance;
    delete []prev;
    return true;
}

bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex) 
{
    if (s_vertex >= graph->getSize() || e_vertex >= graph->getSize())//if out of range
        return false;
    map<int, int> *tmp;
    tmp = new map<int, int>[graph->getSize()];//generate new map
    ofstream fout;
    fout.open("log.txt", ios::app);
    
    int *distance = new int[graph->getSize()];//generate new array
    int *prev = new int[graph->getSize()];//generate new array
    for (int i = 0; i < graph->getSize(); i++) {
        graph->getAdjacentEdgesDirect(i, tmp);//get all directed edges
        distance[i] = 999999;//reset all distance and prev infinity
        prev[i] = 999999;
    }
    
    distance[s_vertex] = 0;//k=0
    for (auto it_ = tmp[s_vertex].begin(); it_ != tmp[s_vertex].end(); it_++) {//k=1
        distance[it_->first] = it_->second;
        prev[it_->first] = s_vertex;
    }
    
    for (int i = 2; i < graph->getSize(); i++) {//k=2~k=graph size
        for (int j = 0; j < graph->getSize(); j++) {
            for (auto it_ = tmp[j].begin(); it_ != tmp[j].end(); it_++) {
                int to = it_->first;
                int cost = it_->second;
                
                if (distance[j] == 999999)//if not connect
                    continue;
                if (distance[to] > distance[j] + cost) {//if greater than sum
                    distance[to] = distance[j] + cost;
                    prev[to] = j;
                }
            }
        }
    }
    //detection of negative cycle
    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it_ = tmp[i].begin(); it_ != tmp[i].end(); it_++) {
            int to = it_->first;
            int cost = it_->second;
            
            if (distance[i] == 999999)
                continue;
            //if distance gonna change
            if (distance[to] > distance[i] + cost) {
                delete []tmp;
                delete []prev;
                delete []distance;
                return false;//return false(negative cycle)
            }
        }
    }
    
    //if direction is not allow
    if (distance[e_vertex] == 999999) {
        fout << "======Bellman-Ford======" << endl;
        if (option == 'Y')
            fout << "Directed Graph Bellman-Ford result" << endl;
        else
            fout << "Undirected Graph Bellman-Ford result" << endl;
        fout << "x" << endl;
        fout << "=======================" << endl << endl;
        return true;
    }
    
    //find path
    fout << "======Bellman-Ford======" << endl;
    if (option == 'Y')
        fout << "Directed Graph Bellman-Ford result" << endl;
    else
        fout << "Undirected Graph Bellman-Ford result" << endl;
    fout << s_vertex;
    fout.close();
    find_path(s_vertex, e_vertex, distance, prev);
    fout.open("log.txt", ios::app);
    fout << "\ncost: " << distance[e_vertex] << endl;
    fout << "=======================" << endl << endl;
    
    delete []tmp;
    delete []distance;
    delete []prev;
    return true;
}

void find_path(int s, int e, int dist[], int prev[]) {
    ofstream fout;
    fout.open("log.txt", ios::app);
    
    if (s == e) {
        return;
    }
    
    find_path(s, prev[e], dist, prev);//recursion of find_path
    fout << " -> " << e;
    return;
}

bool FLOYD(Graph* graph, char option)
{
    map<int, int> *tmp;
    tmp = new map<int, int>[graph->getSize()];//generate new map
    
    ofstream fout;
    fout.open("log.txt", ios::app);
    int **tmpmat = new int *[graph->getSize()];//generate new double pointer array
    
    for (int i = 0; i < graph->getSize(); i++) {
        graph->getAdjacentEdgesDirect(i, tmp);
    }
    
    for (int i = 0; i < graph->getSize(); i++) {
        tmpmat[i] = new int[graph->getSize()];//generate pointer array
        
        for (int j = 0; j < graph->getSize(); j++) {
            tmpmat[i][j] = 999999;//set all infinity
            if (i == j)
                tmpmat[i][j] = 0;//direction of itself =0
        }
    }
    
    for (int i = 0; i < graph->getSize(); i++) {
        for (auto it_ = tmp[i].begin(); it_ != tmp[i].end(); it_++) {
            tmpmat[i][it_->first] = it_->second;//get tmpmat value from tmp.second
        }
    }
    
    //FLOYD
    for (int i = 0; i < graph->getSize(); i++) {
        for (int j = 0; j < graph->getSize(); j++) {
            for (int k = 0; k < graph->getSize(); k++) {
                if(tmpmat[i][k]==999999||tmpmat[j][i]==999999)
                    continue;
                
                int temp = tmpmat[j][i] + tmpmat[i][k];
                if (temp < tmpmat[j][k])
                    tmpmat[j][k] = temp; //set tmpmat[j][k]=temp;
            }
        }
    }
    
    //detection of negative cycle
    for (int i = 0; i < graph->getSize(); i++) {
        if (tmpmat[i][i] < 0) {
            delete []tmp;
            
            for(int i=0;i< graph->getSize();i++){
                delete[]*(tmpmat+i);
            }
            delete []tmpmat;
            return false;
        }
    }
    
    //print FLOYD
    fout << "==========FLOYD==========" << endl;
    if (option == 'Y')
        fout << "Directed Graph FLOYD result" << endl;
    else
        fout << "Undirected Graph FLOYD result" << endl;
    fout << '\t';
    for (int i = 0; i < graph->getSize(); i++) {
        fout << "[" << i << "]" << '\t';
    }
    fout << endl;
    
    for (int i = 0; i < graph->getSize(); i++) {
        fout << "[" << i << "]";
        for (int j = 0; j < graph->getSize() && fout << '\t'; j++) {
            if (tmpmat[i][j] == 999999) {
                fout << "\tx ";
            } else {
                fout << "\t" << tmpmat[i][j];
            }
        }
        fout << endl;
    }
    
    fout << "=========================" << endl << endl;
    
    delete []tmp;
    for(int i=0;i< graph->getSize();i++){
        delete[]*(tmpmat+i);
    }
    delete []tmpmat;
    return true;
}

bool KWANGWOON(Graph* graph, int vertex) {
    if (vertex >= graph->getSize())//if vertex is out of range
        return false;
    
    map<int, int> *tmp;//tmp is for each vertex which connect other vertex
    tmp = new map<int, int>[graph->getSize()];
    
    bool* visited = new bool[graph->getSize()];
    stack<int> s;//stack
    s.push(1);//push first vertex
    visited[1] = true;
    ofstream fout;
    
    fout.open("log.txt", ios::app);
    fout << "=======KWANGWOON========" << endl;
    fout << "startvertex: " << 1 << endl;
    fout << 1;
    
    while (!s.empty()) {
        int cur = s.top();//cur is stack top
        s.pop();//pop s with rule of LIFO
        graph->getAdjacentEdges(cur, tmp);//get cur vertex adjacent edges
        for (auto iter = tmp[cur].begin(); iter != tmp[cur].end(); iter++) {
            int next = iter->first;
            if (!visited[next]) {
                fout << " -> " << next;
                s.push(cur);//push s with cur value
                s.push(next);//push s with cur next
                visited[next] = true;
                break;
            }
        }
    }
    fout << "\n========================" << endl << endl;
    
    delete[]visited;
    delete[]tmp;
    return true;
}
