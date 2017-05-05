// main.cpp : Defines the entry point for the console application.
//

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
#include "Vector.h"


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

	AdjacencyListGraph matr = AdjacencyListGraph(14,true,false);
	matr.AddEdge(0, 8, 6);
	matr.AddEdge(0, 2, 5);
	matr.AddEdge(0, 1, 7);
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
	matr.AddEdge(8, 9, 24);
	matr.AddEdge(10, 9, 9);
	matr.AddEdge(10, 11, 9);
	matr.AddEdge(12, 0, 9);
	matr.AddEdge(12, 3, 9);
	matr.AddEdge(13, 12, 9);
	matr.DisplayEdges();
	matr.BFT(0);
	

	AdjacencyListGraph matr2 = AdjacencyListGraph(123,0.15, true, true);
	//matr2.DisplayMapWithId();
	//matr2.DisplayWeights();
	//std::cout << std::endl << (double)matr2.edges_ / matr2.max_edges_ << std::endl;
	DTS::List<uint> path = matr2.AStarSearch(0, 15,EUCLIDEAN);

	path.Display();
	matr2.DisplayMapWithId();
	matr2.DisplayMap();
	matr2.ClearMap();

	matr2.AddEdge(0, 15, 1);
	DTS::List<uint> path2 = matr2.AStarSearch(65, 98, EUCLIDEAN);
	path2.Display();	
	matr2.DisplayMapWithId();
	for (auto it = path2.begin(); it != path2.end(); it++)
	{
		matr2.GetVertex(*it).DisplayList();

	}
	
	


	DTS::Vector<int> vec = DTS::Vector<int>();
	vec.push_back(4);
	vec.push_back(5);
	std::cout << vec.at(1) << std::endl;

	DTS::PriorityQueue<int,int> lmao = DTS::PriorityQueue<int,int>();
	lmao.Insert(20,5000);
	lmao.Insert(30,1000);
	lmao.Insert(2002,56);
	std::cout << lmao.GetFirst() << " " << lmao.GetPriority(0) << std::endl;
	lmao.UpdatePriority(2, 1);
	std::cout << lmao.GetFirst() << " " << lmao.GetPriority(0);


	


	getchar();
    return 0;
}

