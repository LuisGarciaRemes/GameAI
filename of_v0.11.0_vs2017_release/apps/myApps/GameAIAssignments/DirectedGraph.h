#pragma once
#include <vector>
#include "DirectedWeightedEdge.h"
class DirectedGraph
{

	public:

		DirectedGraph(std::string i_filename);
		DirectedGraph();
		~DirectedGraph();
		std::vector<DirectedWeightedEdge> GetOutgoingEdges(int i_nodeId);
		int GetTotalNodes();

	private:
		std::vector<std::vector<DirectedWeightedEdge>> m_directedGraph;
		int m_size;
};

