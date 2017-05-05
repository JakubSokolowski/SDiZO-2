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
		bool visited_, is_open_, is_closed_;
		DTS::List<SDZ::Edge> list_;

		uint x_;
		uint y_;

		Vertex();
		Vertex(uint id);
		~Vertex();

		void AddEdge(uint destination, uint weight);
		void DisplayListWithWeights();
		void DisplayList();

		bool IsConnected(uint destination);
		uint GetConnectionWeight(uint destination);
		void SetCoordinates(uint x, uint y);
		Vertex & operator = (const Vertex&);

		//A * related fields

		//total distance alredy travelled to reach this node
		uint G;
		uint H;
		uint level;
		//priority - edge weight + A* heuristic
		uint priority;

		void UpadatePriority();

	private:
		
		
	};
}