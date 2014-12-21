#include "Graph.h"

Graph::Graph() {}

void Graph::InitialInsert(string sourceVertex, string destination, int distance, int price, int index)
{
	InfoBuckets[index] = new InitialInfo(); 
	InfoBuckets[index]->sourceCity = sourceVertex; 
	InfoBuckets[index]->destinationCity = destination; 
	InfoBuckets[index]->miles = distance; 
	InfoBuckets[index]->cost = price; 
}

bool Graph::IsDuplicate(string sourceVertex)
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		if (sourceVertex == Vertices[i].cityName)
			return true;
	}
	return false; 
}

bool Graph::SortByCity(Vertex a, Vertex b)
{
	return (a.cityName < b.cityName);
}

void Graph::SortVertices()
{
	sort(Vertices.begin(), Vertices.end(), &Graph::SortByCity);
}

void Graph::InitializeVertices(int index)
{	
	//If IsDuplicate returns false
	if (!IsDuplicate(InfoBuckets[index]->sourceCity))
	{
		Vertex * newVertex = new Vertex(); 
		newVertex->cityName = InfoBuckets[index]->sourceCity; 

		Vertices.push_back(*newVertex); 
	}
}

Graph::Vertex * Graph::GetVertexByCity(string cityName)
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		if (Vertices[i].cityName == cityName)
		{
			return &Vertices[i]; 
		}
	}
	return NULL; 
}

void Graph::BuildGraph()
{
	for (int i = 0; i < SIZE; i++) //Change size to count
	{
		Vertex * sourceCity = GetVertexByCity(InfoBuckets[i]->sourceCity); 
		Vertex * destinationCity = GetVertexByCity(InfoBuckets[i]->destinationCity); 

		Edge * newEdge = new Edge(); 
		newEdge->destinationCity = destinationCity; 
		newEdge->miles = InfoBuckets[i]->miles; 
		newEdge->cost = InfoBuckets[i]->cost;

		sourceCity->adjVertices.push_back(*newEdge); 
	}
}

void Graph::CreateAdjacencyList() 
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		for (int j = 0; j < Vertices[i].adjVertices.size(); j++)
		{
			Edges.push_back(Vertices[i].adjVertices[j]); 
		}
	}
}

//class CompareGreater
//{
//public:
//	bool const operator()(Graph::Edge &EdgeX, Graph::Edge &EdgeY)
//	{
//		return (EdgeX.cost > EdgeY.cost); 
//	}
//};

int Graph::GetIndex(string cityName)
{
	for (int i = 0; i < Vertices.size(); i++)
	{
		if (Vertices[i].cityName == cityName)
			return i; 
	}
	return -1; 
}

void Graph::Dijkstra(Vertex sourceVertex, vector<Vertex> vertices, vector<weight> &minDistance, vector<string> &visited)
{
	int numberOfCities = vertices.size();
	minDistance.clear();
	minDistance.resize(numberOfCities, maxWeight);
	minDistance[GetIndex(sourceVertex.cityName)] = 0;
	visited.clear();
	visited.resize(numberOfCities);
	set<pair<weight, string>> vertexQueue;
	vertexQueue.insert(make_pair(minDistance[GetIndex(sourceVertex.cityName)], sourceVertex.cityName));


	while (!vertexQueue.empty())
	{
		weight dist = vertexQueue.begin()->first;
		string u = vertexQueue.begin()->second;
		vertexQueue.erase(vertexQueue.begin());

		// Visit each edge exiting u
		const vector<Edge> &neighbors = vertices[GetIndex(u)].adjVertices;
		for (vector<Edge>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			string v = (neighbor_iter->destinationCity->cityName);
			weight cost = neighbor_iter->cost;
			weight distanceThroughU = dist + cost;
			if (distanceThroughU < minDistance[GetIndex(v)])
			{
				vertexQueue.erase(make_pair(minDistance[GetIndex(v)], v));
				minDistance[GetIndex(v)] = distanceThroughU;
				visited[GetIndex(v)] = u;
				vertexQueue.insert(make_pair(minDistance[GetIndex(v)], v));
			}
		}
	}
}

vector<Graph::Vertex> Graph::DijkstraGetShortestPathTo(Vertex vertex, const vector<string> &visited)
{
	vector<Vertex> path;
	for (; GetIndex(vertex.cityName) != -1; vertex.cityName = visited[GetIndex(vertex.cityName)])
		path.push_back(vertex);
	return path;
}

void Graph::GetShortestPath(string startingAirport)
{
	//for (int i = 0; i < cityCount; i++)
	//{

	//}
	vector<weight> weights;
	vector<string> visited;
	Dijkstra(*GetVertexByCity(startingAirport), Vertices, weights, visited);

	cout << endl;
	for (int i = 0; i < visited.size(); i++)
	{
		vector <Vertex> path = DijkstraGetShortestPathTo(Vertices[i], visited);


		cout << "Paths from " << Vertices[i].cityName << "\n-------------------\n";
		for (int j = 0; j < path.size(); j++)
		{
			cout << path[j].cityName << "->";
		}
		cout << "\nTotal cost: $" << weights[i];
		cout << "\n\n";
	}
	
	vector <Vertex> path = DijkstraGetShortestPathTo(Vertices[2], visited);
	int i = 0;
}

void Graph::PrintGraph()
{
	//cout << "--------------------------------------------------------------------------------" << endl; 
	//cout << "DIRECT FLIGHTS:" << endl; 
	//cout << "\nSource\t" << "Destination\t" << "Mileage\t\t" << "Cost" << endl; 

	//for (int i = 0; i < SIZE; i++)
	//{
	//	cout << "\t" << *(Vertices[i]->adjVertices[i].destinationCity)
	//		<< "\t" << Vertices[i]->adjVertices[i].miles
	//		<< "\t\t" << Vertices[i]->adjVertices[i].cost
	//		<< endl; 
	//}

	//cout << "\numberOfCities--------------------------------------------------------------------------------" << endl;
}

Graph::~Graph()
{
}
