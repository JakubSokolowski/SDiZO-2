
#include "stdafx.h"
#include <conio.h>
#include <cstdio>
#include <utility>
#include <ctime>
#include <cmath>
#include "IncidenceMatrixGraph.h"
#include "AdjacencyListGraph.h"
#include "Vertex.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "FibonacciHeap.h"
#include "Vector.h"
#include "PerformanceTests.h"
#include <iostream>
#include <iomanip>
using namespace SDZ;


typedef AdjacencyListGraph ALG;
typedef IncidenceMatrixGraph IMG;

void DisplayMenu()
{
	//Wybór Algorytmu A star, Primm z Kopcem Fibb, Ford - fulkerson
			//Wybór reprezentacji - Lista S¹siedztwa, Macierz Incydencji
				//Wczytaj z pliku
				//Wygeneruj
				//Wyswietl
	
	

	ALG l_graph = ALG();
	IMG m_graph = IMG();

	char algorithm_selection = 'a';
	do{
		std::cout << "---MENU---" << std::endl;
		std::cout << "1 - Prim MST with fibonacci heap (adjacency list only)" << std::endl;
		std::cout << "2 - A star shortest path search" << std::endl;
		std::cout << "3 - Ford-Fulkerson maximum flow" << std::endl;
		std::cout << "0 - end" << std::endl;
		std::cout << std::endl;

	
		algorithm_selection = _getche();
		switch (algorithm_selection)
		{
			//Primm MST
			case '1':
			{
				char option = 'a';				
				do {
					std::cout << std::endl;
					std::cout << "---Primm MST Fibonacci Heap---" << std::endl;
					std::cout << "1 - Generate random graph (adjacency list only)" << std::endl;
					std::cout << "2 - Display graph" << std::endl;
					std::cout << "3 - Display map" << std::endl;
					std::cout << "4 - Prim Minimum Spanning Tree" << std::endl;
					std::cout << "0 - End" << std::endl;

					option = _getche();
					std::cout << std::endl;

					switch (option)
					{
							//Graph Generation
						case '1':
						{
							uint vertices;
							double density;
							std::cout << "Number of vertices (unsigned integer) : ";
							std::cin >> vertices;
							std::cout << "Density (dobule 0.0 - 1.0): ";
							std::cin >> density;

							//Prim need undirected weighted graph
							l_graph.SetParameters(vertices, density, false, true);

						} break;

						//Graph Display
						case '2':
						{
							l_graph.DisplayInfo();
							l_graph.DisplayEdges();
						} break;

						//Map Display
						case '3':
						{
							l_graph.DisplayMapWithId();
						} break;

						//Primm Minimum Spanning tree
						case '4':
						{
							l_graph.FHPrimMST();
						} break;
					}
				} while (option != '0');

			}break;
			//A Star Search
			case '2':
			{
				char option = 'a';
				do {
					std::cout << std::endl;
					std::cout << "---A* shortest path search---" << std::endl;
					std::cout << "Choose the graph representation: " << std::endl;
					std::cout << "1 - Adjacency list " << std::endl;
					std::cout << "2 - Incidence matrix " << std::endl;
					std::cout << "0 - End" << std::endl;

					option = _getche();
					std::cout << std::endl;

					switch (option)
					{
						//Adjacency List Graph Generation for Ford-Fulkerson max flow
						case '1':
						{	
							char option = 'a';
							do {
								std::cout << std::endl;
								std::cout << "---A* shortest path search---" << std::endl;
								std::cout << "1 - Generate random graph for adjacency list" << std::endl;
								std::cout << "2 - Display graph" << std::endl;
								std::cout << "3 - Display map" << std::endl;
								std::cout << "4 - A star path search" << std::endl;
								std::cout << "0 - End" << std::endl;

								option = _getche();
								std::cout << std::endl;

								switch (option)
								{
									//Graph Generation
									case '1':
									{
										uint vertices;
										double density;
										std::cout << "Number of vertices (unsigned integer) : ";
										std::cin >> vertices;
										std::cout << "Density (dobule 0.0 - 1.0): ";
										std::cin >> density;

										//Prim need undirected weighted graph
										l_graph.SetParameters(vertices, density, true, true);

									} break;

									//Graph Display
									case '2':
									{
										l_graph.DisplayInfo();
										l_graph.DisplayEdges();
									} break;

									//Map Display
									case '3':
									{
										l_graph.DisplayInfo();
										l_graph.DisplayMapWithId();
									} break;

									//A star Search
									case '4':
									{
										uint start,destination;
										Heuristic heuristic;
										std::cout << "Enter the start vertex (unsigned int): ";
										std::cin >> start;
										std::cout << "Enter the destination vertex (unsigned int): ";
										std::cin >> destination;
										std::cout << "Enter the heuristic: " << std::endl;

										std::cout << "1 - Euclidean, 2 - Manhattan, 3 - None (Dijkstra)" << std::endl;
										uint choice = 3;
										std::cin >> choice;
										switch (choice)
										{
										case 1:
											heuristic = Heuristic::EUCLIDEAN; 
											break;
										case 2:
											heuristic = Heuristic::MANHATTAN;
											break;
										case 3: 
											heuristic = Heuristic::DIJKSTRA;
											break;
										default:
											heuristic = Heuristic::DIJKSTRA;
											break;
										}

										DTS::Vector<uint> path = l_graph.AStarPathSearch(start, destination, heuristic);
										uint distance = l_graph.AStarDistanceSearch(start, destination, heuristic);

										std::cout << "Shortest distance from " << start << " to " << destination << " is: " << distance << std::endl;
										std::cout << "Path : " << std::endl;

										for (auto it : path)
										{
											std::cout << it << " ";
										}
										
										std::cout<<std::endl;
										l_graph.DrawPath(path);

									} break;
								}
							} while (option != '0');

						} break;

						//Incidency Matrix Graph Generation
						case '2':
						{

							char option = 'a';
							do {
								std::cout << std::endl;							
								std::cout << "---A* shortest path search---" << std::endl;
								std::cout << "1 - Generate random graph for incidency matrix" << std::endl;
								std::cout << "2 - Display graph" << std::endl;
								std::cout << "3 - Display map" << std::endl;
								std::cout << "4 - A star path search" << std::endl;
								std::cout << "0 - End" << std::endl;

								option = _getche();
								std::cout << std::endl;

								switch (option)
								{
										//Graph Generation
									case '1':
									{
										uint vertices;
										double density;
										std::cout << "Number of vertices (unsigned integer) : ";
										std::cin >> vertices;
										std::cout << "Density (dobule 0.0 - 1.0): ";
										std::cin >> density;

										//Prim need undirected weighted graph
										m_graph.SetParameters(vertices, density, true, true);

									} break;

									//Graph Display
									case '2':
									{
										m_graph.DisplayInfo();
										m_graph.DisplayMatrix();
										m_graph.DisplayWeights();
									} break;

									//Map Display
									case '3':
									{
										m_graph.DisplayMapWithId();
									} break;

									//A star Search
									case '4':
									{
										uint start, destination;
										Heuristic heuristic;
										std::cout << "Enter the start vertex (unsigned int): ";
										std::cin >> start;
										std::cout << "Enter the destination vertex (unsigned int): ";
										std::cin >> destination;
										std::cout << "Enter the heuristic: " << std::endl;

										std::cout << "1 - Euclidean, 2 - Manhattan, 3 - None (Dijkstra)" << std::endl;
										uint choice = 3;
										std::cin >> choice;
										switch (choice)
										{
										case 1:
											heuristic = Heuristic::EUCLIDEAN;
											break;
										case 2:
											heuristic = Heuristic::MANHATTAN;
											break;
										case 3:
											heuristic = Heuristic::DIJKSTRA;
											break;
										default:
											heuristic = Heuristic::DIJKSTRA;
											break;
										}

										DTS::Vector<uint> path = m_graph.AStarPathSearch(start, destination, heuristic);
										uint distance = m_graph.AStarDistanceSearch(start, destination, heuristic);

										std::cout << "Shortest distance from " << start << " to " << destination << " is: " << distance << std::endl;
										std::cout << "Path : " << std::endl;

										for (auto it : path)
										{
											std::cout << it << " ";
										}

										std::cout << std::endl;
										m_graph.DrawPath(path);

									} break;
								}
							} while (option != '0');
						} break;

					}
				} while (option != '0');
			}
			//Ford-Fulkerson
			case '3':
			{
				char option = 'a';
				do {
					std::cout << std::endl;
					std::cout << "---Ford-Fulkerson Maxium Flow---" << std::endl;
					std::cout << "Choose the graph representation: " << std::endl;
					std::cout << "1 - Adjacency list " << std::endl;
					std::cout << "2 - Incidence matrix " << std::endl;
					std::cout << "0 - End" << std::endl;

					option = _getche();
					std::cout << std::endl;

					switch (option)
					{
						//Adjacency List Graph Generation Ford-Fulkerson maximum path flow
					case '1':
					{

						char option = 'a';
						do {
							std::cout << std::endl;
							std::cout << "---Ford-Fulkerson Maxium Flow---" << std::endl;
							std::cout << "1 - Generate random graph for adjacency list" << std::endl;
							std::cout << "2 - Display graph" << std::endl;
							std::cout << "3 - Display map" << std::endl;
							std::cout << "4 - For-Fulkerson max flow" << std::endl;
							std::cout << "0 - End" << std::endl;

							option = _getche();
							std::cout << std::endl;

							switch (option)
							{
								//Graph Generation
								case '1':
								{
									uint vertices;
									double density;
									std::cout << "Number of vertices (unsigned integer) : ";
									std::cin >> vertices;
									std::cout << "Density (dobule 0.0 - 1.0): ";
									std::cin >> density;

									//Prim need undirected weighted graph
									l_graph.SetParameters(vertices, density, true, true);

								} break;

								//Graph Display
								case '2':
								{
									l_graph.DisplayInfo();
									l_graph.DisplayEdges();
								} break;

								//Map Display
								case '3':
								{
									l_graph.DisplayInfo();
									l_graph.DisplayMapWithId();
								} break;

								//Ford-Fulkerson
								case '4':
								{
									uint source, sink;
									std::cout << "Enter the source vertex (unsigned int): ";
									std::cin >> source;
									std::cout << "Enter the sink vertex (unsigned int): ";
									std::cin >> sink;
				
									uint max_flow = l_graph.FordFulkerson(source, sink);

									std::cout << "Maximum flow from " << source << " to " << sink << " is: " << max_flow << std::endl;							

								} break;
							}
						} while (option != '0');

					} break;

					//Incidency Matrix Graph Generation
					case '2':
					{

						char option = 'a';
						do {
							std::cout << std::endl;
							std::cout << "---Ford-Fulkerson Max flow Flow---" << std::endl;
							std::cout << "1 - Generate random graph for incidency matrix" << std::endl;
							std::cout << "2 - Display graph" << std::endl;
							std::cout << "3 - Display map" << std::endl;
							std::cout << "4 - For-Fulkerson max flow" << std::endl;
							std::cout << "0 - End" << std::endl;

							option = _getche();
							std::cout << std::endl;

							switch (option)
							{
									//Graph Generation
								case '1':
								{
									uint vertices;
									double density;
									std::cout << "Number of vertices (unsigned integer) : ";
									std::cin >> vertices;
									std::cout << "Density (dobule 0.0 - 1.0): ";
									std::cin >> density;

									//Prim need undirected weighted graph
									m_graph.SetParameters(vertices, density, true, true);

								} break;

								//Graph Display
								case '2':
								{
									m_graph.DisplayInfo();
									m_graph.DisplayMatrix();
									m_graph.DisplayWeights();
								} break;

								//Map Display
								case '3':
								{
									m_graph.DisplayMapWithId();
								} break;

								//A star Search
								case '4':
								{
									uint source, sink;
									std::cout << "Enter the source vertex (unsigned int): ";
									std::cin >> source;
									std::cout << "Enter the sink vertex (unsigned int): ";
									std::cin >> sink;

									uint max_flow = m_graph.FordFulkerson(source, sink);

									std::cout << "Maximum flow from " << source << " to " << sink << " is: " << max_flow << std::endl;

								} break;
							}
						} while (option != '0');
					} break;

					}
				} while (option != '0');
			}

		}
	} while (algorithm_selection != '0');
}

void AdjacencyMatrixTest()
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

	std::cout << test_graph.IsConnected(1, 3) << std::endl;
	std::cout << test_graph.IsConnected(3, 1) << std::endl;
	std::cout << test_graph.IsConnected(5, 4) << std::endl;
	std::cout << test_graph.IsConnected(4, 5) << std::endl;

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
int main()
{
	//AdjacencyMatrixTest();
	//IncidenceMatrixTest();
	//GenerateTestSamples();
	DisplayMenu();

	/*StartCounter();
	Sleep(1000);
	std::cout<<GetCounter();
	*/
	uint source = 12;
	uint destination = 456;

	std::cout.precision(10);
	std::cout << "\nSTTAAAARRTTT\n";
	StartCounter();
	AdjacencyListGraph graph = AdjacencyListGraph(1000, 0.9, true, true, true);
	std::cout << std::fixed << "Normal Graph Generation for dense graph " << GetCounter() << std::endl;
	graph.DisplayInfo();

	StartCounter();
	AdjacencyListGraph graph2 = AdjacencyListGraph(5000, 0.9, true, true, false);
	std::cout << std::fixed << "Fast Graph Generation for dense graph " << GetCounter() << std::endl;
	graph.DisplayInfo();

	std::cout << "\nPrim Minimum Spanning Tree with binary heap based priority queue: \n";
	StartCounter();
	graph.PQPrimMST();
	std::cout << "Time: " << GetCounter();
	std::cout << "\nPrim Minimum Spanning Tree with fibonacci heap based priority queue: \n";
	StartCounter();
	graph.FHPrimMST();
	std::cout  <<  "Time: " << GetCounter();
	

	std::cout << "\nSkonczono pisac\n\n";

	getchar();
    return 0;
}