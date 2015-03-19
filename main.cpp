/**
 ASA
 main.cpp
 Purpose: Calculates the Erdos distance
 
 @author Grupo 14 Alameda
 @version 1.0 19/03/15
 */

#include <iostream>
#include <stdint.h>
#include <vector>
#include <list>

class Vertex {
private:
    
	int color;
	int distance;
	std::list<Vertex*> adj;
public:

	Vertex(){
		color = 0;                  // initialized white
		distance = -1;              // initialized at infinity
		adj = std::list<Vertex*>(); // connected list of the adjacencies of a vertex
	}
    
	~Vertex(){}
    
    /* DISTANCE */
	void setDistance(int _distance){ distance = _distance; }
	int getDistance(){ return distance; }
	
    /* COLOR */
	void setGray() { color = 1; }
	bool isWhite() { return color == 0; }

    /* CONNECTIONS */
	void addAdjacent(Vertex* v){ adj.push_back(v); }
    
	Vertex* getNextAdjacent(){
		Vertex* v = NULL;
		if (adj.size() > 0){
			v = adj.back();
			adj.pop_back();
		}
		return v;
	}
};

class Graph {
private:

	int size, max_dist;
	std::vector<Vertex> verts;
	std::list<int>* adj;
	int* dist_count;

public:
	Graph(int n){
		size = n;
		adj = new std::list<int>[n];
        dist_count = new int[size];
        
        /* INIT */
		for (int i = 0; i < size; ++i)
            dist_count[i] = 0;

		for (int i = 0; i < n; ++i){
			verts.insert(verts.end(),Vertex());
			adj[i] = std::list<int>();
		}
	}
    
	~Graph(){
        delete[] adj;
        delete[] dist_count;
    }
    
	void addEdge(int w, int v){         // undirected graph, needs to have both connections
		verts[w].addAdjacent(&verts[v]);
		verts[v].addAdjacent(&verts[w]);
	}

	void printCountedOutput(){
		std::cout << max_dist << "\n";
		for (int i = 1; i <= max_dist; ++i){
			std::cout << dist_count[i] << "\n";
		}
	}

    /* BFS without black color and predecessors */
	void BFS(int start){
		
		std::list<Vertex*> queue;
        
        /* INIT ERDOS */
		Vertex* erdos_vertex = &verts[start-1];
		erdos_vertex->setGray();
		erdos_vertex->setDistance(0);
		queue.push_back(erdos_vertex);
        
        /* MAIN CICLE */
		while (!queue.empty()){

			Vertex* current_vertex = queue.front();
			queue.pop_front();                          // dequeue
			Vertex* adjacent_vertex = current_vertex->getNextAdjacent();
            
			while (adjacent_vertex != NULL){
				if (adjacent_vertex->isWhite()){

					adjacent_vertex->setGray();         // mark vertex as visited/grey
					adjacent_vertex->setDistance(current_vertex->getDistance() + 1);
					queue.push_back(adjacent_vertex);   // enqueue

					++dist_count[adjacent_vertex->getDistance()];
					max_dist = adjacent_vertex->getDistance();

				}
				adjacent_vertex = current_vertex->getNextAdjacent(); // get next vertex
			}
		}

	}
};


int main(){
	int num_vert, num_edge, vert1, vert2, erdos;
    
    /* Get Info and Initialize Erdos and Connections*/
	std::cin >> num_vert >> num_edge;
	Graph g = Graph(num_vert);
	std::cin >> erdos;
	for (int i = 0; i < num_edge; ++i){
		std::cin >> vert1 >> vert2;
		g.addEdge(vert1-1, vert2-1);
	}
    
    /* Run BFS starting at Erdos  and print output*/
	g.BFS(erdos);
	g.printCountedOutput();
    
	return 0;
}