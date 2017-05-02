// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <utility>
#include <ctime>
#include "IncidenceMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "Vertex.h"
#include "Queue.h"



using namespace SDZ;

int main()
{
	IncidenceMatrixGraph matr1 = IncidenceMatrixGraph(4, 5);
	matr1.AddEdge(0, 3, 6);
	matr1.AddEdge(1, 0, 5);
	matr1.AddEdge(1, 3, 7);
	matr1.AddEdge(1, 2, 24);
	matr1.AddEdge(2, 0, 9);
	matr1.DisplayMatrix();
	matr1.DisplayWeights();

	AdjacencyListGraph matr = AdjacencyListGraph(14,true);
	matr.AddEdge(0, 1, 6);
	matr.AddEdge(0, 2, 5);
	matr.AddEdge(0, 8, 7);
	matr.AddEdge(1, 4, 24);
	matr.AddEdge(1, 5, 9);
	matr.AddEdge(1, 7, 9);
	matr.AddEdge(2, 9, 6);
	matr.AddEdge(3, 0, 5);
	matr.AddEdge(3, 10, 7);
	matr.AddEdge(3, 11, 24);
	matr.AddEdge(4, 13, 9);
	matr.AddEdge(5, 6, 9);
	matr.AddEdge(5, 7, 6);
	matr.AddEdge(5, 13, 5);
	matr.AddEdge(7, 8, 7);
	matr.AddEdge(7, 9, 24);
	matr.AddEdge(10, 9, 9);
	matr.AddEdge(10, 11, 9);
	matr.AddEdge(12, 0, 9);
	matr.AddEdge(12, 3, 9);
	matr.AddEdge(13, 12, 9);
	matr.DisplayGraph();
	matr.BDF(0);
	getchar();

	



	//std::cout << queue.GetFront().vertex_id_;
	//std::cout << queue.GetFront().vertex_id_;

	//std::cout << queue.GetSize();

	getchar();
    return 0;

}

