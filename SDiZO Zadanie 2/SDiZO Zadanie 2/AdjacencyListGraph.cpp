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
	{
		ver.vertex_id_ = v1;
		adj_tab_[v2].PushBack(ver);
	}
		
}

void sdz::AdjacencyListGraph::DisplayGraph()
{
	for (uint it = 0; it < vertices_; it++)
	{
		std::cout << "Connections for vertex " << it << std::endl;
		DisplayConnections(it);
	}
}

void sdz::AdjacencyListGraph::BDF(Vertex s)
{
	//List of visited vertices
	bool *visited = new bool[vertices_];

	//Mark all vertices as not visited
	for (uint i = 0; i < vertices_; i++)
		visited[i] = false;

	dts::Queue<Vertex> queue;
	visited[s.vertex_id_] = true;
	queue.PushBack(s);

	while (queue.GetSize()!=0)
	{
		//Deque a vertex from queue and print it
		s = queue.GetFront();
		std::cout << s.vertex_id_ << " ";
		queue.PopFront();
		//Get all adjacent vertices of the dequeed vertex s
		//If a adjacent has not been visited, then mark it visited and enque it
		for (auto it = adj_tab_[s.vertex_id_].begin(); it != adj_tab_[s.vertex_id_].end(); it++)
		{
			if (!visited[it->vertex_id_])
			{
				visited[it->vertex_id_] = true;
				queue.PushBack(*it);
			}
		}
	}

	



}

Vertex sdz::AdjacencyListGraph::GetVertex(uint vertex_id)
{
	return Vertex();
	
}

void sdz::AdjacencyListGraph::DisplayConnections(uint v)
{
	for (auto it = adj_tab_[v].begin(); it != adj_tab_[v].end(); it++)
		std::cout<< it->vertex_id_ <<"-"<< it->edge_weight_<<" "; 
	std::cout << std::endl;
}
