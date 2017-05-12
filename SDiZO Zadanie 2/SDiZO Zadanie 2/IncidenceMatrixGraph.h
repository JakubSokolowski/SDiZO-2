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

		//Array that holds graph representation [vertices_][edges_]
		int **matrix_;
		//Constructor flags
		bool is_directed, is_euclidean;
		//Number of vertices
		uint vertices_;
		//Number of edges
		uint edges_;
		//Current number of edges
		uint current_edges_;
		//Array that holds the weights of edges
		int *weights;

		//X Y map with randomly placed vertices
		int **map_;
		//X Y coordinates of vertices
		DTS::Vector<std::pair<uint, uint>> coordinates_;

		//Chosen heuristic function
		SDZ::Heuristic heuristic_;

		bool IsValidEdge(uint origin, uint destination);

		bool IsConnected(uint origin, uint destination);
		void MakeConnected();
		void GenerateEdges(double density);
		void GenerateCoordinates();
		uint CalculateMapSize();
		void SetCoordinates(uint vertex, uint X, uint Y);
		//A star
		void SetHeuristic(Heuristic h);
		uint GetDistance(uint source, uint destination);
		uint GetManhattanHeuristic(uint source, uint destination);
		uint GetEuclideanHeuristic(uint source, uint destination);
		uint GetHeuristicValue(uint source, uint destination);
		//FordFulerson
		
	};

}
