#pragma once
#include <iostream>


namespace sdz
{
	class AdjacencyMatrixGraph
	{
		typedef unsigned int uint;
	public:

		//Constructors & Destructors

		AdjacencyMatrixGraph();
		AdjacencyMatrixGraph(uint vertices_count);
		~AdjacencyMatrixGraph();

		//Edge Management

		void AddEdge(uint origin, uint destination);
		void AddEdge(uint origin, uint destination, uint weight);

		void Display();

	private:

		bool IsValidEdge(uint origin, uint destination);

		uint vertices_count_;
		uint **matrix_;
		bool *visited_;
		bool is_directed;

	};
}

