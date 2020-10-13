#include "graphMatrix.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main() {  

    string filename;
    ifstream digraphFile;
	int numVertices = 0;
	int vertex1;
	int vertex2;
	int startingVertex;
	int currentVertex;
	bool hasCycle = false;
	int index = 0;
	int* sorted;
    
    cout << "\nEnter the name of your file that contains the graph vertices: ";
    
    getline(cin, filename);
    
    digraphFile.open(filename.c_str());
    
    if(!digraphFile.is_open())
    {
        cout << "\n\nFile could not be opened.";
        exit(EXIT_FAILURE);
    }
    else
    {	        
		digraphFile >> numVertices;
		
		//create the matrix object
		graphMatrix* vm = new graphMatrix(numVertices);
		
		while(digraphFile >> vertex1)
        {
			digraphFile >> vertex2;
			//add edge to the adjacency matrix
			vm->addEdge(vertex1, vertex2);
		}
		digraphFile.close();
		cout << "\nAdjency Matrix: " << endl;
		vm->printGraph();
		cout << "\n\nNow topologically sorting the graph..." << endl;
		
		//stack object for DFS
		Stack<int> DFS_stack;
		
		//dynamically allocate bool array
		bool* visited = new bool[numVertices]; //track visited nodes
		
		sorted = new int [numVertices]; //topologically sorted array
		index = numVertices - 1;

		for(int i = 0; i < numVertices; i++)
		{
			visited[i] = false;
		}
		
		startingVertex = vm->getFirstVertex();
		DFS_stack.push(startingVertex);
		//cout << "\npushing: " << startingVertex << endl;
		
		while(!DFS_stack.isEmpty())
		{
			DFS_stack.peek(currentVertex);
			visited[currentVertex] = true;
			
			bool restart = false;
			for(int i = 0; i < numVertices || restart == true; i++)
			{
				//cout << "\nWe are now at " << currentVertex << endl;
				//cout << "\nwe are now looking at " << i << endl;
				if(restart == true)
				{
					i = 0;
					restart = false;					
				}
					
				if(!visited[i] && vm->isThereAnEdge(currentVertex, i))
				{
					DFS_stack.push(i);
					//cout << "\npushing: " << i << endl;
					visited[i] = true;
						
					//if(!visited[i] && vm->isThereAnEdge(currentVertex, i) == false)
					//{
						restart = true;
						currentVertex = i;
					//}
				}
					
				if(visited[i] && vm->isThereAnEdge(currentVertex, i) && DFS_stack.find(i) == true)
				{
					hasCycle = true;
					break;
				}
			}
			DFS_stack.pop(currentVertex);
			//cout << "\npopping: " << currentVertex << endl;
			
			sorted[index] = currentVertex;
			index--;
		}
     }
	 
if(hasCycle == true)
{
	cout << "\nCycle Detected!  Cannot sort topologically!  Sorry, sucker!" << endl;
}
else
{
	cout << "\n";
	for(int i = 0; i < numVertices; i++)
	{
		cout << sorted[i] << " ";
	}
	cout << endl;
}
	 
cout <<  endl;
system("pause");
return 0;
}