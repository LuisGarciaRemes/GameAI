#include "SearchAlgorithms.h"

std::vector<int> SearchAlgorithms::Dijkstra(DirectedGraph* i_graph, int i_start, int i_goal)
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

	//Search through while open list is not empty or until goal is found
	while (!openList.Empty())
	{
		currRecord = openList.GetNext();

		if (currRecord.m_node == i_goal)
		{
			break;
		}

		currEdges = i_graph->GetOutgoingEdges(currRecord.m_node);

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
					//do nothing and put it back
					openList.PriorityInsert(sinkRecord, sinkRecord.m_costSoFar);
					continue;
				}
			}
			else
			{
				sinkRecord.m_node = sinkNode;
			}

			sinkRecord.m_costSoFar = sinkNodeCost;
			sinkRecord.m_incomingEdge = edge;
			openList.PriorityInsert(sinkRecord,sinkRecord.m_costSoFar);
		}		

		//put the last checked node into the closed list
		closedList.PriorityInsert(currRecord, currRecord.m_costSoFar);
	}

	//if goal not found return empty path
	if (currRecord.m_node != i_goal)
	{
		return std::vector<int>();
	}

	//Traverse and generate path
	std::vector<int> path;

	while (currRecord.m_node != i_start)
	{
		if (path.empty())
		{
			path.push_back(currRecord.m_node);
		}
		else
		{
			path.insert(path.begin(), currRecord.m_node);
		}

		currRecord = closedList.Find(currRecord.m_incomingEdge.GetSource());
	}

	//return path
	return path;
}

std::vector<int> SearchAlgorithms::RandomAStar(DirectedGraph * i_graph, int i_start, int i_goal, int i_seed)
{
	srand(i_seed);

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

	//Search through while open list is not empty or until goal is found
	while (!openList.Empty())
	{
		currRecord = openList.GetNext();

		if (currRecord.m_node == i_goal)
		{
			break;
		}

		currEdges = i_graph->GetOutgoingEdges(currRecord.m_node);

		for (DirectedWeightedEdge edge : currEdges)
		{
			int sinkNode = edge.GetSink();

			int sinkNodeCost = currRecord.m_costSoFar + edge.GetCost() + (rand() % 500);

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
					//do nothing and put it back
					openList.PriorityInsert(sinkRecord, sinkRecord.m_costSoFar);
					continue;
				}
			}
			else
			{
				sinkRecord.m_node = sinkNode;
			}

			sinkRecord.m_costSoFar = sinkNodeCost;
			sinkRecord.m_incomingEdge = edge;
			openList.PriorityInsert(sinkRecord, sinkRecord.m_costSoFar);
		}

		//put the last checked node into the closed list
		closedList.PriorityInsert(currRecord, currRecord.m_costSoFar);
	}

	//if goal not found return empty path
	if (currRecord.m_node != i_goal)
	{
		return std::vector<int>();
	}

	//Traverse and generate path
	std::vector<int> path;

	while (currRecord.m_node != i_start)
	{
		if (path.empty())
		{
			path.push_back(currRecord.m_node);
		}
		else
		{
			path.insert(path.begin(), currRecord.m_node);
		}

		currRecord = closedList.Find(currRecord.m_incomingEdge.GetSource());
	}

	//return path
	return path;
}
