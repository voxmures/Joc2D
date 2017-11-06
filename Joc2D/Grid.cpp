#define _USE_MATH_DEFINES
#include <cmath>

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

//void Grid::checkLaunch(Bubble* bubble, float angle)
//{
//	Hex* prev = NULL;
//	glm::vec2 position = *bubble->getPosition();
//
//	bool factor = true;
//	bool found = false;
//	while (!found) {
//		position.x += cos(angle*M_PI / 180) * 32 * (factor ? -1 : 1);
//		if (position.x < 202) {
//			position.x += (202 - position.x);
//			factor = !factor;
//		}
//		else if (position.x > 439) {
//			position.x -= (position.x - 439);
//			factor = !factor;
//		}
//
//		position.y += sin(angle*M_PI / 180) * -24;
//		if (position.y <= 42.f) {
//			found = true;
//			continue;
//		}
//
//		Hex* current = coordToHex(position);
//		if (current != NULL && current->getValue() != -1) {
//			found = true;
//			continue;
//		}
//
//		if (current != NULL)
//			prev = current;
//	}
//	prev->hookBubble(bubble);
//}

bool Grid::isOccupiedHex(int r, int q) {
	return hexagons[r][(N / 2 - 1) + q]->getValue() != -1;
}

glm::vec2& Grid::getHexCoord(glm::vec2& position) {
	return pixelToHexCoord(position);
}

bool Grid::isValidHex(glm::vec2& coord) {
	int r = coord.x,
		q = coord.y;
	if (r >= 0 && r <= 11 && q >= -5 && q <= 7) {
		if (q < -(r / 2))
			return false;

		bool rowIsOdd = (r % 2 != 0);
		if (!rowIsOdd && q < -(r / 2) + 7)
			return true;
		else if (rowIsOdd && q < -(r / 2) + 8)
			return true;
	}
	return false;
}

glm::vec2& Grid::getHexCentre(int r, int q) {
	glm::vec2 result;
	result.x = 208.f + (q + r / 2) * 32.f;
	if (r % 2 != 0)
		result.x += 32.f / 2;
	result.y = 42.f + /*32.f / 2 +*/ r * 32.f;

	return result;
}

glm::vec2& Grid::pixelToHexCoord(glm::vec2& position) {
	float w = 32.f;
	float radius = 32.f / 2;
	float x = position.x,
		y = position.y;

	x -= 208.f - radius;
	y -= 42.f - radius;
	int row = (int)(y / (w * 3 / 4));
	int col;

	if (row % 2 == 0) {
		col = (int)(x / w);
	}
	else {
		col = (int)((x - radius) / w);
	}

	float relY = y - (row * (w * 3 / 4));
	float relX;

	if (row % 2 == 0) {
		relX = x - (col * w);
	}
	else {
		relX = (x - (col * w)) - radius;
	}

	float c = radius / 2;
	float m = c / radius;
	if (relY < (-m * relX) + c) { // LEFT edge
		if (row % 2 == 0)
			col--;
		row--;
	}
	else if (relY < (m * relX) - c) { // RIGHT edge
		if (row % 2 != 0)
			col++;
		row--;
	}

	col -= row / 2;
	
	return glm::vec2(row, col);
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

