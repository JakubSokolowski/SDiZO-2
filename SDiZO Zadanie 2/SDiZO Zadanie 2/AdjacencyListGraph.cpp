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
	for (uint it = 0; it < vertices_; ++it)
	{
		adj_tab_[it].vertex_id_ = it;
	}	
	MarkAllNotVisited();
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

void SDZ::AdjacencyListGraph::BFT(uint node_id)
{
	//Create Queue for ids 
	DTS::Queue<uint> queue = DTS::Queue<uint>();
	//Mark all vertices not visited
	MarkAllNotVisited();
	//Current id 
	uint current = node_id;

	//Mark the current node as visited and enqueue it
	adj_tab_[current].visited_ = true;
	queue.PushBack(current);
	
	std::cout << "\nBreadth first traversal from node: " << current << std::endl;

	while (!queue.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		current = queue.GetFront();
		std::cout << current << " ";
		queue.PopFront();

		//Iterate through all the adacent vertices of the dequeed vertex
		for (auto it = adj_tab_[current].list_.begin(); it!= adj_tab_[current].list_.end() ; it++)
		{
			//If adjacent has not been visited
			if (!adj_tab_[it->destination_id].visited_)
			{
				//Mark it visited
					adj_tab_[it->destination_id].visited_ = true;
				//And enqueue it
				queue.PushBack(it->destination_id);			
			}
		}
	}
}

Vertex SDZ::AdjacencyListGraph::GetVertex(uint vertex_id)
{
	return Vertex();
	
}

void SDZ::AdjacencyListGraph::MarkAllVisited()
{
	for (uint it = 0; it < vertices_; it++)
		adj_tab_[it].visited_ = true;
}

void SDZ::AdjacencyListGraph::MarkAllNotVisited()
{
	for (uint it = 0; it < vertices_; it++)
		adj_tab_[it].visited_ = false;
}


