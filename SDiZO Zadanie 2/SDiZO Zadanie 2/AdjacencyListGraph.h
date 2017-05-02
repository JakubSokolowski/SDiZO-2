#pragma once
#include "Vertex.h"
#include "List.h"
#include "Queue.h"
#include <iostream>

	
namespace SDZ
{
	class AdjacencyListGraph
	{
	public:

		
		AdjacencyListGraph();
		AdjacencyListGraph(uint vertices, bool is_directed);
		~AdjacencyListGraph();

		void AddEdge(uint source, uint destination, uint weight);
		void DisplayGraph();
		void BDF(uint start);
		Vertex GetVertex(uint vertex_id);
		
	private:

		bool is_directed_;
		uint vertices_;
		Vertex *adj_tab_;

	};



}
