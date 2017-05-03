#include "stdafx.h"
#include "AdjacencyListGraph.h"


using namespace SDZ;

AdjacencyListGraph::AdjacencyListGraph()
{
	adj_tab_ = new Vertex[10];
}

SDZ::AdjacencyListGraph::AdjacencyListGraph(uint vertices,bool is_directed, bool is_euclidian)
{
	
	vertices_ = vertices;
	edges_ = 0;
	is_directed_ = is_directed;
	is_euclidian_ = is_euclidian;
	max_edges_ = vertices_ * (vertices_ - 1);
	adj_tab_ = new Vertex[vertices_];

	//Assign the ids 0 ... vertices-1
	for (uint it = 0; it < vertices_; ++it)
	{
		adj_tab_[it].vertex_id_ = it;
	}	
	if (is_euclidian_)
	{
		map_size_ = CalculateMapSize();
		GenerateCoordinates();
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
	++edges_;
}

void SDZ::AdjacencyListGraph::DisplayGraph()
{
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].DisplayList();
	}
}

void SDZ::AdjacencyListGraph::DisplayWeights()
{
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].DisplayListWithWeights();
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
	uint counter = 0;

	//Mark the current node as visited and enqueue it
	adj_tab_[current].visited_ = true;
	queue.PushBack(current);
	
	std::cout << "\nBreadth first traversal from node: " << current << std::endl;

	while (!queue.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		current = queue.GetFront();
		std::cout << current << " ";
		++counter;
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
	std::cout << " Traversed " << counter << " nodes. " << std::endl;
}

DTS::List<uint> SDZ::AdjacencyListGraph::BFT(uint start, uint finish)
{
	//Create Queue for ids 
	DTS::Queue<uint> queue = DTS::Queue<uint>();
	//Create list that holds traversed path
	DTS::List<uint> path = DTS::List<uint>();
	//Mark all vertices not visited
	MarkAllNotVisited();
	//Current id 
	uint current = start;
	uint counter = 0;

	//Mark the current node as visited and enqueue it
	adj_tab_[current].visited_ = true;
	queue.PushBack(current);

	std::cout << "\nBreadth first traversal from node: " << current << std::endl;

	while (!queue.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		current = queue.GetFront();
		path.PushBack(current);
		++counter;
		queue.PopFront();
		if (current == finish)
			break;

		//Iterate through all the adacent vertices of the dequeed vertex
		for (auto it = adj_tab_[current].list_.begin(); it != adj_tab_[current].list_.end(); it++)
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
	return path;
}

Vertex SDZ::AdjacencyListGraph::GetVertex(uint vertex_id)
{
	return adj_tab_[vertex_id];
	
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

void SDZ::AdjacencyListGraph::GenerateCoordinates()
{
	
	uint map_size_ = CalculateMapSize();

	//Create map 
	map_ = new int*[map_size_];
	for (uint i = 0; i < map_size_; i++)
	{
		//Mark all spaces in map as free
		map_[i] = new int[map_size_];
		for (uint j = 0; j < map_size_; j++)
			map_[i][j] = 0;
	}
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, map_size_-1);

	for (uint it = 0; it < vertices_; it++)
	{		
		bool avalible_space = false;

		while (!avalible_space)
		{
			uint x = uni(rng);
			uint y = uni(rng);
			if (map_[x][y] == 0)
			{
				adj_tab_[it].SetCoordinates(x, y);
				map_[x][y] = 1;
				avalible_space = true;
				if (it >= 1)
				{
					//Connect all the points with each other to make sure
					//that the graph is connected
					AddEdge(it - 1, it, GetDistance(it - 1, it));
				}
			}
		}		
	}	
}

void SDZ::AdjacencyListGraph::DisplayMap()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;
	

	int counter = 0;
	if (is_euclidian_)
	{
		for (uint x = 0; x < map_size_; x++)
		{
			for (uint y = 0; y < map_size_; y++)
			{
				if (map_[x][y]==1)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << std::setw(2) << (char)254u;
					counter++;
					SetConsoleTextAttribute(hConsole, 15);
				}	
				if (map_[x][y] == 0)
				{
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << std::setw(2) << (char)254u;					
				}
				else
				{
					
				}
					
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << counter << std::endl;
}

void SDZ::AdjacencyListGraph::DisplayMapWithId()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;

	uint print_width = GetNumberOfDigits(vertices_) + 1 ;

	int counter = 0;
	if (is_euclidian_)
	{
		for (uint x = 0; x < map_size_; x++)
		{
			for (uint y = 0; y < map_size_; y++)
			{
				if (map_[x][y] == 1)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << std::setw(print_width) << FindVertex(x,y);
					counter++;
					SetConsoleTextAttribute(hConsole, 15);
				}
				if (map_[x][y] == 0)
				{
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << std::setw(print_width) << (char)254u;
				}
				else
				{

				}

			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl << counter << std::endl;
}

void SDZ::AdjacencyListGraph::ConnectVertices(float density)
{
	
	//Calculate the number of edges needed for given density
	uint desired_edges = static_cast<uint>(density * max_edges_);
	//Calculte the number of missing edges, by substracting current number from desired
	if (edges_ >= desired_edges)
		return;
	uint missing_edges = desired_edges - edges_;

	
	std::random_device rd;
	std::mt19937 rng(rd());
	//Generate random integers to connect all id's
	std::uniform_int_distribution<uint> uni(0, vertices_-1);

	for (uint it = 0; it < missing_edges;)
	{
		uint source = uni(rng);
		uint destination = uni(rng);
		if (!adj_tab_[source].IsConnected(destination))
		{
			AddEdge(source, destination, GetDistance(source, destination));
			++it;
		}
	}
}

uint SDZ::AdjacencyListGraph::FindVertex(uint x, uint y)
{
	for (uint it = 0; it < vertices_; ++it)
	{
		if (adj_tab_[it].x_ == x && adj_tab_[it].y_ == y)
		{
			return adj_tab_[it].vertex_id_;
		}
	}		
	return NULL;
}

uint SDZ::AdjacencyListGraph::CalculateMapSize()
{
	return uint(ceil(sqrt(vertices_ * 4)));
}

uint SDZ::AdjacencyListGraph::GetDistance(uint source, uint destination)
{
	//Calculte the distance between 2 points and cast it on unsigned int
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(sqrt(pow(X, 2) + pow(Y, 2)));
}

uint SDZ::AdjacencyListGraph::GetManhattanHeuristic(uint source, uint destination)
{
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(MANHATTAN * (X + Y));
}

uint SDZ::AdjacencyListGraph::GetEuclideanHeuristic(uint source, uint destination)
{
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(EUCLIDEAN * sqrt(pow(X, 2) + pow(Y, 2)));
}

uint SDZ::AdjacencyListGraph::GetNumberOfDigits(unsigned n)
{
	return n > 0 ? (int)log10((double)n) + 1 : 1;
}


