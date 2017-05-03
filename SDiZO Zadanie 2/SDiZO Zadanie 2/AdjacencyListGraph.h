#pragma once
#include "Vertex.h"
#include "List.h"
#include "Queue.h"
#include <iostream>
#include <cmath>
#include <random>
#include <Windows.h>
#include <iomanip>
#include <io.h>
#include <fcntl.h>

	
namespace SDZ
{
	class AdjacencyListGraph
	{
	public:

		
		AdjacencyListGraph();
		AdjacencyListGraph(uint vertices, bool is_directed, bool is_euclidian);
		~AdjacencyListGraph();

		void AddEdge(uint source, uint destination, uint weight);
		void DisplayGraph();
		void DisplayWeights();
		void BFT(uint start);
		DTS::List<uint> BFT(uint start,uint finish);
		Vertex GetVertex(uint vertex_id);

		void MarkAllVisited();
		void MarkAllNotVisited();
		
		void GenerateCoordinates();
		void DisplayMap();
		void DisplayMapWithId();
		void ConnectVertices(float density);

		uint edges_;
		uint max_edges_;
	private:

		uint FindVertex(uint x, uint y);
		bool is_directed_;
		bool is_euclidian_;

		uint vertices_;
		
		Vertex *adj_tab_;
		int **map_;
		//Map related A* fields
		uint CalculateMapSize();
		uint map_size_;
		//A* heurystic

		enum Heuristic{ EUCLIDEAN = 4, MANHATTAN = 1};

		uint GetDistance(uint source, uint destination);
		uint GetManhattanHeuristic(uint source, uint destination);
		uint GetEuclideanHeuristic(uint source, uint destination);

		//Utility
		uint GetNumberOfDigits(unsigned n);


		

	};



}
