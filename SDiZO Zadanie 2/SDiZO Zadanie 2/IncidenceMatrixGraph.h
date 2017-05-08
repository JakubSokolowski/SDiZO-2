#pragma once
#include "Vector.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include <limits.h>
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <cmath>
#include "AdjacencyListGraph.h"

#define INF UINT32_MAX

enum EdgeState { START = 1, END = -1, NO_EDGE = 0 };

typedef unsigned int uint;

namespace SDZ
{
	class IncidenceMatrixGraph
	{

	public:
		IncidenceMatrixGraph();
		IncidenceMatrixGraph(uint vertices_count, uint edges_count);
		~IncidenceMatrixGraph();

		void AddEdge(uint origin, uint destination, uint weight);
		uint AStarDistanceSearch(uint origin, uint destination, Heuristic h);
		uint FordFulkerson(uint source, uint sink);
		uint FindEdgeDestination(uint vertex, uint edge);
		int GetEdgeWeight(uint source, uint destination);
		int GetEdgeId(uint source, uint destination);
		void DisplayMatrix();
		void DisplayWeights();
		bool FordFulkersonBFS(uint source, uint destination, int path[]);

	private:

		int **matrix_;
		bool is_directed, is_euclidean;
		uint vertices_;
		uint edges_;
		uint number_of_edges_;
		int *weights;
		uint **map_;
		DTS::Vector<std::pair<uint, uint>> coordinates_;

		SDZ::Heuristic heuristic_;

		bool IsValidEdge(uint origin, uint destination);

		//A star
		void SetHeuristic(Heuristic h);
		//FordFulerson
		
	};

}
