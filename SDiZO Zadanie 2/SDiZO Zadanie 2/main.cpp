

#include "stdafx.h"
#include <cstdio>
#include <utility>
#include <ctime>
#include <cmath>
#include "IncidenceMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "Vertex.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "FibonacciHeap.h"
#include "Vector.h"


using namespace SDZ;


int main()
{
	
	AdjacencyListGraph matr = AdjacencyListGraph(9,false,false);
	matr.AddEdge(0, 1, 4);
	matr.AddEdge(0, 7, 8);
	matr.AddEdge(1, 2, 8);
	matr.AddEdge(1, 7, 11);
	matr.AddEdge(2, 3, 7);
	matr.AddEdge(2, 8, 2);
	matr.AddEdge(2, 5, 4);
	matr.AddEdge(3, 4, 9);
	matr.AddEdge(3, 5, 14);
	matr.AddEdge(4, 5, 10);
	matr.AddEdge(5, 6, 2);
	matr.AddEdge(6, 7, 1);
	matr.AddEdge(6, 8, 6);
	matr.AddEdge(7, 8, 7);
	//matr.DisplayEdges();
	//matr.PrimMST();
	

	AdjacencyListGraph matr2 = AdjacencyListGraph(200,1, false, true);
	matr2.SetMaxWeight(5);
	//matr2.DisplayMapWithId();
	//matr2.DisplayWeights();
	//std::cout << std::endl << (double)matr2.edges_ / matr2.max_edges_ << std::endl;
	//DTS::List<uint> path = matr2.AStarSearch(0, 6,EUCLIDEAN);

	//path.Display();
	//matr2.DisplayEdges();
	//matr2.DisplayMapWithId();
	//matr2.DisplayMap();
	//matr2.ClearMap();

	matr2.PrimMST();


	getchar();
    return 0;
}