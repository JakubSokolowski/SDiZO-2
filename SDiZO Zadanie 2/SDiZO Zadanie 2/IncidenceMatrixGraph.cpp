#include "stdafx.h"
#include "IncidenceMatrixGraph.h"

using namespace SDZ;


//Base constructor, creates matrix with 10 vertices and 10 edges
IncidenceMatrixGraph::IncidenceMatrixGraph()
	: vertices_(10)
	, edges_(10)
	, current_edges_(0)
	, is_directed_(false)
	, is_euclidean_(false)
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
	
	coordinates_.assign(vertices_, std::pair<uint,uint>(0,0));
	GenerateCoordinates();
}

SDZ::IncidenceMatrixGraph::IncidenceMatrixGraph(std::string filepath, bool is_directed, bool is_euclidean)
{
	is_euclidean_ = is_euclidean;
	is_directed_ = is_directed;

	std::fstream file;
	file.open(filepath, std::ios_base::in);
	if (!file)
		throw std::runtime_error("Could not open the file");

	uint edges, source, destination, weight, x, y;

	file >> edges;
	file >> vertices_;

	edges_ = edges;

	if (is_directed)
		edges_max_num_ = vertices_ * (vertices_ - 1);
	else
		edges_max_num_ = vertices_ * (vertices_ - 1) / 2;

	//Create Matrix
	matrix_ = new int *[vertices_];
	//Create array to hold the weights of edges
	weights = new int[edges]();

	for (uint i = 0; i < vertices_; i++)
	{
		matrix_[i] = new int[edges_];
		//Mark all rows as NO_EDGE
		for (uint j = 0; j < edges_; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}

	//Read Coordinates from file
	if (is_euclidean)
	{
		for (uint it = 0; it < vertices_; it++)
		{
			if (file >> x >> y)
			{
				SetCoordinates(it, x, y);
			}
		}
	}

	//Read edges from file
	while (file >> source >> destination >> weight)
	{
		if (!IsConnected(source,destination))
			AddEdge(source, destination, weight);
	}
	is_directed_ = is_directed;
	file.close();
}

SDZ::IncidenceMatrixGraph::IncidenceMatrixGraph(uint vertices, double density, bool is_directed, bool is_euclidean)
	: vertices_(vertices)
	, current_edges_(0)
	, is_directed_(is_directed)
	, is_euclidean_(is_euclidean)
{
	//Create Matrix
	matrix_ = new int *[vertices_];

	if (is_directed)
		edges_max_num_ = vertices * (vertices - 1);
	else
		edges_max_num_ = vertices_ * (vertices_ - 1) / 2;

	edges_ = CalculateNumberOfEdges(edges_max_num_, density);
	//Create array to hold the weights of edges
	weights = new int[edges_]();

	for (uint i = 0; i < vertices_; i++)
	{
		matrix_[i] = new int[edges_];
		//Mark all rows as NO_EDGE
		for (uint j = 0; j < edges_; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
	if (is_euclidean)
	{
		map_size_ = CalculateMapSize();
		GenerateCoordinates();		
	}	
	GenerateEdges(density);
}

void SDZ::IncidenceMatrixGraph::SetParameters(uint vertices, double density, bool is_directed, bool is_euclidean)
{
	ClearGraph();

	vertices_ = vertices;
	is_directed_ = is_directed;
	//Create Matrix
	matrix_ = new int *[vertices_];

	if (is_directed)
		edges_max_num_ = vertices * (vertices - 1);
	else
		edges_max_num_ = vertices_ * (vertices_ - 1) / 2;

	edges_ = CalculateNumberOfEdges(edges_max_num_, density);
	//Create array to hold the weights of edges
	weights = new int[edges_]();

	for (uint i = 0; i < vertices_; i++)
	{
		matrix_[i] = new int[edges_];
		//Mark all rows as NO_EDGE
		for (uint j = 0; j < edges_; j++)
		{
			matrix_[i][j] = NO_EDGE;
		}
	}
	if (is_euclidean)
	{
		map_size_ = CalculateMapSize();
		GenerateCoordinates();
	}
	GenerateEdges(density);
	
}

//Creates incidence matrix with given number vertices and edges
IncidenceMatrixGraph::IncidenceMatrixGraph(uint number_of_vertices, uint number_of_edges)
	: vertices_(number_of_vertices)
	, edges_(number_of_edges)
	, current_edges_(0)
	, is_directed_(false)
	, is_euclidean_(false)
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
	coordinates_.assign(vertices_, std::pair<uint, uint>(0, 0));
	GenerateCoordinates();
}

//Free the memory
IncidenceMatrixGraph::~IncidenceMatrixGraph()
{
	for (uint i = 0; i < vertices_;i++)
	{
		delete[] matrix_[i];
	}
	delete[] weights;
}

//Connects origin and destination with edge of given weight

void IncidenceMatrixGraph::AddEdge(uint origin, uint destination, uint weight)
{
	if (IsValidEdge(origin, destination))
	{
		if (!IsConnected(origin, destination))
		{
			//Connect the origin and destination with edge of given weight
			if (is_directed_)
			{
				matrix_[origin][current_edges_] = START;
				matrix_[destination][current_edges_] = START;			
			}
			else
			{
				matrix_[origin][current_edges_] = START;
				matrix_[destination][current_edges_] = END;
			}
			weights[current_edges_] = weight;
			++current_edges_;
		}		
	}
}

uint SDZ::IncidenceMatrixGraph::AStarDistanceSearch(uint start_id, uint finish_id, Heuristic h)
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
		auto current = frontier.GetFront();
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
				//Find the destination of edge
				uint destination_id = FindEdgeDestination(current, it);
				//Find the total cost of edge
				uint new_cost = cost_so_far[current] + weights[it];
				//Find the destination of edge				
				if (!cost_so_far.count(destination_id) || new_cost < cost_so_far[destination_id]) {
					cost_so_far[destination_id] = new_cost;
					uint priority = new_cost + GetHeuristicValue(destination_id, finish_id);
					frontier.Insert(destination_id, priority);
					came_from[destination_id] = current;
				}
			}			
		}
	}
	return cost_so_far[finish_id];
}

DTS::Vector<uint> SDZ::IncidenceMatrixGraph::AStarPathSearch(uint start_id, uint finish_id, Heuristic h)
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
		auto current = frontier.GetFront();
		frontier.PopFront();

		//If the goal is reached, stop early
		if (current == finish_id)
			break;

		//Iterate through all the edges to find neighbour vertices
		for (auto it = 0; it<edges_; it++)
		{
			//If vertex is an edge source ( vertex has neighbour)
			if (matrix_[current][it] == 1)
			{
				//Find the destination of edge
				uint destination_id = FindEdgeDestination(current, it);
				//Find the total cost of edge
				uint new_cost = cost_so_far[current] + weights[it];
				//Find the destination of edge				
				if (!cost_so_far.count(destination_id) || new_cost < cost_so_far[destination_id]) {
					cost_so_far[destination_id] = new_cost;
					uint priority = new_cost + GetHeuristicValue(destination_id, finish_id);
					frontier.Insert(destination_id, priority);
					came_from[destination_id] = current;
				}
			}
		}
	}
	DTS::Vector<uint> rec_path;
	uint curr = finish_id;
	rec_path.push_back(curr);
	while (curr != start_id)
	{
		curr = came_from[curr];
		rec_path.push_back(curr);
	}
	std::reverse(rec_path.begin(), rec_path.end());

	return rec_path;	
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
	for (uint i = 0; i < current_edges_ ; i++)
		std::cout << std::setw(3) << i << " ";
	std::cout << std::setw(2) << std::endl << " ";
	for (uint i = 0; i < current_edges_ ; i++)
		std::cout << std::setw(3) << weights[i] << " ";
	std::cout << std::endl;
}



uint SDZ::IncidenceMatrixGraph::FindEdgeDestination(uint vertex, uint edge)
{
	if (matrix_[vertex][edge] == 1)
	{
		for (uint i = 0; i < vertices_; i++)
		{
			if (i == vertex)
				continue;
			if (matrix_[i][edge] != NO_EDGE)
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
			if(matrix_[destination][i] != NO_EDGE)
				return weights[i];
	}
	return NULL;
}

int SDZ::IncidenceMatrixGraph::GetEdgeId(uint source, uint destination)
{
	for (uint i = 0; i < edges_; i++)
	{
		if (matrix_[source][i] == START)
		{
			if (matrix_[destination][i] != NO_EDGE)
				return i;		
		}			
	}
	return -1;
}

bool IncidenceMatrixGraph::IsValidEdge(uint origin, uint destination)
{
	return (origin > vertices_ || destination > vertices_) ? false : true;
}

bool SDZ::IncidenceMatrixGraph::IsConnected(uint origin, uint destination)
{
	for (auto it = 0; it < edges_; it++)
	{
		if (matrix_[origin][it] == 1)
			if (matrix_[destination][it] != NO_EDGE)
				return true;
	}
	return false;
}

void SDZ::IncidenceMatrixGraph::MakeConnected()
{
	bool old = is_directed_;
	if (old)
		is_directed_ = false;

	DisplayInfo();

	DTS::Vector<bool> alredy_connected(vertices_, false);

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> weight(0, edge_max_weight_);
	std::uniform_int_distribution<int> rnd_ver(0, vertices_ - 1);

	uint source = rnd_ver(rng);
	alredy_connected[source] = true;
	for (uint it = 0; it < vertices_ - 1;)
	{
		uint destination = rnd_ver(rng);
		if (source == destination)
			continue;

		if (!IsConnected(source,destination) && !alredy_connected[destination])
		{
			if (is_euclidean_)
				AddEdge(source, destination, GetDistance(source, destination));
			else
				AddEdge(source, destination, weight(rng));

			alredy_connected[destination] = true;
			source = destination;
			++it;
		}
	}
	is_directed_ = old;
}

void SDZ::IncidenceMatrixGraph::GenerateEdges(double density)
{
	if (edge_max_weight_ <= 0)
		edge_max_weight_ = 10;

	MakeConnected();
	//Calculate the number of edges needed for given density
	
	//uint desired_edges = static_cast<uint>(floor(density * edges_max_num_) + 0.5);
	uint desired_edges = CalculateNumberOfEdges(edges_max_num_, density);
	//Calculte the number of missing edges, by substracting current number from desired
	if (current_edges_ >= desired_edges)
		return;

	uint threshold = static_cast<uint>(floor(density * 100 + 0.5));
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<uint> uni(0, 100);
	std::uniform_int_distribution<uint> weight(1, edge_max_weight_);

	while (current_edges_ != desired_edges)
	{
		for (uint i = 0; i < vertices_; i++)
		{
			for (uint j = 0; j < vertices_; j++)
			{
				if (i == j)
					continue;
				uint value = uni(rng);
				if (value < threshold)
				{
					if (!IsConnected(i, j))
					{
						if (is_euclidean_)
						{
							AddEdge(i, j, GetDistance(i, j));
						}
						else
						{
							AddEdge(i, j, weight(rng));
						}
					}					
				}
				if (current_edges_ == desired_edges)
					break;
			}
		}
	}
}

void SDZ::IncidenceMatrixGraph::GenerateCoordinates()
{
	coordinates_.assign(vertices_, std::pair<uint, uint>(0, 0));

	uint map_size_ = CalculateMapSize();

	//Create map 
	map_ = new int*[map_size_];
	for (uint i = 0; i < map_size_; i++)
	{
		//Mark all spaces in map as free
		map_[i] = new int[map_size_];
		for (uint j = 0; j < map_size_; j++)
			map_[i][j] = MapState::FREE;
	}

	//Uniform distribution random place generation
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, map_size_ - 1);

	for (uint it = 0; it < vertices_; it++)
	{
		bool avalible_space = false;

		while (!avalible_space)
		{
			uint x = uni(rng);
			uint y = uni(rng);
			if (map_[x][y] == 0)
			{
				SetCoordinates(it, x, y);
				map_[x][y] = MapState::TAKEN;
				avalible_space = true;
			}
		}
	}
}

uint SDZ::IncidenceMatrixGraph::CalculateMapSize()
{
	return uint(ceil(sqrt(vertices_ * 4)));
}

void SDZ::IncidenceMatrixGraph::ClearGraph()
{
	for (uint i = 0; i < vertices_; i++)
	{
		delete[] matrix_[i];
	}
	delete[] weights;
	edges_ = 0;
	vertices_ = 0;
	edges_max_num_ = 0;
	current_edges_ = 0;
	edge_max_weight_ = 0;
	delete [] map_;
	map_size_ = 0;
}

void SDZ::IncidenceMatrixGraph::SetCoordinates(uint vertex, uint X, uint Y)
{
	coordinates_.at(vertex) = std::make_pair(X, Y);
}

void SDZ::IncidenceMatrixGraph::DisplayMap()
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
					SetConsoleTextAttribute(hConsole, 13);
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

void SDZ::IncidenceMatrixGraph::DisplayMapWithId()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::endl;

	uint print_width = GetNumberOfDigits(vertices_) + 1;

	int counter = 0;
	if (is_euclidean_)
	{
		for (uint x = 0; x < map_size_; x++)
		{
			for (uint y = 0; y < map_size_; y++)
			{
				if (map_[x][y] == TAKEN)
				{
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << std::setw(print_width) << FindVertex(x, y);
					counter++;
					SetConsoleTextAttribute(hConsole, 15);
				}
				if (map_[x][y] == FREE)
				{
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << std::setw(print_width) << (char)254u;
				}
				if (map_[x][y] == PATH)
				{
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << std::setw(print_width) << FindVertex(x, y);
					SetConsoleTextAttribute(hConsole, 15);
				}
				if (map_[x][y] == PATH_START)
				{
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << std::setw(print_width) << (char)254u;
				}
				if (map_[x][y] == PATH_FINISH)
				{
					SetConsoleTextAttribute(hConsole, 10);
					std::cout << std::setw(print_width) << FindVertex(x, y);
					SetConsoleTextAttribute(hConsole, 15);
				}
			}
			std::cout << std::endl;
		}
	}
}

void SDZ::IncidenceMatrixGraph::DrawPath(DTS::Vector<uint>& vec)
{
	ClearMap();
	for (auto it : vec)
	{
		map_[coordinates_.at(it).first][coordinates_.at(it).second] = PATH;
	}
	map_[coordinates_.at(0).first][coordinates_.at(0).second] = PATH_START;
	map_[coordinates_.at(vec.size()-1).first][coordinates_.at(vec.size()-1).second] = PATH_FINISH;
}


void SDZ::IncidenceMatrixGraph::ClearMap()
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

void SDZ::IncidenceMatrixGraph::DisplayInfo()
{
	std::cout << std::endl;
	if (is_directed_)
	{
		std::cout << "Graph is directed";
		if (is_euclidean_)
			std::cout << " and has X,Y coordinates on map" << std::endl;
		else
		{
			std::cout << " and does not have X,Y coordinates on map" << std::endl;
			std::cout << "Max edge weight: " << edge_max_weight_ << std::endl;
		}
	}
	else
	{
		std::cout << "Graph is undirected";
		if (is_euclidean_)
			std::cout << " and has X,Y coordinates on map" << std::endl;
		else
		{
			std::cout << " and does not have X,Y coordinates on map" << std::endl;
			std::cout << "Max edge weight: " << edge_max_weight_ << std::endl;
		}
	}
	std::cout << "Vertices : " << vertices_ << std::endl;
	std::cout << "Edges    : " << current_edges_ << "  " << "Max edges: " << edges_max_num_ << std::endl;
	std::cout << std::setprecision(2) << "Density  : " << double(edges_) / edges_max_num_ << "\n\n";
}

uint SDZ::IncidenceMatrixGraph::FindVertex(uint x, uint y)
{
	for (uint it = 0; it < vertices_; ++it)
	{
		if (coordinates_.at(it).first == x && coordinates_.at(it).second == y)
			return it;		
	}
}

uint SDZ::IncidenceMatrixGraph::GetNumberOfDigits(uint n)
{
	return n > 0 ? (int)log10((double)n) + 1 : 1;
}

uint SDZ::IncidenceMatrixGraph::CalculateNumberOfEdges(uint vertices,double density)
{
	return  static_cast<uint>(floor(density * edges_max_num_ + 0.5));
}

void SDZ::IncidenceMatrixGraph::SetHeuristic(Heuristic h)
{
	heuristic_ = h;
}

uint SDZ::IncidenceMatrixGraph::GetDistance(uint source, uint destination)
{
	uint X = abs((int)coordinates_.at(source).first - (int)coordinates_.at(destination).first);
	uint Y = abs((int)coordinates_.at(source).second - (int)coordinates_.at(destination).second);
	return static_cast<uint>(sqrt(pow(X, 2) + pow(Y, 2)));
}

uint SDZ::IncidenceMatrixGraph::GetManhattanHeuristic(uint source, uint destination)
{
	uint X = abs((int)coordinates_.at(source).first - (int)coordinates_.at(destination).first);
	uint Y = abs((int)coordinates_.at(source).second - (int)coordinates_.at(destination).second);
	return static_cast<uint>(MANHATTAN * (X + Y));
}

uint SDZ::IncidenceMatrixGraph::GetEuclideanHeuristic(uint source, uint destination)
{
	uint X = abs((int)coordinates_.at(source).first - (int)coordinates_.at(destination).first);
	uint Y = abs((int)coordinates_.at(source).second - (int)coordinates_.at(destination).second);
	return static_cast<uint>(EUCLIDEAN * sqrt(pow(X, 2) + pow(Y, 2)));
}

uint SDZ::IncidenceMatrixGraph::GetHeuristicValue(uint source, uint destination)
{
	// TODO change to switch
	if (heuristic_ == MANHATTAN)
	{
		return GetManhattanHeuristic(source, destination);
	}
	if (heuristic_ == EUCLIDEAN)
	{
		return GetEuclideanHeuristic(source, destination);
	}
	else
	{
		return 0;
	}
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
