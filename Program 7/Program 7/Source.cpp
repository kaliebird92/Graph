#include "Graph.h"

int main()
{
	//Instantiate Graph object
	Graph graph; 

	//Create variables
	ifstream inputFile; 
	string fileName, inputString, sourceCity, destinationCity; 
	int miles, cost, size = 0; 
	const int STRING_SIZE = 50; 

	//Print student information
	cout << "Kalie Walker, CS2420-002, Program 7" << endl; 

	//Prompt user for file name
	//cout << "\nEnter file name: "; 

	//Open file
	do
	{
		//getline(cin, fileName);
		inputFile.open("p7data.txt");
		if (!inputFile && fileName != "quit")
		{
			cout << "\nCannot open file " << fileName << ".\n";
			cout << "\nEnter a new file name or \"quit\" to quit: ";
		}
	} while (!inputFile && fileName != "quit");

	//Read information into list of Info buckets
	do
	{
		if (inputFile.good())
		{
			//Read in line from file
			inputString = ""; 
			getline(inputFile, inputString); 

			//Parse 
			int position = 0; 
			string delimiter = " "; 
			int index = 0; 

			array<string, STRING_SIZE> line; 

			while ((position = inputString.find(delimiter)) != string::npos)
			{
				line[index++] = inputString.substr(0, position);
				inputString.erase(0, position + delimiter.length());
			}
			line[index++] = inputString;
			position = 0;
			
			//Store parsed values
			sourceCity = line[0]; 
			destinationCity = line[1]; 
			miles = stoi(line[2]); 
			cost = stoi(line[3]); 

			//Insert parsed values into Info bucket
			graph.InitialInsert(sourceCity, destinationCity, miles, cost, size); 

			//Insert source city into vertex bucket
			graph.InitializeVertices(size++);
		}
	} while (!inputFile.eof()); 

	//Sort vertices
	graph.SortVertices(); 

	//Build graph
	graph.BuildGraph(); 

	//Print graph
	graph.PrintGraph(); 

	graph.CreateAdjacencyList();

	graph.GetShortestPath("SLC");

	system("pause"); 
	return 0; 
}