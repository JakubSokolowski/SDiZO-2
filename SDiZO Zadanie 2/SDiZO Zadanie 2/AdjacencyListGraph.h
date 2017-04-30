#pragma once
#include "Vertex.h"
#include "List.h"
#include "Queue.h"
#include <iostream>

	
namespace sdz
{
	class AdjacencyListGraph
	{
	public:

		
		AdjacencyListGraph();
		AdjacencyListGraph(uint vertices, bool is_directed);
		~AdjacencyListGraph();

		void AddEdge(uint source, uint destination, uint weight);
		void DisplayGraph();
		void BDF(Vertex start);
		Vertex GetVertex(uint vertex_id);
		
	private:

		void DisplayConnections(uint v);

		bool is_directed_;
		uint vertices_;
		dts::List<Vertex> *adj_tab_;

	};



}
