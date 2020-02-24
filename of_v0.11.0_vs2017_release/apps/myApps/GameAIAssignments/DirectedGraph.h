#pragma once
#include <vector>
#include "DirectedWeightedEdge.h"
class DirectedGraph
{

	public:

		DirectedGraph();
		~DirectedGraph();
		std::vector<DirectedWeightedEdge> GetOutgoingEdges(int i_nodeId);

	private:
		std::vector<std::vector<DirectedWeightedEdge>> m_directedGraph;
};

