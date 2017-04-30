#pragma once
#include <iostream>


namespace sdz
{
	class AdjacencyMatrixGraph
	{
	public:

		//Constructors & Destructors

		AdjacencyMatrixGraph();
		AdjacencyMatrixGraph(unsigned int vertices_count);
		~AdjacencyMatrixGraph();

		//Edge Management

		void AddEdge(unsigned int origin, unsigned int destination);
		void AddEdge(unsigned int origin, unsigned int destination, unsigned int weight);

		void Display();

	private:

		bool IsValidEdge(unsigned int origin, unsigned int destination);

		unsigned int vertices_count_;
		unsigned int **matrix_;
		bool *visited_;
		bool is_directed;

	};
}

