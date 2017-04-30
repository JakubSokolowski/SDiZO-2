// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"
#include <cstdio>
#include <utility>
#include <ctime>
#include "IncidenceMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "Vertex.h"



using namespace sdz;

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

	AdjacencyListGraph matr = AdjacencyListGraph(4,true);
	matr.AddEdge(0, 3, 6);
	matr.AddEdge(1, 0, 5);
	matr.AddEdge(1, 3, 7);
	matr.AddEdge(1, 2, 24);
	matr.AddEdge(2, 0, 9);
	matr.DisplayGraph();

	getchar();

    return 0;

}

