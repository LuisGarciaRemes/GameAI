#include "DirectedWeightedEdge.h"

DirectedWeightedEdge::DirectedWeightedEdge(int i_source, int i_sink, float i_cost)
{
	m_source = i_source;
	m_sink = i_sink;
	m_cost = i_cost;
}

DirectedWeightedEdge::DirectedWeightedEdge()
{
	m_source = 0;
	m_sink = 0;
	m_cost = 0.0f;
}

DirectedWeightedEdge::~DirectedWeightedEdge()
{
}

float DirectedWeightedEdge::GetCost()
{
	return m_cost;
}

int DirectedWeightedEdge::GetSource()
{
	return m_source;
}

int DirectedWeightedEdge::GetSink()
{
	return m_sink;
}
