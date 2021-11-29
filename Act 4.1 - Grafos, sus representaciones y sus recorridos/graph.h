/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*
*  Extiende este archivo para completar tu soución.

*  Author: Daniel Rodriguez Figueroa

*  A01612889

*  correcion act 4.1

*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int> *adjList;
    int *adjMatrix;

public:

    Graph();

    void loadGraphMat(const string&, int, int);
    void loadGraphList(const string&, int, int);
	void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);

    string printAdjMat();
	string printAdjMat_clean();
    string printAdjList();
    string DFS(int, int);
    string BFS(int, int);

    void DFSHelper(int, int, stack<int> &, list<int> &, vector<vector<int> > &, stringstream &);
    void BFSHelper(int, int, queue<int> &, list<int> &, vector<vector<int> > &, stringstream &);
    static void printPath(vector<vector<int> > &, int, int, stringstream &);
    static void printVisited(list<int>, stringstream &);
    static bool contains(list<int>, int);
    void sortAdjList();

};

Graph::Graph() {
    edgesList = edgesMat = nodes = 0;
}

void Graph::loadGraphMat(const string &file_name, int a, int b) {
    adjMatrix = new int[a * b];
    nodes = a;
    for (int i = 0; i < a * b; i++)
        adjMatrix[i] = 0;
		string line;
		ifstream archivo(file_name);
		int u, v;
		if (archivo.is_open()) {
			while (getline(archivo, line)) {
				u = stoi(line.substr(1, 1));
				v = stoi(line.substr(4, 1));
				addEdgeAdjMatrix(u, v);
			}
			archivo.close(); 
		} else	cout << "Unable to open file";
}

void Graph::loadGraphList(const string &file_name, int a, int b) {
    nodes = a;
    adjList = new vector<int>[nodes];

    string line;
    ifstream archivo(file_name);
    int u, v;
    if (archivo.is_open()) {
        while (getline(archivo, line)) {
              u = stoi(line.substr(1, 1));
              v = stoi(line.substr(4, 1));
              addEdgeAdjList(u, v);
        }
        archivo.close();
    } else{
		cout << "Unable to open file";
	}
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edgesMat++;
}

string Graph::printAdjList(){
	sortAdjList();
	stringstream aux;
	for (int i = 0; i < nodes; i++){
		aux << "vertex "
				<< i << " :";
		for (int j = 0; j < adjList[i].size(); j ++){
							aux << " " << adjList[i][j];
				}
		aux << " ";
	}
	return aux.str();

}

string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
		}
	}
    return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

string Graph::DFS(int start, int target) {
    stringstream aux;

    stack<int> my_stack;
    list<int> visited;
    vector<vector<int> > paths(nodes, vector<int>(1, -1));
    my_stack.push(start);

    DFSHelper(start, target, my_stack, visited, paths, aux);
    printPath(paths, start, target, aux);

    return aux.str();
}

void Graph::DFSHelper(int current, int target, stack<int> &stack, list<int> &visited, vector<vector<int> > &paths, stringstream &aux) {

    if (current == target){
		printVisited(visited, aux);
	} else if (stack.empty()){
		aux << "node not found";
    } else {
        current = stack.top();
        stack.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++){
            if (!contains(visited, adjList[current][i])) {
                stack.push(adjList[current][i]);
                paths[adjList[current][i]][0] = current;
            }
		}
        DFSHelper(current, target, stack, visited, paths, aux);
    }
}

string Graph::BFS(int start, int target) {
    stringstream aux;

    queue<int> queue;
    list<int> visited;
    vector<vector<int> > paths(nodes, vector<int>(0));
    queue.push(start);

    BFSHelper(start, target, queue, visited, paths, aux);
    printPath(paths, start, target, aux);

    return aux.str();
}

void Graph::BFSHelper(int current, int target, queue<int> &queue, list<int> &visited, vector<vector<int> > &paths, stringstream &aux) {

    if (current == target){
		printVisited(visited, aux);
	} else if (queue.empty()){
		aux << "";
     } else {
        current = queue.front();
        queue.pop();
        visited.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!contains(visited, adjList[current][i])) {
                queue.push(adjList[current][i]);
                paths[adjList[current][i]].push_back(current);
            }
		}
        BFSHelper(current, target, queue, visited, paths, aux);
    }
}

void Graph::printVisited(list<int> visited, stringstream &aux) {
    aux << "visited: ";
    while (!visited.empty()) {
        aux << visited.front() << " ";
        visited.pop_front();
    }
}

void Graph::printPath(vector<vector<int> > &path, int start, int target, stringstream &aux) {
    aux << "path: ";
    int node = path[target][0];

    stack<int> reverse;
    reverse.push(target);

    while (node != start) {
        reverse.push(node);
        node = path[node][0];
    }

    reverse.push(start);
    while (!reverse.empty()) {
        aux << reverse.top();
        reverse.pop();
        if (!reverse.empty()){
			aux << " ";
		}
    }
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(), adjList[i].end());
	}
}

bool Graph::contains(list<int> lista, int node) {
    list<int>::iterator it;
    it = find(lista.begin(), lista.end(), node);

    if (it != lista.end()){
		return true;
	} else {
		return false;
	}
}
#endif