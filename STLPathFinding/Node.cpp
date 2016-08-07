#include "stdafx.h"
#include <iostream>
#include "Node.h"

// Constructor for Node. The gCost of the node is the gCost of the node we came from + 1
Node::Node(const int discoveredNodeX, const int discoveredNodeY, const int fromX, const int fromY, const int nTargetX, const int nTargetY, const int sentGCost) : m_X{ discoveredNodeX }, m_Y{ discoveredNodeY }, m_fromX{ fromX }, m_fromY{ fromY }, m_gCost { sentGCost + 1 } {
	calculateHCost(nTargetX, nTargetY);
	calculateFCost();
}

Node::~Node() {}

// Calculates the Manhattan distance between the node and the target
void Node::calculateHCost(const int nTargetX, const int nTargetY) {
	m_hCost = abs(m_X - nTargetX) + abs(m_Y - nTargetY);
}

void Node::calculateFCost() {
	m_fCost = m_gCost + m_hCost;
}
