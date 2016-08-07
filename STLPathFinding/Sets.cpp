#include "stdafx.h"
#include "Sets.h"

OpenSet::OpenSet() {}

OpenSet::~OpenSet() {
	while(!isSetEmpty()) {
		Node *ptr = m_set.top();
		delete ptr;
		m_set.pop();
	}
}

void OpenSet::addToSet(Node *node) {
	m_set.push(node);
}

bool OpenSet::isSetEmpty() const {
	return m_set.empty();
}

// Returns a pointer to the node with the lowest fCost
// Also curX, curY, curGCost take the respective properties of the node
Node* OpenSet::findNodeWithMinFCost(int &curX, int &curY, int &curGCost) const {
	
	Node *ptr = m_set.top();

	curX = ptr->m_X;
	curY = ptr->m_Y;
	curGCost = ptr->m_gCost;

	return ptr;
}

void OpenSet::removeNodeWithMinFCost() {
	m_set.pop();
}

ClosedSet::ClosedSet() {}

ClosedSet::~ClosedSet() {
	std::deque<Node *>::const_iterator it;
	it = m_set.begin();

	Node *ptr;

	while (it != m_set.end()) {
		ptr = *it;
		delete ptr;
		++it;
	}
}

void ClosedSet::addToSet(Node *node) {
	m_set.push_front(node);
}

// Follows the path from the last node inserted (which is the target) to the first (the start)
// Saves the path to pOutBuffer
// Returns its length
int ClosedSet::reconstructPath(const int nTargetX, const int nTargetY, const int nMapWidth, int *pOutBuffer, const int nOutBufferSize) {

	std::deque<Node *>::const_iterator it;
	it = m_set.begin();

	int searchX = nTargetX;
	int searchY = nTargetY;

	while (it != m_set.end()) {

		Node *ptr;
		ptr = *it;

		if (ptr->m_X == searchX && ptr->m_Y == searchY) {
			reconstructedPath.push(convert2DTo1D(searchX, searchY, nMapWidth));
			searchX = ptr->m_fromX;
			searchY = ptr->m_fromY;
		}

		++it;
	}

	int index = 0;

	reconstructedPath.pop();

	if (reconstructedPath.size() > nOutBufferSize) {
		return -2;
	}

	else {
		while (!reconstructedPath.empty()) {
			pOutBuffer[index] = reconstructedPath.top();
			reconstructedPath.pop();
			++index;
		}
	}

	return index;
}

// Converts the coordinates given of a 2D grid (x, y) to those of a 1D array
int convert2DTo1D(const int x, const int y, const int nMapWidth) {
	return (y * nMapWidth) + x;
}
