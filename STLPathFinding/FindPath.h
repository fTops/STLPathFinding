#pragma once
#include "Sets.h"

int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize);

void putDiscoveredNodeInOpenSet(const int curX, const int curY, const int curGCost,
	const int discoveredNodeX, const int discoveredNodeY, const int nTargetX, const int nTargetY,
	OpenSet &openSet, int *alreadyPutInClosedSet, const int nMapWidth);