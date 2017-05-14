
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

int main()
{
	//AdjacencyListTest();
	//IncidenceMatrixTest();
	//GenerateTestSamples();
	DisplayMenu();
	getchar();
    return 0;
}