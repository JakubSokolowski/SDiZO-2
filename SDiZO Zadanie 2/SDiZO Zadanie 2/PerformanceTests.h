#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include "AdjacencyListGraph.h"

using namespace SDZ;
//Processor Frequency

double PCFreq = 0.0;
__int64 CounterStart = 0;

//ms - 1000.0
double time_unit = 1.0;
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

void AStarHeuristicComparision()
{
	uint source = 12;
	uint destination = 456;

	AdjacencyListGraph graph = AdjacencyListGraph(1000, 0.3, true, true);

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
	std::cout << "Euclidean heuristic time: " << GetCounter() << std::endl;
}

void HeapComparisionTest()
{

}