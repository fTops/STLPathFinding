#pragma once
#include <queue>
#include <stack>
#include "Node.h"

extern std::stack<int> reconstructedPath;

class OpenSet {
	// So that we have a min priority queue based on the fCost
	struct compare {
		bool operator()(Node* l, Node* r) {
			return l->m_fCost > r->m_fCost;
		}
	};

	std::priority_queue<Node *, std::vector<Node *>, compare> m_set;

public:
	OpenSet();
	~OpenSet();

	void addToSet(Node *node);
	bool isSetEmpty() const;
	Node* findNodeWithMinFCost(int &curX, int &curY, int &curGCost) const;
	void removeNodeWithMinFCost();
};

class ClosedSet {
	std::deque<Node *> m_set;

public:
	ClosedSet();
	~ClosedSet();

	void addToSet(Node *node);
	int reconstructPath(const int nTargetX, const int nTargetY, const int nMapWidth, int *pOutBuffer, const int nOutBufferSize);
};

int convert2DTo1D(const int x, const int y, const int nMapWidth);