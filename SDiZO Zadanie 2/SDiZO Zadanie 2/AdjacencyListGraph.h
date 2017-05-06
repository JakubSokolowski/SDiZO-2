#pragma once
#include "Vertex.h"
#include "List.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include "FibonacciHeap.h"
#include "Vector.h"
#include <iostream>
#include <cmath>
#include <random>
#include <Windows.h>
#include <iomanip>
#include <unordered_map>
#include <io.h>
#include <fcntl.h>
#include <limits.h>

	
namespace SDZ
{
	enum Heuristic { EUCLIDEAN = 4, MANHATTAN = 1 };
	enum MapState{ FREE = 0, TAKEN = 1, PATH = 2, PATH_START =3, PATH_FINISH = 4};


	class AdjacencyListGraph
	{
	public:		

		// Constructors

		AdjacencyListGraph();
		AdjacencyListGraph(uint vertices, bool is_directed, bool is_euclidian);
		AdjacencyListGraph(uint vertives, double density, bool is_directed, bool is_euclidean);
		~AdjacencyListGraph();

		// Bulding graph

		void AddEdge(uint source, uint destination, uint weight);
		void SetMaxWeight(uint max_weight);

		// Display 

		void DisplayEdges();
		void DisplayEdgesWithWeights();
		void DisplayMap();
		void DisplayMapWithId();
		void DrawPath();
		void ClearMap();


		// Traversal & Search

		void BFT(uint start);
		DTS::List<uint> BFT(uint start,uint finish);
		DTS::List<uint> AStarSearch(uint source, uint destination, Heuristic h);

		// Minimum Spanning Trees

		void PrimMST();

		// Maximum Flow

		Vertex GetVertex(uint vertex_id);	

	private:

		//Graph structure & information

		uint vertices_;
		uint edges_;
		uint max_edges_;
		uint max_edge_weight_;
		Vertex *adj_tab_;	

		// Construcor flags

		bool is_directed_;
		bool is_euclidean_;		

		uint FindVertex(uint x, uint y);

		// Graph connection & Display

		int **map_;
		uint map_size_;

		uint CalculateMapSize();
		uint GetNumberOfDigits(unsigned n);

		void GenerateCoordinates();
		uint GetDistance(uint source, uint destination);
		void GenerateEdges(double density);
		void GenerateEdges(double density, uint max_weight);
		void MakeConnected();

		void MarkAllVisited();
		void MarkAllNotVisited();
		void MarkAsPathVertex(uint node_id);
		void MarkClosed(uint node_id);
		void MarkOpen(uint node_id);

		//Edmonds-karp n

		//Prim

		//A* 

		Heuristic heuristic_;
		void SetHeuristic(Heuristic h);
		
		uint GetManhattanHeuristic(uint source, uint destination);
		uint GetEuclideanHeuristic(uint source, uint destination);
		uint GetHeuristicValue(uint source, uint destination);	

	};
}
