#include "SearchAlgorithms.h"

std::vector<DirectedWeightedEdge> SearchAlgorithms::Dijkstra(DirectedGraph i_graph, int i_start, int i_goal)
{
	//Initialize the record for the start node.
	NodeRecord currRecord;
	std::vector<DirectedWeightedEdge> currEdges;

	NodeRecord startRecord;
	startRecord.m_node = i_start;
	startRecord.m_costSoFar = 0;

	//Initialize the open and closed lists;
	PriorityQueue openList;
	PriorityQueue closedList;
	openList.PriorityInsert(startRecord, startRecord.m_costSoFar);

	while (!openList.Empty())
	{
		currRecord = openList.GetNext();

		if (currRecord.m_node == i_goal)
		{
			break;
		}

		currEdges = i_graph.GetOutgoingEdges(currRecord.m_node);

		for (DirectedWeightedEdge edge : currEdges)
		{
			int sinkNode = edge.GetSink();

			int sinkNodeCost = currRecord.m_costSoFar + edge.GetCost();
			
			NodeRecord sinkRecord;

			if (closedList.Contains(sinkNode))
			{
				continue;
			}
			else if (openList.Contains(sinkNode))
			{
				sinkRecord = openList.Find(sinkNode);

				if (sinkRecord.m_costSoFar <= sinkNodeCost)
				{
					continue;
				}
			}
			else
			{
				sinkRecord.m_node = sinkNode;
			}

			sinkRecord.m_costSoFar = sinkNodeCost;
			sinkRecord.m_incomingEdge = edge;

			if(!openList.Contains(sinkNode))
			{
				openList.PriorityInsert(sinkRecord,sinkRecord.m_costSoFar);
			}
		}		
	}

	closedList.PriorityInsert(currRecord, currRecord.m_costSoFar);

	if (currRecord.m_node != i_goal)
	{
		return std::vector<DirectedWeightedEdge>();
	}

	std::vector<DirectedWeightedEdge> path;

	while (currRecord.m_node != i_start)
	{
		if (path.empty)
		{
			path.push_back(currRecord.m_incomingEdge);
		}
		else
		{
			path.insert(path.begin, currRecord.m_incomingEdge);
		}

		currRecord = currRecord.m_incomingEdge.GetSource();
	}

	return path;
}
