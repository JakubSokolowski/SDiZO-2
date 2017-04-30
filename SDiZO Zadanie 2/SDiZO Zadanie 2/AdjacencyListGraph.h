#pragma once
#include "Vertex.h"
#include "List.h"

	
namespace sdz
{
	class AdjacencyListGraph
	{
	public:

		
		AdjacencyListGraph();
		AdjacencyListGraph(uint vertices, bool is_directed);
		~AdjacencyListGraph();

		void AddEdge(uint v1, uint id, uint weight);
		void DisplayGraph();
		void DisplayConnections(uint v);
	private:

		bool is_directed_;
		uint vertices_;
		dts::List<Vertex> *adj_tab_;

	};



}
