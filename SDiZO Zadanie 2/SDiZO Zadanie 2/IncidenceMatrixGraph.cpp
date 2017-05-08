#include "stdafx.h"
#include "IncidenceMatrixGraph.h"

using namespace SDZ;

#define min(a,b) ((a) < (b) ? (a) : (b))

//Base constructor, creates matrix with 10 vertices and 10 edges
IncidenceMatrixGraph::IncidenceMatrixGraph()
	: vertices_(10)
	, edges_(10)
	, number_of_edges_(0)
{
	//Create Matrix
	matrix_ = new int *[10];

	//Create array to hold the weights of edges
	weights = new int[10]();

	for (int i = 0; i < 10; i++)
	{
		matrix_[i] = new int[10];
		//Mark all rows as NO_EDGE
		for (int j = 0; j < 10; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
}

//Creates incidence matrix with given number vertices and edges
IncidenceMatrixGraph::IncidenceMatrixGraph(uint number_of_vertices, uint number_of_edges)
	: vertices_(number_of_vertices)
	, edges_(number_of_edges)
	, number_of_edges_(0)
{
	//Create Matrix
	matrix_ = new int *[number_of_vertices];
	//Create array to hold the weights of edges
	weights = new int[number_of_edges]();

	for (uint i = 0; i < number_of_vertices; i++)
	{
		matrix_[i] = new int[number_of_edges];
		//Mark all rows as NO_EDGE
		for (uint j = 0; j < number_of_edges; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
}

//Free the memory
IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
	for (uint i = 0; i < vertices_;i++)
	{
		delete[] matrix_[i];
	}
}

//Connects origin and destination with edge of given weight
void IncidenceMatrixGraph::AddEdge(uint origin, uint destination, uint weight)
{
	if (IsValidEdge(origin, destination))
	{
		//Connect the origin and destination with edge of given weight
		matrix_[origin][number_of_edges_] = START;
		matrix_[destination][number_of_edges_] = END;
		weights[number_of_edges_] = weight;
		
		++number_of_edges_;
	}
}

uint SDZ::IncidenceMatrixGraph::AStarDistanceSearch(uint start_id, uint finish_id, Heur h)
{
	std::unordered_map<uint, uint> came_from, cost_so_far;
	SetHeuristic(h);

	//Create Queue for ids 
	DTS::PriorityQueue<uint, uint> frontier;
	//Create vector to store vertices, mark all as not visited
	//Current id 

	frontier.Insert(start_id, 0);
	came_from[start_id] = start_id;
	cost_so_far[start_id] = 0;

	while (!frontier.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		auto current = frontier.GetFirst();
		frontier.PopFront();

		//If the goal is reached, stop early
		if (current == finish_id)
			break;

		//Iterate through all the edges to find neighbour vertices
		for (auto it = 0; it<edges_;it++)
		{
			//If vertex is an edge source ( vertex has neighbour)
			if (matrix_[current][it] == 1)
			{
				//Find the cost of the edge
				uint destination_id = FindEdgeDestination(current, it);
				uint new_cost = cost_so_far[current] + weights[it];
				//Find the destination of edge				
				//If node is marked as closed, move over to the next one
				if (!cost_so_far.count(destination_id) || new_cost < cost_so_far[destination_id]) {
					cost_so_far[destination_id] = new_cost;
					uint priority = new_cost + 0;//GetHeuristicValue(it->destination_id, finish_id);
					frontier.Insert(destination_id, priority);
					came_from[destination_id] = current;
				}
			}			
		}
	}
	return cost_so_far[finish_id];
}

uint SDZ::IncidenceMatrixGraph::FordFulkerson(uint source, uint sink)
{
	uint curr_node, parent_node;
	uint max_flow = 0;
	//Filled by BFS
	int *path = new int [vertices_];	

	// Augument the flow while there is a path from source to sink

	while (FordFulkersonBFS(source, sink, path))
	{
		//Find the minimum residual capacity of the edges along the
		//path filled by BFS.
		uint path_flow = INF;

		for (curr_node = sink; curr_node != source; curr_node = path[curr_node])
		{
			parent_node = path[curr_node];
			path_flow = min(path_flow, GetEdgeWeight(parent_node,curr_node));
		}
		for (curr_node = sink; curr_node != source; curr_node = path[curr_node])
		{
			parent_node = path[curr_node];
			uint edge_id = GetEdgeId(parent_node, curr_node);
			if(edge_id!=-1)
				weights[edge_id] = weights[edge_id] + (path_flow * -1);
			edge_id = GetEdgeId(curr_node, parent_node);
			if (edge_id != -1)
				weights[edge_id] = weights[edge_id] + path_flow;
		}
		//Add to max_flow
		max_flow += path_flow;
	}
	return max_flow;
}


void IncidenceMatrixGraph::DisplayMatrix()
{
	std::cout << std::endl;
	std::cout << "  ";
	for (uint i = 0; i < edges_; i++)
		std::cout << std::setw(3) << i << " ";

	std::cout << std::endl;

	for (uint row = 0; row < vertices_; row++)
	{
		std::cout << row << " ";
		for (uint column = 0; column < edges_; column++)
			std::cout << std::setw(3) << matrix_[row][column] << " ";
		std::cout << std::endl;
	}
}

void IncidenceMatrixGraph::DisplayWeights()
{
	std::cout <<std::endl<< std::setw(2) << " ";
	for (uint i = 0; i < number_of_edges_ ; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::setw(2) << std::endl << " ";
	for (uint i = 0; i < number_of_edges_ ; i++)
		std::cout << std::setw(3) << weights[i] << " ";
	std::cout << std::endl;
}



uint SDZ::IncidenceMatrixGraph::FindEdgeDestination(uint vertex, uint edge)
{
	if (matrix_[vertex][edge] == 1)
	{
		for (uint i = 0; i < vertices_; i++)
		{
			if (matrix_[i][edge] == -1)
				return i;
		}
	}
	return NULL;
}

int SDZ::IncidenceMatrixGraph::GetEdgeWeight(uint source, uint destination)
{
	for(uint i = 0; i < edges_; i++)
	{
		if (matrix_[source][i] == 1)
			if (matrix_[destination][i] == -1)
				return weights[i];
	}
	return NULL;
}

int SDZ::IncidenceMatrixGraph::GetEdgeId(uint source, uint destination)
{
	for (uint i = 0; i < edges_; i++)
	{
		if (matrix_[source][i] == 1)
			if (matrix_[destination][i] == -1)
				return i;
	}
	return -1;
}

bool IncidenceMatrixGraph::IsValidEdge(uint origin, uint destination)
{
	return (origin > vertices_ || destination > vertices_) ? false : true;
}

void SDZ::IncidenceMatrixGraph::SetHeuristic(Heur h)
{
	heursitic_ = h;
}

bool SDZ::IncidenceMatrixGraph::FordFulkersonBFS(uint source, uint destination, int path[])
{

	//Create Queue for ids 
	DTS::Queue<uint> queue = DTS::Queue<uint>();
	bool *visited = new bool[vertices_];

	for (uint i = 0; i<vertices_; i++)
		visited[i] = false;

	visited[source] = true;
	path[source] = -1;
	queue.PushBack(source);

	while (!queue.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		uint curr_ver = queue.GetFront();
		queue.PopFront();

		//Iterate through all the edges  
		for (uint it = 0; it < edges_; it++)
		{
			//If vertex is an edge source
			if (matrix_[curr_ver][it] == 1)
			{
				//Find the destination of edge
				uint destination_id = FindEdgeDestination(curr_ver, it);
				//If the destination vertex of edge has not been visited 
				//And the current edge capacity > 0
				if (!visited[destination_id] && weights[it] > 0)
				{
					//Enqueue it
					queue.PushBack(destination_id);
					//Add to path
					path[destination_id] = curr_ver;
					//Mark as visited
					visited[destination_id] = true;
				}
			}
		}		
	}
	return (visited[destination] == true);
}
