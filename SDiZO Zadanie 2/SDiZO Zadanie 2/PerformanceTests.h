#pragma once
#include <Windows.h>
#include <random>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "AdjacencyListGraph.h"
#include "IncidenceMatrixGraph.h"

using namespace SDZ;


bool FileExits(std::string &filename)
{

	struct stat buffer;
	return (stat(filename.c_str(), &buffer) == 0);
}
//Processor Frequency

double PCFreq = 0.0;
__int64 CounterStart = 0;

//ms - 1000.0
double time_unit = 1000.0;
void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / time_unit;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void RandomPath(uint &start, uint &finish, uint max_vertex)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, max_vertex - 1);
	bool not_the_same = false;
	while (!not_the_same)
	{
		start = uni(rng);
		finish = uni(rng);
		if (start != finish)
		{
			not_the_same = true;
		}
	}
}

void AdjacencyListTest()
{
	// Ford - fulkerson. For graph below Max flow should be 23

	AdjacencyListGraph test_graph = AdjacencyListGraph(6, DIRECTED, NO_COORDINATES);
	test_graph.AddEdge(0, 1, 16);
	test_graph.AddEdge(0, 2, 13);
	test_graph.AddEdge(1, 2, 10);
	test_graph.AddEdge(1, 3, 12);
	test_graph.AddEdge(2, 1, 4);
	test_graph.AddEdge(2, 4, 14);
	test_graph.AddEdge(3, 2, 9);
	test_graph.AddEdge(3, 5, 20);
	test_graph.AddEdge(4, 3, 7);
	test_graph.AddEdge(4, 5, 4);

	test_graph.DisplayInfo();
	test_graph.DisplayEdges();

	std::cout << "Maximum flow from vertex 0 to 5 : " << test_graph.FordFulkerson(0, 5) << std::endl;

	//Prim with Fibonacci heap. For graph below MST :
	//0-1 , 1-2 / 0-7 , 2-3, 3-4, 2-5, 5-6, 6-7, 2-8	

	test_graph.SetParameters(9, UNDIRECTED, NO_COORDINATES);

	test_graph.AddEdge(0, 1, 4);
	test_graph.AddEdge(0, 7, 8);
	test_graph.AddEdge(1, 2, 8);
	test_graph.AddEdge(1, 7, 11);
	test_graph.AddEdge(2, 3, 7);
	test_graph.AddEdge(2, 8, 2);
	test_graph.AddEdge(2, 5, 4);
	test_graph.AddEdge(3, 4, 9);
	test_graph.AddEdge(3, 5, 14);
	test_graph.AddEdge(4, 5, 10);
	test_graph.AddEdge(5, 6, 2);
	test_graph.AddEdge(6, 7, 1);
	test_graph.AddEdge(6, 8, 6);
	test_graph.AddEdge(7, 8, 7);

	test_graph.FHPrimMST();

	// A star search

	test_graph.SetParameters(9, DIRECTED, NO_COORDINATES);
	test_graph.AddEdge(0, 1, 4);
	test_graph.AddEdge(0, 7, 8);
	test_graph.AddEdge(1, 2, 8);
	test_graph.AddEdge(1, 7, 11);
	test_graph.AddEdge(2, 3, 7);
	test_graph.AddEdge(2, 8, 2);
	test_graph.AddEdge(2, 5, 4);
	test_graph.AddEdge(3, 4, 9);
	test_graph.AddEdge(3, 5, 14);
	test_graph.AddEdge(4, 5, 10);
	test_graph.AddEdge(5, 6, 2);
	test_graph.AddEdge(6, 7, 1);
	test_graph.AddEdge(6, 8, 6);
	test_graph.AddEdge(7, 8, 7);

	for (uint it = 1; it < 9; it++)
	{
		std::cout << "Shortest path from 0 to " << it << " is: " << test_graph.AStarDistanceSearch(0, it, SDZ::DIJKSTRA) << std::endl;
	}

	DTS::Vector<uint> list = test_graph.AStarPathSearch(0, 5, SDZ::DIJKSTRA);
	for (auto it : list)
	{
		std::cout << it << " ";
	}
	std::cout << "\n\nShortest path from 0 to 7: " << test_graph.AStarDistanceSearch(0, 5, SDZ::DIJKSTRA);

}

void IncidenceMatrixTest()
{
	// Ford - fulkerson. For graph below Max flow should be 23

	IncidenceMatrixGraph test_graph = IncidenceMatrixGraph(6, 10);
	test_graph.AddEdge(0, 1, 16);
	test_graph.AddEdge(0, 2, 13);
	test_graph.AddEdge(1, 2, 10);
	test_graph.AddEdge(1, 3, 12);
	test_graph.AddEdge(2, 1, 4);
	test_graph.AddEdge(2, 4, 14);
	test_graph.AddEdge(3, 2, 9);
	test_graph.AddEdge(3, 5, 20);
	test_graph.AddEdge(4, 3, 7);
	test_graph.AddEdge(4, 5, 4);


	test_graph.DisplayMatrix();
	test_graph.DisplayWeights();

	std::cout << "Maximum flow from vertex 0 to 5 : " << test_graph.FordFulkerson(0, 5) << std::endl;

	// A star search
	IncidenceMatrixGraph test_graph2 = IncidenceMatrixGraph(9, 14);
	test_graph2.AddEdge(0, 1, 4);
	test_graph2.AddEdge(0, 7, 8);
	test_graph2.AddEdge(1, 2, 8);
	test_graph2.AddEdge(1, 7, 11);
	test_graph2.AddEdge(2, 3, 7);
	test_graph2.AddEdge(2, 8, 2);
	test_graph2.AddEdge(2, 5, 4);
	test_graph2.AddEdge(3, 4, 9);
	test_graph2.AddEdge(3, 5, 14);
	test_graph2.AddEdge(4, 5, 10);
	test_graph2.AddEdge(5, 6, 2);
	test_graph2.AddEdge(6, 7, 1);
	test_graph2.AddEdge(6, 8, 6);
	test_graph2.AddEdge(7, 8, 7);

	std::cout << std::endl;
	for (uint it = 1; it < 9; it++)
	{
		std::cout
			<< "Shortest path from 0 to " << it << " is: " << test_graph2.AStarDistanceSearch(0, it, Heuristic::DIJKSTRA) << std::endl;
	}

	IncidenceMatrixGraph test_graph3 = IncidenceMatrixGraph(700, 1, true, true);
	test_graph3.DisplayInfo();
	for (int i = 1; i < 10; i++)
	{
		DTS::Vector<uint> vec = test_graph3.AStarPathSearch(0, i, Heuristic::DIJKSTRA);
		test_graph3.DrawPath(vec);
		std::cout << std::endl;
		for (auto it : vec)
			std::cout << it << " ";
		std::cout << std::endl;
		test_graph3.DisplayMapWithId();
	}
	getchar();
}

void AStarHeuristicComparision()
{
	uint source = 12;
	uint destination = 345;

	AdjacencyListGraph graph = AdjacencyListGraph(500, 0.3, true, true);

	StartCounter();
	std::cout << "\nShortest path from " << source << " to " << destination << " : "
		<< graph.AStarDistanceSearch(source, destination, Heuristic::DIJKSTRA) << std::endl;
	std::cout << "Djikstra heuristic time: " << GetCounter() << std::endl;

	StartCounter();
	std::cout << "\nShortest path from " << source << " to " << destination << " : "
		<< graph.AStarDistanceSearch(source, destination, Heuristic::EUCLIDEAN) << std::endl;
	std::cout << "Euclidean heuristic time: " << GetCounter() << std::endl;

	StartCounter();
	std::cout << "\nShortest path from " << source << " to " << destination << " : "
		<< graph.AStarDistanceSearch(source, destination, Heuristic::MANHATTAN) << std::endl;
	std::cout << "Manhattan heuristic time: " << GetCounter() << std::endl;
}

void HeapComparisionTest()
{

}

void GenerateTestSamples()
{
	//Size 25, 50, 100, 200, 400
	//Density 25,50,75,99
	std::string filepath = "C:\\Users\\Jakub\\Documents\\IV Semestr\\Struktury Danych i Z³o¿onoœc Obliczeniowa\\Projekt\\SDiZO Zadanie 2\\SDiZO Zadanie 2\\TestSamples\\25Density\\";
	std::string s = "V";
	std::string den = "D";
	std::string post = ".txt";


	double density = 0.25;

	for (int i = 50; i < 801; i *= 2)
	{
		for (int it = 0; it < 5; it++)
		{
			std::string filename = filepath + s + std::to_string(i) + den + std::to_string(int(density * 100)) + std::to_string(it) + post;
			AdjacencyListGraph graph = AdjacencyListGraph(i, density, true, true, true);
			graph.WriteToFile(filename);
			std::cout << "Finished writing: " + filename << std::endl;
		}

	}

	density = 0.50;
	filepath = "C:\\Users\\Jakub\\Documents\\IV Semestr\\Struktury Danych i Z³o¿onoœc Obliczeniowa\\Projekt\\SDiZO Zadanie 2\\SDiZO Zadanie 2\\TestSamples\\50Density\\";
	for (int i = 50; i < 801; i *= 2)
	{
		for (int it = 0; it < 5; it++)
		{
			std::string filename = filepath + s + std::to_string(i) + den + std::to_string(int(density * 100)) + std::to_string(it) + post;
			AdjacencyListGraph graph = AdjacencyListGraph(i, density, true, true, true);
			graph.WriteToFile(filename);
			std::cout << "Finished writing: " + filename << std::endl;
		}

	}
	density = 0.75;
	filepath = "C:\\Users\\Jakub\\Documents\\IV Semestr\\Struktury Danych i Z³o¿onoœc Obliczeniowa\\Projekt\\SDiZO Zadanie 2\\SDiZO Zadanie 2\\TestSamples\\75Density\\";
	for (int i = 50; i < 801; i *= 2)
	{
		for (int it = 0; it < 5; it++)
		{
			std::string filename = filepath + s + std::to_string(i) + den + std::to_string(int(density * 100)) + std::to_string(it) + post;
			AdjacencyListGraph graph = AdjacencyListGraph(i, density, true, true, true);
			graph.WriteToFile(filename);
			std::cout << "Finished writing: " + filename << std::endl;
		}

	}
	density = 0.99;
	filepath = "C:\\Users\\Jakub\\Documents\\IV Semestr\\Struktury Danych i Z³o¿onoœc Obliczeniowa\\Projekt\\SDiZO Zadanie 2\\SDiZO Zadanie 2\\TestSamples\\99Density\\";
	for (int i = 50; i < 801; i *= 2)
	{
		for (int it = 0; it < 5; it++)
		{
			std::string filename = filepath + s + std::to_string(i) + den + std::to_string(int(density * 100)) + std::to_string(it) + post;
			AdjacencyListGraph graph = AdjacencyListGraph(i, density, true, true, true);
			graph.WriteToFile(filename);
			std::cout << "Finished writing: " + filename << std::endl;
		}

	}
}

void PrimFibHeap()
{

}
void PrimBinHeap()
{

}

void PrimTest()
{
	const int graph_vertices[5] = { 25, 50, 100, 200, 400 };
	const double graph_density[4] = { 0.25, 0.50, 0.75, 0.99 };
	AdjacencyListGraph graph = AdjacencyListGraph();

	std::string filename = "PrimFibHeap.txt";
	std::string filename2 = "PrimBinHeap.txt";
	//Adj List Prim MST test
	std::ofstream file(filename);
	std::ofstream file2(filename2);

	double fib_time = 0.0;
	double bin_time = 0.0;

	file << "Prim fib test" << "\n";
	file2 << "Prim bin test" << "\n";

	std::cout << "Prim MST Start\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nStart for graph with density " << graph_density[i];
		for (int j = 0; j < 5; j++)
		{
			std::cout << "\n\tand vertices " << graph_vertices[j];
			for (int k = 0; k < 10; k++)
			{
				graph.SetParameters(graph_vertices[j], graph_density[i], false, true);
				StartCounter();
				graph.PQPrimMST();
				bin_time += GetCounter();
				StartCounter();
				graph.FHPrimMST();
				fib_time += GetCounter();
			}
			//file << time / 10 << " " << "V" << graph_vertices[i] << "D" << graph_density[j] << "\n";
			file << std::fixed << fib_time / 10 << "\n";
			file2 << std::fixed << bin_time / 10 << "\n";
			fib_time = 0.0;
			bin_time = 0.0;
		}
	}
	std::cout << "\nFinished Primm\n ";
	file.close();
	file2.close();
}
void AstarList()
{
	const uint graph_vertices[5] = { 25, 50, 100, 200, 400 };
	const double graph_density[4] = { 0.25, 0.50, 0.75, 0.99 };
	AdjacencyListGraph graph = AdjacencyListGraph();

	std::string filename = "ListDijkstra.txt";
	std::string filename2 = "ListAstar.txt";
	//Adj List Prim MST test
	std::ofstream file(filename);
	std::ofstream file2(filename2);

	double astar_time = 0.0;
	double dijkstra_time = 0.0;

	std::random_device rd;
	std::mt19937 rng(rd());

	uint start, finish, result;

	file << "Adjacency list Dijkstra test" << "\n";
	file2 << "Adjacency list Astar test" << "\n";

	std::cout << "Astar & Dijkstra Adjacency list Start\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nStart for graph with denisty " << graph_density[i];
		for (int j = 0; j <5; j++)
		{
			std::cout << "\n\tand vertices " << graph_vertices[j];
			graph.SetParameters(graph_vertices[j], graph_density[i], true, true);
			for (int k = 0; k < 10; k++)
			{
				RandomPath(start, finish, graph_vertices[j]);
				StartCounter();
				result = graph.AStarDistanceSearch(start, finish, Heuristic::EUCLIDEAN);
				astar_time += GetCounter();
				StartCounter();
				result = graph.AStarDistanceSearch(start, finish, Heuristic::DIJKSTRA);
				dijkstra_time += GetCounter();
			}
			//file << time / 10 << " " << "V" << graph_vertices[i] << "D" << graph_density[j] << "\n";
			std::cout <<" "<< astar_time << " " << dijkstra_time << std::endl;
			file << std::fixed << dijkstra_time / 10 << "\n";
			file2 << std::fixed << astar_time / 10 << "\n";
			astar_time = 0.0;
			dijkstra_time = 0.0;
		}
	}
	std::cout << "\n A* Adjacency List Finish\n";
	file.close();
	file2.close();

}
void AstarMatrix()
{
	const uint graph_vertices[5] = { 25, 50, 100, 200, 400 };
	const double graph_density[4] = { 0.25, 0.50, 0.75, 0.99 };
	IncidenceMatrixGraph graph = IncidenceMatrixGraph();

	std::string filename = "MatrixDijkstra.txt";
	std::string filename2 = "MatrixAstar.txt";
	//Adj List Prim MST test
	std::ofstream file(filename);
	std::ofstream file2(filename2);

	double astar_time = 0.0;
	double dijkstra_time = 0.0;

	std::random_device rd;
	std::mt19937 rng(rd());

	uint start, finish, result;

	file << "Incidence matrix Dijkstra test" << "\n";
	file2 << "Incidence matrix  A* test" << "\n";

	std::cout << "Astar & Dijkstra Incidence matrix list Start\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nStart for graph with denisty " << graph_density[i];
		for (int j = 0; j <5; j++)
		{
			std::cout << "\n\tand vertices " << graph_vertices[j];
			graph.SetParameters(graph_vertices[j], graph_density[i], true, true);
			for (int k = 0; k < 10; k++)
			{
				RandomPath(start, finish, graph_vertices[j]);
				StartCounter();
				result = graph.AStarDistanceSearch(start, finish, Heuristic::EUCLIDEAN);
				astar_time += GetCounter();
				StartCounter();
				result = graph.AStarDistanceSearch(start, finish, Heuristic::DIJKSTRA);
				dijkstra_time += GetCounter();
			}
			//file << time / 10 << " " << "V" << graph_vertices[i] << "D" << graph_density[j] << "\n";
			std::cout << " " << astar_time/10 << " " << dijkstra_time/10 << std::endl;
			file << std::fixed << dijkstra_time / 10 << "\n";
			file2 << std::fixed << astar_time / 10 << "\n";
			astar_time = 0.0;
			dijkstra_time = 0.0;
		}
	}
	std::cout << "\n A* Adjacency List Finish\n";
	file.close();
	file2.close();

}
void AStarTest()
{
	AstarList();
	AstarMatrix();
}

void FordFulkersonList()
{
	const uint graph_vertices[5] = { 25, 50, 100, 200, 400 };
	const double graph_density[4] = { 0.25, 0.50, 0.75, 0.99 };
	AdjacencyListGraph graph = AdjacencyListGraph();

	std::string filename = "ListFordFulkerson.txt";
	//Adj List Prim MST test
	std::ofstream file(filename);
	double time = 0.0;



	std::random_device rd;
	std::mt19937 rng(rd());

	uint start, finish, result;

	//file << "Adjacency list Ford Fulkerson test" << "\n";

	std::cout << "\nFord Fulkerson Adjacency List Start\n";

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nStart for graph with denisty " << graph_density[i];
		for (int j = 0; j < 5; j++)
		{
			std::cout << "\n\tand vertices " << graph_vertices[j] << " ";
			graph.SetParameters(graph_vertices[j], graph_density[i], true, true);
			for (int k = 0; k < 5; k++)
			{
				RandomPath(start, finish, graph_vertices[j]);

				StartCounter();
				result = graph.FordFulkerson(start, finish);			
				time += GetCounter();
				std::cout << result << " ";
			}
			file << std::fixed << time / 5 << "\n";
			time = 0.0;
		}
	}
	std::cout << "\n Ford Fulkerson Adjacency List Finish\n";
	file.close();

}
void FordFulkersonMatrix()
{
	const uint graph_vertices[5] = { 25, 50, 100, 200, 400 };
	const double graph_density[4] = { 0.25, 0.50, 0.75, 0.99 };
	IncidenceMatrixGraph graph = IncidenceMatrixGraph();

	std::string filename = "MatrixFordFulkerson.txt";
	//Adj List Prim MST test
	std::ofstream file(filename);
	double time = 0.0;



	std::random_device rd;
	std::mt19937 rng(rd());

	uint start, finish, result;

	//file << "Adjacency list Ford Fulkerson test" << "\n";

	std::cout << "\nFord Fulkerson Incidence Matrix Start\n";

	for (int i = 0; i < 4; i++)
	{
		std::cout << "\nStart for graph with denisty " << graph_density[i] ;
		for (int j = 0; j < 5; j++)
		{
			std::cout << "\n\tand vertices " << graph_vertices[j] << " ";
			graph.SetParameters(graph_vertices[j], graph_density[i], true, true);
			for (int k = 0; k < 5; k++)
			{
				RandomPath(start, finish, graph_vertices[j]);

				StartCounter();
				result = graph.FordFulkerson(start, finish);
				time += GetCounter();
				std::cout << result << " ";

			}
			file << std::fixed << time / 5 << "\n";
			time = 0.0;
		}
	}
	std::cout << "\n Ford Fulkerson Adjacency List Finish\n";
	file.close();

}
void FordFulkersonTest()
{
	//FordFulkersonList();
	FordFulkersonMatrix();
}


void TimeAlgorithms()
{
	//PrimTest();
	//AStarTest();
	FordFulkersonTest();
}


