
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
					std::cout << "2 - Read From File" << std::endl;
					std::cout << "3 - Display graph" << std::endl;
					std::cout << "4 - Display map" << std::endl;
					std::cout << "5 - Prim Minimum Spanning Tree" << std::endl;
					std::cout << "T - Save to file" << std::endl;
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


							if (vertices < 0 || density < 0)
								break;

							//Prim need undirected weighted graph
							l_graph.SetParameters(vertices, density, false, true);

						} break;

						//Red from file
						case '2':
						{
							std::string filename;
							std::cout << "Enter the filename: ";
							std::cin >> filename;
							if (FileExits(filename))
							{
								l_graph.ReadFromFile(filename, UNDIRECTED, XY_COORDINATES);
							}
							
						} break;
						//Graph Display
						case '3':
						{
							l_graph.DisplayInfo();
							l_graph.DisplayEdges();

						}break;

						//Map Display
						case '4':
						{
							l_graph.DisplayMapWithId();
						} break;

						//Primm Minimum Spanning tree
						case '5':
						{
							l_graph.FHPrimMST();
						} break;
						
						//Save to file
						case 'T':
						{
							std::string filename;
							std::cout << "Enter the filename: ";
							std::cin >> filename;
							l_graph.WriteToFile(filename);

						}break;
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
						//Adjacency List Graph Generation for A*
						case '1':
						{	
							char option = 'a';
							do {
								std::cout << std::endl;
								std::cout << "---A* shortest path search---" << std::endl;
								std::cout << "1 - Generate random graph for adjacency list" << std::endl;
								std::cout << "2 - Read From File" << std::endl;
								std::cout << "3 - Display graph" << std::endl;
								std::cout << "4 - Display map" << std::endl;
								std::cout << "5 - A star path search" << std::endl;
								std::cout << "T - Save to file" << std::endl;
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


										if (vertices < 0 || density < 0)
											break;

										//Prim need undirected weighted graph
										l_graph.SetParameters(vertices, density, true, true);

									} break;

									//Read from file
									//Red from file
									case '2':
									{
										std::string filename;
										std::cout << "Enter the filename: ";
										std::cin >> filename;
										if (FileExits(filename))
										{
											l_graph.ReadFromFile(filename, DIRECTED, XY_COORDINATES);
										}

									} break;


									//Graph Display
									case '3':
									{
										l_graph.DisplayInfo();
										l_graph.DisplayEdges();
									} break;

									//Map Display
									case '4':
									{
										l_graph.DisplayInfo();
										l_graph.DisplayMapWithId();
									} break;

									//A star Search
									case '5':
									{
										uint start,destination;
										Heuristic heuristic;
										std::cout << "Enter the start vertex (unsigned int): ";
										std::cin >> start;
										std::cout << "Enter the destination vertex (unsigned int): ";
										std::cin >> destination;
										std::cout << "Enter the heuristic: " << std::endl;


										if (start < 0 || destination < 0)
											break;

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
									case 'T':
									{
										std::string filename;
										std::cout << "Enter the filename: ";
										std::cin >> filename;
										l_graph.WriteToFile(filename);

									}break;
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
								std::cout << "2 - Read From File" << std::endl;
								std::cout << "3 - Display graph" << std::endl;
								std::cout << "4 - Display map" << std::endl;
								std::cout << "5 - A star path search" << std::endl;
								std::cout << "T - Save to file" << std::endl;
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


										if (vertices < 0 || density < 0)
											break;

										//Prim need undirected weighted graph
										m_graph.SetParameters(vertices, density, true, true);

									} break;

									//Red from file
									case '2':
									{
										std::string filename;
										std::cout << "Enter the filename: ";
										std::cin >> filename;
										if (FileExits(filename))
										{
											m_graph.ReadFromFile(filename, DIRECTED, XY_COORDINATES);
										}

									} break;
									//Graph Display
									case '3':
									{
										m_graph.DisplayInfo();
										m_graph.DisplayMatrix();
										m_graph.DisplayWeights();
									} break;

									//Map Display
									case '4':
									{
										m_graph.DisplayMapWithId();
									} break;

									//A star Search
									case '5':
									{
										uint start, destination;
										Heuristic heuristic;
										std::cout << "Enter the start vertex (unsigned int): ";
										std::cin >> start;
										std::cout << "Enter the destination vertex (unsigned int): ";
										std::cin >> destination;
										std::cout << "Enter the heuristic: " << std::endl;


										if (start < 0 || destination < 0)
											break;

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
									case 'T':
									{
										std::string filename;
										std::cout << "Enter the filename: ";
										std::cin >> filename;
										m_graph.WriteToFile(filename);

									}break;
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
							std::cout << "2 - Read from file" << std::endl;
							std::cout << "3 - Display graph" << std::endl;
							std::cout << "4 - Display map" << std::endl;
							std::cout << "5 - For-Fulkerson max flow" << std::endl;
							std::cout << "T - Save to file" << std::endl;
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


									if (vertices < 0 || density < 0)
										break;

									//Prim need undirected weighted graph
									l_graph.SetParameters(vertices, density, true, true);

								} break;

								//Red from file
								case '2':
								{
									std::string filename;
									std::cout << "Enter the filename: ";
									std::cin >> filename;
									if (FileExits(filename))
									{
										l_graph.ReadFromFile(filename, DIRECTED, XY_COORDINATES);
									}

								} break;

								//Graph Display
								case '3':
								{
									l_graph.DisplayInfo();
									l_graph.DisplayEdgesWithWeights();
								} break;

								//Map Display
								case '4':
								{
									l_graph.DisplayMapWithId();
								} break;

								//Ford-Fulkerson
								case '5':
								{
									uint source, sink;
									std::cout << "Enter the source vertex (unsigned int): ";
									std::cin >> source;
									std::cout << "Enter the sink vertex (unsigned int): ";
									std::cin >> sink;


									if (source < 0 || sink < 0)
										break;
				
									uint max_flow = l_graph.FordFulkerson(source, sink);

									std::cout << "Maximum flow from " << source << " to " << sink << " is: " << max_flow << std::endl;							

								} break;
								case 'T':
								{
									std::string filename;
									std::cout << "Enter the filename: ";
									std::cin >> filename;
									l_graph.WriteToFile(filename);

								}break;
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
							std::cout << "2 - Read From File" << std::endl;
							std::cout << "3 - Display graph" << std::endl;
							std::cout << "4 - Display map" << std::endl;
							std::cout << "5 - For-Fulkerson max flow" << std::endl;
							std::cout << "T - Save to file" << std::endl;
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

									if (vertices < 0 || density < 0)
										break;

									//Prim need undirected weighted graph
									m_graph.SetParameters(vertices, density, true, true);

								} break;

								//Red from file
								case '2':
								{
									std::string filename;
									std::cout << "Enter the filename: ";
									std::cin >> filename;
									if (FileExits(filename))
									{
										m_graph.ReadFromFile(filename, DIRECTED, XY_COORDINATES);
									}

								} break;

								//Graph Display
								case '3':
								{
									m_graph.DisplayInfo();
									m_graph.DisplayMatrix();
									m_graph.DisplayWeights();
								} break;

								//Map Display
								case '4':
								{
									m_graph.DisplayInfo();
									m_graph.DisplayMapWithId();
								} break;

								//Ford Fulkerson
								case '5':
								{
									uint source, sink;
									std::cout << "Enter the source vertex (unsigned int): ";
									std::cin >> source;
									std::cout << "Enter the sink vertex (unsigned int): ";
									std::cin >> sink;


									if (source < 0 || sink < 0)
										break;

									uint max_flow = m_graph.FordFulkerson(source, sink);

									std::cout << "Maximum flow from " << source << " to " << sink << " is: " << max_flow << std::endl;

								} break;
								case 'T':
								{
									std::string filename;
									std::cout << "Enter the filename: ";
									std::cin >> filename;
									m_graph.WriteToFile(filename);

								}break;

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
	//GenerateTestSamples();
	//TimeAlgorithms();
	//AStarHeuristicComparision();
	DisplayMenu();
	getchar();
    return 0;
}