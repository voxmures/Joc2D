#include "Grid.h"

#include<iostream>

Grid::Grid() {
	for (int i = 0; i < N; i++) {
		std::vector<Hex *> row;
		int padding = 5 - (i / 2);
		for (int j = 0; j <= N; j++) {
			if (j < padding || j >= (padding + MAX_BALLS_PER_ROW - (i % 2))) {
				row.push_back(NULL);
			}
			else {
				row.push_back(new Hex(i, j - padding - (i / 2)));
			}
		}
		hexagons.push_back(row);
	}
}

Grid::Grid(std::vector<Bubble*> &map) {
	unsigned int k = 0;
	for (int i = 0; i < N; i++) {
		std::vector<Hex *> row;
		int padding = (N / 2 - 1) - (i / 2);
		for (int j = 0; j <= N; j++) {
			if (j < padding || j >= (padding + MAX_BALLS_PER_ROW - (i % 2))) {
				row.push_back(NULL);
			}
			else {
				Bubble* b = (k >= map.size() ? NULL : map[k++]);
				row.push_back(new Hex(i, j - padding - (i / 2), b));
			}
		}
		hexagons.push_back(row);
	}
}

void Grid::testGrid() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= N; j++) {
			if (hexagons[i][j] != NULL) {
				std::pair<int, int> coord = hexagons[i][j]->getCoord();
				int value = hexagons[i][j]->getValue();
				std::cout << "r: " << coord.first << ", q: " << coord.second << ", v: " << value << std::endl;
			}
		}
	}

	std::cout << std::endl;

	Hex* testHex = new Hex(5, -1, 0);
	std::vector<Hex*> result = BFS(testHex);
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i]->getCoord().first << ", " << result[i]->getCoord().second << std::endl;
	}
}

Hex* Grid::getNeighbour(Hex* hex, int direction) {
	std::pair<int, int> nCoord = hex->getNeighbourCoord(direction);
	int i = nCoord.first,
		j = (N / 2 - 1) + nCoord.second;
	if (i < 0 || i > N - 1 || j < 0 || j > N)
		return NULL;

	return hexagons[i][j];
}

std::vector<Hex*> Grid::BFS(Hex* start) {
	std::queue<Hex*> frontier;
	std::vector<Hex*> visited;
	visited.push_back(start);

	frontier.push(start);
	while (!frontier.empty()) {
		Hex* current = frontier.front(); frontier.pop();
		int value = current->getValue();

		//std::cout << "CURRENT" << std::endl;
		//std::cout << "r: " << current->getCoord().first << ", q: " << current->getCoord().second << ", v: " << value << std::endl;

		//std::cout << "NEIGHBOURS" << std::endl;
		for (int i = 0; i < 6; i++) {
			Hex* neighbour = getNeighbour(current, i);
			bool v = std::find(visited.begin(), visited.end(), neighbour) != visited.end();

			if (neighbour != NULL && !v && neighbour->getValue() == value) {
				frontier.push(neighbour);
				visited.push_back(neighbour);
				//std::cout << "r: " << neighbour->getCoord().first << ", q: " << neighbour->getCoord().second << ", v: " << neighbour->getValue() << std::endl;
			}
		}
	}

	return visited;
}

