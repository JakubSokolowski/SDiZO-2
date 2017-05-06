#include "stdafx.h"
#include "AdjacencyListGraph.h"

#define INF UINT32_MAX
using namespace SDZ;

//Base graph constructor. Creates not directed graph with 10 vertices without X,Y coordinates
AdjacencyListGraph::AdjacencyListGraph()
	: vertices_(10)
	, edges_(0)
	, is_directed_(false)
	, is_euclidean_(false)
	, max_edges_(10*9)
	, adj_tab_(new Vertex[10])
{}

//Creates graph with given amount of vertices. If is_euclidean flag is set, generate X,Y coordinates for vertices
SDZ::AdjacencyListGraph::AdjacencyListGraph(uint vertices, bool is_directed, bool is_euclidean)
{	
	vertices_ = vertices;
	edges_ = 0;
	is_directed_ = is_directed;
	is_euclidean_ = is_euclidean;
	max_edges_ = vertices_ * (vertices_ - 1);
	adj_tab_ = new Vertex[vertices_];

	//Assign the ids 0 ... vertices-1
	for (uint it = 0; it < vertices_; ++it)
	{
		adj_tab_[it].vertex_id_ = it;
	}	
	//If vertices need to have x,y coordinates
	if (is_euclidean_)
	{
		map_size_ = CalculateMapSize();
		GenerateCoordinates();
	}
	MarkAllNotVisited();
}

//Creates graph with given amount of vertices and density. If is_euclidean flag is set, generate X,Y coordinates for vertices
SDZ::AdjacencyListGraph::AdjacencyListGraph(uint vertices, double density, bool is_directed, bool is_euclidean)
{
	vertices_ = vertices;
	edges_ = 0;
	is_directed_ = is_directed;
	is_euclidean_ = is_euclidean;
	max_edges_ = vertices_ * (vertices_ - 1);
	adj_tab_ = new Vertex[vertices_];

	//Assign the ids 0 ... vertices-1
	for (uint it = 0; it < vertices_; ++it)
	{
		adj_tab_[it].vertex_id_ = it;
	}
	if (is_euclidean_)
	{
		map_size_ = CalculateMapSize();
		GenerateCoordinates();
		GenerateEdges(density);
	}
	MarkAllNotVisited();
}

//Destructor
AdjacencyListGraph::~AdjacencyListGraph()
{
	delete[] adj_tab_;
	delete[] map_;
}

//Connects source and destination vertex with edge of given weight;
void SDZ::AdjacencyListGraph::AddEdge(uint source, uint destination, uint weight)
{

	adj_tab_[source].AddEdge(destination, weight);
	if (!is_directed_)
		adj_tab_[destination].AddEdge(source, weight);
	++edges_;
}

//Sets the maximum weight of edge
void SDZ::AdjacencyListGraph::SetMaxWeight(uint max_weight)
{
	max_edge_weight_ = max_weight;
}

//Displays all the edges in graph
void SDZ::AdjacencyListGraph::DisplayEdges()
{
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].DisplayList();
		std::cout << std::endl;
	}
}

//Displays all the edges with weights in graph
void SDZ::AdjacencyListGraph::DisplayEdgesWithWeights()
{
	for (uint it = 0; it < vertices_; it++)
	{
		adj_tab_[it].DisplayListWithWeights();
		std::cout << std::endl;
	}
}

//Breadth first traversal of graph. Displays the traversed path
void SDZ::AdjacencyListGraph::BFT(uint start_id)
{
	//Create Queue for ids 
	DTS::Queue<uint> queue = DTS::Queue<uint>();
	//Mark all vertices not visited
	MarkAllNotVisited();
	//Current id 
	uint current = start_id;
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

//Breadth first traversal of graph from star vertex to end vertex. 
//Returns list of nodes traversed
DTS::List<uint> SDZ::AdjacencyListGraph::BFT(uint start_id, uint finish_id)
{
	
	//Create Queue for ids 
	DTS::Queue<uint> queue = DTS::Queue<uint>();
	//Create list that holds traversed path
	DTS::List<uint> came_from = DTS::List<uint>();
	//Mark all vertices not visited
	MarkAllNotVisited();
	//Current id 
	uint current = start_id;
	uint counter = 0;

	//Mark the current node as visited and enqueue it
	adj_tab_[current].visited_ = true;
	queue.PushBack(current);

	while (!queue.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		current = queue.GetFront();
		came_from.PushBack(current);
		++counter;
		queue.PopFront();

		//If the goal is reached, stop early
		if (current == finish_id)
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
	return came_from;
}

//Returns Vertex with given id
Vertex SDZ::AdjacencyListGraph::GetVertex(uint vertex_id)
{
	return adj_tab_[vertex_id];
	
}

//Marks all nodes as visited
void SDZ::AdjacencyListGraph::MarkAllVisited()
{
	for (uint it = 0; it < vertices_; it++)
		adj_tab_[it].visited_ = true;
}

//Marks all nodes as not visited
void SDZ::AdjacencyListGraph::MarkAllNotVisited()
{
	for (uint it = 0; it < vertices_; it++)
		adj_tab_[it].visited_ = false;
}

//Generates a map and randomly puts vertices on it. Coordinates XY are unique for every vertex
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
			map_[i][j] = FREE;
	}

	//Uniform distribution random place generation
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
				map_[x][y] = TAKEN;
				avalible_space = true;				
			}
		}		
	}	
}

//Displays map of vertices. 
void SDZ::AdjacencyListGraph::DisplayMap()
{
	//Needed to change color
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;	

	int counter = 0;
	if (is_euclidean_)
	{
		for (uint x = 0; x < map_size_; x++)
		{
			for (uint y = 0; y < map_size_; y++)
			{
				if (map_[x][y] == TAKEN)
				{

					// 12 - Red, 16 - Black, 15 - White, 13 - Green
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << std::setw(2) << (char)254u;
					counter++;
					SetConsoleTextAttribute(hConsole, 16);
				}	
				if (map_[x][y] == FREE)
				{
					SetConsoleTextAttribute(hConsole, 16);
					std::cout << std::setw(1) << (char)219u << (char)219u;
				}
				if (map_[x][y] == PATH)
				{
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << std::setw(2) << (char)254u;
					SetConsoleTextAttribute(hConsole, 16);
				}					
			}
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

//Displays map of vertices with ids
void SDZ::AdjacencyListGraph::DisplayMapWithId()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;

	uint print_width = GetNumberOfDigits(vertices_) + 1 ;

	int counter = 0;
	if (is_euclidean_)
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
				if(map_[x][y] == 2)
				{
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << std::setw(print_width) << FindVertex(x,y);
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
			std::cout << std::endl;
		}
	}
}

//Marks path vertices on a map
void SDZ::AdjacencyListGraph::DrawPath()
{
}

//Connects randomly vertices with edges, until the density is reached
void SDZ::AdjacencyListGraph::GenerateEdges(double density)
{
	if (max_edge_weight_ <= 0)
		max_edge_weight_ = 10;
	std::cout << max_edges_;
	MakeConnected();
	//Calculate the number of edges needed for given density
	uint desired_edges = static_cast<uint>(floor(density * max_edges_ + 0.5));
	//Calculte the number of missing edges, by substracting current number from desired
	if (edges_ >= desired_edges)
		return;
	uint missing_edges = desired_edges - edges_;

	
	std::random_device rd;
	std::mt19937 rng(rd());
	//Generate random integers to connect all id's
	std::uniform_int_distribution<uint> uni(0, vertices_-1);
	
	std::uniform_int_distribution<uint> rnd_weight(1, max_edge_weight_);

	for (uint it = 0; it < missing_edges;)
	{
		uint source = uni(rng);
		uint destination = uni(rng);
		if (!adj_tab_[source].IsConnected(destination))
		{
			if (is_euclidean_)
				AddEdge(source, destination, GetDistance(source, destination));
			else
				AddEdge(source, destination, rnd_weight(rng));
			source = destination;
			++it;
		}
	}
}

//Connects randomly graph with random weight edges, until the density is reached
void SDZ::AdjacencyListGraph::GenerateEdges(double density, uint max_weight)
{
	//Calculate the number of edges needed for given density
	uint desired_edges = static_cast<uint>(density * max_edges_);

	// If given density is smaller than the min density required for graph to be connected, return
	if (edges_ >= desired_edges)
		return;

	//Calculte the number of missing edges, by substracting current number from desired
	uint missing_edges = desired_edges - edges_;

	std::random_device rd;
	std::mt19937 rng(rd());
	//Generate random integers to connect all id's
	std::uniform_int_distribution<uint> rnd_vertex(0, vertices_ - 1);
	std::uniform_int_distribution<uint> rnd_weight(1, max_weight);

	for (uint it = 0; it < missing_edges;)
	{
		//Choose 2 random vertices

		uint source = rnd_vertex(rng);
		uint destination = rnd_vertex(rng);

		//Check if they are connected
		if (!adj_tab_[source].IsConnected(destination))
		{
			// Cannot connect vertex with itself - loops are not allowed
			if (source == destination)
				continue;
			// Connect the vertices with random weight
			AddEdge(source, destination, rnd_weight(rng));
			++it;
		}
	}
}

//Connects all the vertices with each other so the graph is fully connected
void SDZ::AdjacencyListGraph::MakeConnected()
{
	bool old = is_directed_;
	if (old)
		is_directed_ = false;

	DTS::Vector<bool> connected(vertices_, false);

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> weight(0, max_edge_weight_);
	std::uniform_int_distribution<int> rnd_ver(0, vertices_-1);
	
	uint source = rnd_ver(rng);
	for (uint it = 0; it < vertices_-1;)
	{				
		uint destination = rnd_ver(rng);
		if (source == destination)
			continue;

		if (!adj_tab_[source].IsConnected(destination) && !connected[destination])
		{
			if (is_euclidean_)
				AddEdge(source, destination, GetDistance(source, destination));
			else
				AddEdge(source, destination, weight(rng));
			connected[source] = true;
			source = destination;
			++it;
		}
	}	
	is_directed_ = old;
}

//Searches the shortest path from start to finish using A* algorithm. 
//Avalible heuristics - Manhattan Distance, Euclidean Distance
//Returns the list containing the shortest path
DTS::List<uint> SDZ::AdjacencyListGraph::AStarSearch(uint start_id, uint finish_id, Heuristic h)
{
	std::unordered_map<uint, uint> came_from, cost_so_far;
	SetHeuristic(h);
	
	//Create Queue for ids 
	DTS::PriorityQueue<uint, uint> frontier;
	//Create list that holds traversed path
	DTS::List<uint> path = DTS::List<uint>();

	//Mark all vertices not visited
	MarkAllNotVisited();
	//Current id 
	uint current = start_id;

	frontier.Insert(start_id, 0);
	came_from[start_id] = start_id;
	cost_so_far[start_id] = 0;

	std::cout << "\nA* search from node: " << current << " to node " << finish_id<< std::endl;

	while (!frontier.IsEmpty())
	{
		//Deque a vertex from queue and print it's id
		current = frontier.GetFirst();	
		
		//Add to closed set
		MarkClosed(current);
		//If the goal is reached, stop early
		if (current == finish_id)
		{
			path.PushBack(current);
			MarkAsPathVertex(current);
			break;
		}
		path.PushBack(current);
		MarkAsPathVertex(current);
		frontier.PopFront();
		//Iterate through all the neighbour nodes
		for (auto it = adj_tab_[current].list_.begin(); it != adj_tab_[current].list_.end(); it++)
		{
			uint new_cost = cost_so_far[current] + it->weight_;
			//If node is marked as closed, move over to the next one
			if (!cost_so_far.count(it->destination_id) || new_cost < cost_so_far[it->destination_id]) {
				cost_so_far[it->destination_id] = new_cost;
				uint priority = new_cost + GetHeuristicValue(it->destination_id, finish_id);
				frontier.Insert(it->destination_id, priority);
				came_from[it->destination_id] = current;
			}
		}
	}
	return path;
}

void SDZ::AdjacencyListGraph::PrimMST()
{
	//Create a heap to store vertices 
	DTS::FibonacciHeap<uint, uint> fib_heap;
	
	//Create Vector for keys, initializa all keys as infinite
	DTS::Vector<uint> keys(vertices_, INF);

	DTS::Vector<int> parent(vertices_, -1);
	DTS::Vector<int> weights(vertices_, 0);

	DTS::Vector<bool> inMST(vertices_, false);

	//Vertex 0 is source
	uint source = 0;
	fib_heap.Insert(source, 0);
	keys[source] = 0;

	while (!fib_heap.IsEmpty())
	{
		//The first vertex in pair is the minimum key vertex,
		//extract it from heap.
		uint u = fib_heap.GetMin();
		fib_heap.PopMin();
		inMST[u] = true;

		for (auto it = adj_tab_[u].list_.begin(); it != adj_tab_[u].list_.end(); it++)
		{
			//Get vertex label and weight of curren adjacent of u
			uint ver = (*it).destination_id;
			uint weight = (*it).weight_;

			if (inMST[ver])
				continue;
			//If v is not in mst and weight of (u,v) is smaller than current key of v
			if (keys[ver] > weight)
			{
				keys[ver] = weight;
				fib_heap.Insert(ver, weight);
				parent[ver] = u;
				weights[ver] = weight;
			}
		}
	}

	std::cout << "Minimum spanning tree : " << std::endl;
	for (uint i = 1; i < vertices_; ++i)
	{
		std::cout << parent[i] << " " << i << ":  " <<weights[i] << std::endl;
	}
	
}

//Returns the id of vertex at given coordinates
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

//Marks the vertex on map as path. Used in Display 
void SDZ::AdjacencyListGraph::MarkAsPathVertex(uint vertex_id)
{
	map_[adj_tab_[vertex_id].x_][adj_tab_[vertex_id].y_] = 2;
}

//Makrs all path vertices as normal vertices
void SDZ::AdjacencyListGraph::ClearMap()
{
	if (is_euclidean_)
	{
		for (uint x = 0; x < map_size_; x++)
		{
			for (uint y = 0; y < map_size_; y++)
			{
				if (map_[x][y] == PATH)
				{
					map_[x][y] = TAKEN;
				}
			}
		}
	}
}

//Returns size of map suitable for number of vertices in graph
uint SDZ::AdjacencyListGraph::CalculateMapSize()
{
	//Set map size so that only ~25% places are taken
	return uint(ceil(sqrt(vertices_ * 4)));
}

//Mark vertex as closed
void SDZ::AdjacencyListGraph::MarkClosed(uint node_id)
{
	adj_tab_[node_id].is_closed_ = true;
}

//Mark vertex as open
void SDZ::AdjacencyListGraph::MarkOpen(uint node_id)
{
	adj_tab_[node_id].is_open_ = true;
}

//Sets the heuristic used in A* search
void SDZ::AdjacencyListGraph::SetHeuristic(Heuristic h)
{
	heuristic_ = h;
}

//Returns straight line distance between 2 vertices , casted to unsigned int
uint SDZ::AdjacencyListGraph::GetDistance(uint source, uint destination)
{
	//Calculte the distance between 2 points and cast it on unsigned int
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(sqrt(pow(X, 2) + pow(Y, 2)));
}

//Returns value of Manhattan Heuristic 
uint SDZ::AdjacencyListGraph::GetManhattanHeuristic(uint source, uint destination)
{
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(MANHATTAN * (X + Y));
}

//Returns value of Euclidean Heuristic 
uint SDZ::AdjacencyListGraph::GetEuclideanHeuristic(uint source, uint destination)
{
	int X = abs((int)adj_tab_[source].x_ - (int)adj_tab_[destination].x_);
	int Y = abs((int)adj_tab_[source].y_ - (int)adj_tab_[destination].y_);
	return static_cast<uint>(EUCLIDEAN * sqrt(pow(X, 2) + pow(Y, 2)));
}

//Returns the value of current heuristic function
uint SDZ::AdjacencyListGraph::GetHeuristicValue(uint source, uint destination)
{
	// TODO change to switch
	if (heuristic_ == MANHATTAN)
	{
		return GetManhattanHeuristic(source, destination);
	}
	else
	{
		return GetEuclideanHeuristic(source, destination);
	}
}

//Returns number of digits in integer
uint SDZ::AdjacencyListGraph::GetNumberOfDigits(unsigned n)
{
	return n > 0 ? (int)log10((double)n) + 1 : 1;
}


