#pragma once

typedef unsigned int uint;
namespace sdz
{
	class Vertex
	{
	public:

		uint vertex_id_;
		uint edge_weight_;
		Vertex();
		Vertex(uint id, uint weight);
		~Vertex();
	};


}