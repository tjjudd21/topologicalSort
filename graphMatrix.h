#ifndef GRAPHMATRIX_H
#define GRAPHMATRIX_H

#include <iostream>
#include <iomanip>
using namespace std;

class graphMatrix 
{
	private:
		int** vertexMatrix;
		int numVertices;
		int numEdges;
		
	public:
		graphMatrix(int numVertices)
		{
			this->numVertices = numVertices;
			vertexMatrix = new int* [numVertices];
			for(int i = 0; i < numVertices; i++)
			{
				vertexMatrix[i] = new int [numVertices];
				
				for(int j = 0; j < numVertices; j++)
				{
					vertexMatrix[i][j] = 0;
				}
			}
		}
		
		~graphMatrix() //destructor
		{
			for(int i = 0; i < numVertices; i++)
			{
				delete vertexMatrix[i];
			}
			delete [] vertexMatrix;
		}
		
		void addEdge(int v1, int v2)
		{	
			vertexMatrix[v1][v2] = 1;
		}
		
		void printGraph()
		{
			for(int i = 0; i < numVertices; i++)
			{
				for(int j = 0; j < numVertices; j++)
				{
					cout << setw(5) << vertexMatrix[i][j] << " ";
				}
				cout << endl;
			}
		}
		
		int getFirstVertex()
		{
			bool checker;
			int columnIndex = 0;
			
			for(int j = 0; j < numVertices; j++)
			{
				checker = false;
				for(int i = 0; i < numVertices; i++)
				{
					if(vertexMatrix[i][j] == 1)
					{
						checker = true;
					}
				}
				if(checker == false)
				{
					columnIndex = j;
				}
			}
			return columnIndex;
		}
		
		bool isThereAnEdge(int r, int c)
		{
			if(vertexMatrix[r][c] == 1)
				return true;
			else
				return false;
		}
};
#endif