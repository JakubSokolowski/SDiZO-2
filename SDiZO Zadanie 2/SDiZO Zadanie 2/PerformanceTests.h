#pragma once
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "AdjacencyListGraph.h"
#include "IncidenceMatrixGraph.h"
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