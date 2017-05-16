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

		// Graph Construction

		IncidenceMatrixGraph();
		IncidenceMatrixGraph(std::string filename, bool is_directed, bool is_euclidean);
		IncidenceMatrixGraph(uint vertices, double density,bool is_directed, bool is_euclidean);	
		IncidenceMatrixGraph(uint vertices_count, uint edges_count);

		void SetParameters(uint vertices, double density, bool is_directed, bool is_euclidean);

		void WriteToFile(std::string filename);
		void ReadFromFile(std::string filename, bool is_directed, bool is_euclidean);

		void AddEdge(uint origin, uint destination, uint weight);

		~IncidenceMatrixGraph();


		//A*
		uint AStarDistanceSearch(uint origin, uint destination, Heuristic h);
		DTS::Vector<uint> AStarPathSearch(uint origin, uint destination, Heuristic h);

		//Ford-Fulkerson
		uint FordFulkerson(uint source, uint sink);
	
		void DisplayMatrix();
		void DisplayWeights();	

		void DisplayMap();
		void DisplayMapWithId();
		void DrawPath(DTS::Vector<uint> &vec);
		void DisplayInfo();



	private:

		int **matrix_;
		bool is_directed_, is_euclidean_;
		uint vertices_;
		uint edges_;
		uint current_edges_;
		uint edges_max_num_;
		uint edge_max_weight_;
		int *weights;
		int *residual_weights;
		
		DTS::Vector<std::pair<uint, uint>> coordinates_;
	
		void ClearGraph();

		//Chosen heuristic function
		SDZ::Heuristic heuristic_;

		//Random Graph Generation

		void MakeConnected();
		void GenerateEdges(double density);
		void GenerateCoordinates();
		uint CalculateMapSize();

		

		//Map Generation & Display

		int **map_;
		uint map_size_;

		void SetCoordinates(uint vertex, uint X, uint Y);	
		void ClearMap();

		// Utility
		uint FindVertex(uint x, uint y);
		uint FindEdgeDestination(uint vertex, uint edge);
		uint GetNumberOfDigits(uint number);

		int GetEdgeWeight(uint source, uint destination);
		int GetResidualEdgeWeight(uint source, uint destination);
		int GetEdgeId(uint source, uint destination);

		bool IsConnected(uint source, uint destination);
		bool IsValidEdge(uint origin, uint destination);
		uint CalculateNumberOfEdges(uint vertices,double density);
	
		// A star

		void SetHeuristic(Heuristic h);
		uint GetDistance(uint source, uint destination);
		uint GetManhattanHeuristic(uint source, uint destination);
		uint GetEuclideanHeuristic(uint source, uint destination);
		uint GetHeuristicValue(uint source, uint destination);

		// Ford-Fulkerson
		bool FordFulkersonBFS(uint source, uint destination, int path[]);
	};

}
