#include "stdafx.h"
#include "AdjacencyListGraph.h"

using namespace sdz;

AdjacencyListGraph::AdjacencyListGraph()
{
	adj_tab_ = new dts::List<Vertex>[10];
}

sdz::AdjacencyListGraph::AdjacencyListGraph(uint vertices,bool is_directed)
{
	
	vertices_ = vertices;
	is_directed_ = is_directed;
	adj_tab_ = new dts::List<Vertex>[vertices_];
}


AdjacencyListGraph::~AdjacencyListGraph()
{
}

void sdz::AdjacencyListGraph::AddEdge(uint v1, uint v2, uint weight)
{
	Vertex ver = Vertex(v2, weight);
	adj_tab_[v1].PushBack(ver);
	if (!is_directed_)
		adj_tab_[v2].PushBack(ver);
}

void sdz::AdjacencyListGraph::DisplayGraph()
{
	for (uint it = 0; it < vertices_; it++)
	{
		std::cout << "Connections for vertex " << it << std::endl;
		DisplayConnections(it);
	}
}

void sdz::AdjacencyListGraph::DisplayConnections(uint v)
{
	for (auto it = adj_tab_[v].begin(); it != adj_tab_[v].end(); it++)
		std::cout<< it->vertex_id_ <<"-"<< it->edge_weight_<<" "; 
	std::cout << std::endl;
}
