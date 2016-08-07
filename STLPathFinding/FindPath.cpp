#include "stdafx.h"
#include "Sets.h"

// If the discovered node is not already evaluated in the Closed Set
// ..add it to the Open Set for evaluation
// Return 0 for success
// or -1 for failure to allocate memory
int putDiscoveredNodeInOpenSet(const int curX, const int curY, const int curGCost,
	const int discoveredNodeX, const int discoveredNodeY, const int nTargetX, const int nTargetY,
	OpenSet &openSet, int *alreadyPutInClosedSet, const int nMapWidth) {

	if (alreadyPutInClosedSet[convert2DTo1D(discoveredNodeX, discoveredNodeY, nMapWidth)] == 0) {

		Node *pos = new (std::nothrow) Node{ discoveredNodeX, discoveredNodeY, curX, curY, nTargetX, nTargetY, curGCost };

		if (!pos)
			return -1;

		openSet.addToSet(pos);
	}
	return 0;
}

// Given a starting position, the target, a grid, its dimensions, a buffer to save the nodes of the shortest path and a size for the buffer..
// ..return the length of the shortest path between the starting position and the target
// or -1 if there's no such path
// or -2 if the path does not fit in the buffer
int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {

	ClosedSet closedSet; // Contains the nodes already evaluated
	OpenSet openSet; // Contain the discovered nodes that haven't been evaluated yet

	// Contains an indication whether a node has already been evaluated
	int *alreadyPutInClosedSet = new (std::nothrow) int[nMapWidth*nMapHeight]{};

	if (!alreadyPutInClosedSet) {
		return -3;
	}

	Node *start = new (std::nothrow) Node{ nStartX, nStartY, nStartX, nStartY, nTargetX, nTargetY, -1 };

	if (!start) {
		delete[] alreadyPutInClosedSet;
		return -3;
	}

	openSet.addToSet(start); // The starting node is pushed into the Open Set

	int curX = 0;
	int curY = 0;
	int curGCost = 0;
	Node *current;

	while (!openSet.isSetEmpty()) { // While there are still nodes for evaluation

		// current, curX, curY, curGCost will contain the info of the node with the lowest F cost in the Open Set
		current = openSet.findNodeWithMinFCost(curX, curY, curGCost);

		// if the node is not already evaluated in the Closed Set
		if (alreadyPutInClosedSet[convert2DTo1D(curX, curY, nMapWidth)] == 0) {

			// if that is our target
			if (curX == nTargetX && curY == nTargetY) {
				closedSet.addToSet(current);
				openSet.removeNodeWithMinFCost();
				int result = closedSet.reconstructPath(nTargetX, nTargetY, nMapWidth, pOutBuffer, nOutBufferSize);
				delete[] alreadyPutInClosedSet;
				return result;
			}

			// Otherwise remove the node from the Open Set, put it in the Closed Set and put an indication that we finished with that node
			closedSet.addToSet(current);
			alreadyPutInClosedSet[convert2DTo1D(curX, curY, nMapWidth)] = 1;

			openSet.removeNodeWithMinFCost();

			// Search for traversible neighbors in up, down, left, right directions..
			if (curY > 0) // If we are not at the top row..
						  // .. we can now check if we can move to the neighbor above
				if (pMap[convert2DTo1D(curX, curY, nMapWidth) - nMapWidth] == 1) { // if the neighbor above is traversible (1 instead of 0)
					int success = putDiscoveredNodeInOpenSet(curX, curY, curGCost, curX, curY - 1, nTargetX, nTargetY, openSet, alreadyPutInClosedSet, nMapWidth);
					if (success == -1) {
						delete[] alreadyPutInClosedSet;
						return -3;
					}
				}

			if (curY < nMapHeight - 1) // if we are not at the bottom row..
									   // .. we can now check if we can move to the neighbor bellow
				if (pMap[convert2DTo1D(curX, curY, nMapWidth) + nMapWidth] == 1) { // if the neighbor bellow is traversible (1 instead of 0)
					int success = putDiscoveredNodeInOpenSet(curX, curY, curGCost, curX, curY + 1, nTargetX, nTargetY, openSet, alreadyPutInClosedSet, nMapWidth);
					if (success == -1) {
						delete[] alreadyPutInClosedSet;
						return -3;
					}
				}

			if (curX > 0) // if we are not at the leftmost column..
						  // .. we can now check if we can move to the neighbor to the left
				if (pMap[convert2DTo1D(curX, curY, nMapWidth) - 1] == 1) { // if the neighbor to the left is traversible (1 instead of 0)
					int success = putDiscoveredNodeInOpenSet(curX, curY, curGCost, curX - 1, curY, nTargetX, nTargetY, openSet, alreadyPutInClosedSet, nMapWidth);
					if (success == -1) {
						delete[] alreadyPutInClosedSet;
						return -3;
					}
				}

			if (curX < nMapWidth - 1) // if we are not at the rightmost column..
									  // .. we can now check if we can move to the neighbor to the right
				if (pMap[convert2DTo1D(curX, curY, nMapWidth) + 1] == 1) { // if the neighbor to the right is traversible (1 instead of 0)
					int success = putDiscoveredNodeInOpenSet(curX, curY, curGCost, curX + 1, curY, nTargetX, nTargetY, openSet, alreadyPutInClosedSet, nMapWidth);
					if (success == -1) {
						delete[] alreadyPutInClosedSet;
						return -3;
					}
				}
		}
		// if the node is already evaluated in the Closed Set, remove it from the Open Set and skip to the next
		else
			openSet.removeNodeWithMinFCost();
	}

	delete[] alreadyPutInClosedSet;
	return -1;
}