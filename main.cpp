#include <iostream>
#include <stdint.h>
#include <vector>
#include <list>

class Vertex {
private:
	/*
		color
		= 0 -> nao visitado
		= 1 -> visitado, nao terminado
		= 2 -> terminado
	*/
	int color;
	int distance;
	std::list<Vertex*> adj;
public:

	Vertex(){
		color = 0;
		distance = -1;
		adj = std::list<Vertex*>();
	}
	~Vertex(){}

	void setDistance(int _distance){ distance = _distance; }
	int getDistance(){ return distance; }
	
	void setGray() { color = 1; }
	void setBlack() { color = 2; }
	bool isWhite() { return color == 0; }

	void addAdjacent(Vertex* v){
		adj.push_back(v);
	}
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

		for (int i = 0; i < size; i++)
			dist_count[i] = 0;

		for (int i = 0; i < n; i++){
			verts.insert(verts.end(),Vertex());
			adj[i] = std::list<int>();
		}
	}
	~Graph(){
		//delete adj;
		//delete dist_count;
	}
	/* Adicionar edge de W -> V */
	void addEdge(int w, int v){
		//std::cout << "Edge between " << w << " and " << v << "\n";
		verts[w].addAdjacent(&verts[v]);
		verts[v].addAdjacent(&verts[w]);
	}
	
	void printDebugInfo(){
		std::cout << "Number of vertex: " << size << "\n";
		std::cout << "Edges: \n";
		std::list<int>::const_iterator it;
		for (int i = 0; i < size; i++){
			for (it = adj[i].begin(); it != adj[i].end(); ++it){
				std::cout << "Edge between " << i << " and " << (*it) << " \n";
			}
		}
	}

	void printCountedOutput(){
		std::cout << max_dist << "\n";
		for (int i = 1; i <= max_dist; i++){
			std::cout << dist_count[i] << "\n";
		}
	}

	void BFS(int start){
		
		std::list<Vertex*> queue;

		Vertex* erdos_vertex = &verts[start-1];
		erdos_vertex->setGray();
		erdos_vertex->setDistance(0);
		queue.push_back(erdos_vertex);

		while (queue.size() > 0){

			Vertex* current_vertex = queue.front();
			queue.pop_front();
			Vertex* adjacent_vertex = current_vertex->getNextAdjacent();

			while (adjacent_vertex != NULL){
				if (adjacent_vertex->isWhite()){

					adjacent_vertex->setGray();
					adjacent_vertex->setDistance(current_vertex->getDistance() + 1);
					queue.push_back(adjacent_vertex);

					dist_count[adjacent_vertex->getDistance()]++;
					max_dist = adjacent_vertex->getDistance();

				}
				adjacent_vertex = current_vertex->getNextAdjacent();
			}
			current_vertex->setBlack();
		}

	}
};


int main(){

	int num_vert, num_edge, vert1, vert2, erdos;
	std::cin >> num_vert >> num_edge;
	Graph g = Graph(num_vert);
	std::cin >> erdos;
	for (int i = 0; i < num_edge; i++){
		std::cin >> vert1 >> vert2;
		g.addEdge(vert1-1, vert2-1);
	}
	g.BFS(erdos);
	g.printCountedOutput();
	return 0;
}