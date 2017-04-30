// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include <cstdio>
#include <utility>
#include <ctime>
#include "List.h"
#include "Vertex.h"



using namespace sdz;

int main()
{
	IncidenceMatrixGraph matr = IncidenceMatrixGraph(4, 5);
	matr.AddEdge(0, 3, 6);
	matr.AddEdge(1, 0, 5);
	matr.AddEdge(1, 3, 7);
	matr.AddEdge(1, 2, 24);
	matr.AddEdge(2, 0, 9);
	matr.DisplayMatrix();
	matr.DisplayWeights();

	
	

	AdjacencyListGraph graph = AdjacencyListGraph(4,true);
	graph.AddConnection(0, 3, 6);
	graph.AddConnection(1, 0, 5);
	graph.AddConnection(1, 3, 7);
	graph.AddConnection(1, 2, 24);
	graph.AddConnection(2, 0, 9);
	graph.DisplayGraph();

getchar();



	return 0;
}


