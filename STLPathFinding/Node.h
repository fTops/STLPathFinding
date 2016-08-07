#pragma once

class Node {
	int m_X;
	int m_Y;

	int m_fromX;
	int m_fromY;

	int m_gCost;
	int m_hCost;
	int m_fCost;

public:
	Node(const int discoveredNodeX, const int discoveredNodeY, const int fromX, const int fromY, const int nTargetX, const int nTargetY, const int sentGCost);
	~Node();
	void calculateHCost(const int nTargetX, const int nTargetY);
	void calculateFCost();

	friend class OpenSet;
	friend class ClosedSet;
};