// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IncidenceMatrix.h"
#include "AdjacencyList.h"
#include <vector>


int main()
{
	IncidenceMatrix matr = IncidenceMatrix(4, 5);
	matr.AddEdge(0, 3, 6);
	matr.AddEdge(1, 0, 5);
	matr.AddEdge(1, 3, 7);
	matr.AddEdge(1, 2, 24);
	matr.AddEdge(2, 0, 9);
	matr.DisplayMatrix();
	matr.DisplayWeights();


	getchar();
    return 0;
}

