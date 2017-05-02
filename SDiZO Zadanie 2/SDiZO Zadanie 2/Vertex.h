#pragma once
#include "List.h"
#include "Edge.h"
#include <iostream>

typedef unsigned int uint;


namespace SDZ
{
	class Vertex
	{
	public:

		uint vertex_id_;
		bool visited_;
		DTS::List<SDZ::Edge> list_;

		uint x_;
		uint y_;

		Vertex();
		Vertex(uint id);
		~Vertex();

		void AddEdge(uint destination, uint weight);
		void DisplayList();

		Vertex & operator = (const Vertex&);
	};


}