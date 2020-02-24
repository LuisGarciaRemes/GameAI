#pragma once
class DirectedWeightedEdge
{

public:

	DirectedWeightedEdge(int i_source, int i_sink, float i_cost);
	DirectedWeightedEdge();
	~DirectedWeightedEdge();

	float GetCost();
	int GetSource();
	int GetSink();

private:

	int m_source;
	int m_sink;
	float m_cost;

};

