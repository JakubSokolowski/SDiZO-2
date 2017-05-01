#include "stdafx.h"
#include "AdjacencyListGraph.h"

using namespace SDZ;

AdjacencyListGraph::AdjacencyListGraph()
{
	adj_tab_ = new Vertex[10];
}

SDZ::AdjacencyListGraph::AdjacencyListGraph(uint vertices,bool is_directed)
{
	
	vertices_ = vertices;
	is_directed_ = is_directed;
	adj_tab_ = new Vertex[vertices_];

	//Assign the ids 0 ... vertices-1
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].vertex_id_ = it;
		adj_tab_[it].visited_ = false;
	}		
}


AdjacencyListGraph::~AdjacencyListGraph()
{
}

void SDZ::AdjacencyListGraph::AddEdge(uint source, uint destination, uint weight)
{
	adj_tab_[source].AddEdge(destination, weight);
	if (!is_directed_)
		adj_tab_[destination].AddEdge(source, weight);
}

void SDZ::AdjacencyListGraph::DisplayGraph()
{
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].DisplayList();
	}
}

void SDZ::AdjacencyListGraph::BDF(uint s)
{
	DTS::Queue<uint> queue;
	uint current =s;

	//Mark the current node as visited and enqueue it
	adj_tab_[s].visited_ = true;
	queue.PushBack(current);
	

	while (queue.GetSize()!=0)
	{
		//Deque a vertex from queue and print it
		current = queue.GetFront();
		std::cout << current << " ";
		queue.PopFront();

		//Get all adjacent vertices of the dequeed vertex s
		//If a adjacent has not been visited, then mark it visited and enque it
		for (auto it = adj_tab_[current].list_.begin();it!= adj_tab_[current].list_.end();it++)
		{ 
			if (!adj_tab_[it->destination_id].visited_)
			{
				adj_tab_[it->destination_id].visited_ = true;
				queue.PushBack(it->destination_id);
			}
		}
	}
}

Vertex SDZ::AdjacencyListGraph::GetVertex(uint vertex_id)
{
	return Vertex();
	
}


