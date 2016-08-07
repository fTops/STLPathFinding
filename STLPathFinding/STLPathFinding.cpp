#include "stdafx.h"
#include <iostream>
#include <string>
#include "FindPath.h"

std::stack<int> reconstructedPath;

// Returns 'Y' (for Yes) if the input was Y, y, yes or Yes (or any other combination of capital and lower case letters)
// Returns 'N' (for No) if the input was N, n, no or No etc
// Returns 'F' (for Failure) if the input was anything else
char validateYNInput(std::string input) {

	transform(input.begin(), input.end(), input.begin(), toupper); // make input to all CAPS

	if (input == "Y" || input == "YES")
		return 'Y';
	else if (input == "N" || input == "NO")
		return 'N';

	std::cout << "\nInvalid input, please try again\n\n";
	return 'F';
}

void printPath(int* pOutBuffer, int result, int nStartX, int nStartY, int nTargetX, int nTargetY) {
	std::cout << "The length of the shortest path between (" << nStartX << ", " << nStartY << ") and (" << nTargetX << ", " << nTargetY << ") is: " << result << std::endl;
	std::cout << "The path itself is:\n";

	for (int i = 0; i < result; ++i) {
		std::cout << pOutBuffer[i];
		if (i != result - 1)
			std::cout << " -> ";
		else
			std::cout << std::endl;
	}
}

int main() {

	unsigned char pMap[] = { 1, 1, 1, 1,
							 0, 1, 0, 1,
							 0, 1, 1, 1 };

	const int nMapWidth = 4;
	const int nMapHeight = 3;

	const int nStartX = 0;
	const int nStartY = 0;
	const int nTargetX = 1;
	const int nTargetY = 2;

	int nOutBufferSize = 3;
	int *pOutBuffer = nullptr;
	pOutBuffer = new (std::nothrow) int[nOutBufferSize];

	if (!pOutBuffer) {
		std::cerr << "Unable to allocate memory\n";
		return 0;
	}

	int result;

	if (nMapWidth >= 1 && nMapHeight >= 1 && nStartX >= 0 && nStartX < nMapWidth && nStartY >= 0 && nStartY < nMapHeight &&
		nTargetX >= 0 && nTargetX < nMapWidth && nTargetY >= 0 && nTargetY < nMapHeight &&
		pMap[convert2DTo1D(nStartX, nStartY, nMapWidth)] == 1 && pMap[convert2DTo1D(nTargetX, nTargetY, nMapWidth)] == 1
		&& nOutBufferSize >= 0) {

		result = FindPath(nStartX, nStartY, nTargetX, nTargetY, pMap, nMapWidth, nMapHeight, pOutBuffer, nOutBufferSize);
	}
	else {
		std::cout << "One or more of the parameters do not fit the constraints, change them and run it again.\n";
		delete[] pOutBuffer;
		return 0;
	}

	if (result == -1)
		std::cout << "No path exists between (" << nStartX << "," << nStartY << ") and (" << nTargetX << "," << nTargetY << ")\n";
	else if (result == -2) {
		std::cout << "The buffer size is too small to fit the complete path.\n";
		std::cout << "You need a buffer of size: " << reconstructedPath.size() << " to fit it.\n";

		std::string input;
		int choice;

		do {
			std::cout << "Increase it? (Y / N): ";

			std::getline(std::cin, input);
			choice = validateYNInput(input);
		} while (choice == 'F'); // F for failure, if the user selected anything other than Yes or No

		if (choice == 'Y') {
			int index = 0;
			nOutBufferSize = static_cast<int>(reconstructedPath.size());
			delete[] pOutBuffer;
			pOutBuffer = new (std::nothrow) int[nOutBufferSize];

			if (!pOutBuffer) {
				std::cerr << "Unable to allocate memory\n";
				return 0;
			}

			while (!reconstructedPath.empty()) {
				pOutBuffer[index] = reconstructedPath.top();
				reconstructedPath.pop();
				++index;
			}
			printPath(pOutBuffer, index, nStartX, nStartY, nTargetX, nTargetY);
		}
	}
	else if (result == -3)
		std::cerr << "Unable to allocate memory\n";

	else 
		printPath(pOutBuffer, result, nStartX, nStartY, nTargetX, nTargetY);

	delete[] pOutBuffer;
	return 0;
}