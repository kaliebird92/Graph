#ifndef MAIN_WALKER_GRAPH
#define MAIN_WALKER_GRAPH
#include <cstdlib>
#include <iostream>
#include <fstream> 
#include <string> 
#include <array> 
#include <vector>
#include <queue>
#include <set>

using namespace std; 

class Graph
{
public:
	static int const SIZE = 15; 
	int cityCount = 0;
	typedef double weight; 
	const weight maxWeight = std::numeric_limits<double>::infinity();

	struct Vertex; 
	struct Edge
	{
		Vertex *destinationCity; 
		int cost;
		int miles;
	};
	struct Vertex
	{
		string cityName;
		vector<Edge> adjVertices;
	};
	struct InitialInfo
	{
		string sourceCity; 
		string destinationCity;
		int miles; 
		int cost; 
	};
	InitialInfo* InfoBuckets[SIZE]; 
	vector<Vertex> Vertices;
	vector<Edge> Edges; 
public:
	Graph(); 
	void InitialInsert(string, string, int, int, int); 
	bool IsDuplicate(string); 
	static bool SortByCity(Vertex, Vertex); 
	void SortVertices(); 
	void InitializeVertices(int); 
	Vertex * GetVertexByCity(string); 
	void BuildGraph(); 
	void CreateAdjacencyList(); 
	int GetIndex(string); 
	void Dijkstra(Vertex, vector<Vertex>, vector<weight>&, vector<string>&); 
	vector<Vertex> DijkstraGetShortestPathTo(Vertex, const vector<string>&); 
	void GetShortestPath(string); 
	void PrintGraph(); 
	~Graph();
};
#endif; 
