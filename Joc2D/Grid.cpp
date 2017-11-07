#define _USE_MATH_DEFINES
#include <cmath>

#include "Grid.h"
#include "Game.h"

#include<iostream>
#include<fstream>
#include<sstream>

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

bool Grid::isOccupiedHex(int r, int q) {
	return hexagons[r][(N / 2 - 1) + q]->getValue() != -1;
}

glm::vec2& Grid::getHexCoord(glm::vec2& position) {
	return pixelToHexCoord(position);
}

bool Grid::isValidHex(glm::vec2& coord) {
	int r = (int)coord.x,
		q = (int)coord.y;
	if (r >= 0 && r <= 11 && q >= -5 && q <= 7) {
		if (q < -(r / 2))
			return false;

		bool rowIsOdd = (r % 2 != 0);
		if (!rowIsOdd && q < -(r / 2) + 8)
			return true;
		else if (rowIsOdd && q < -(r / 2) + 7)
			return true;
	}
	return false;
}

glm::vec2& Grid::getHexCentre(int r, int q) {
	glm::vec2 result;
	float marginLeft = 208.f;
	if (r % 2 != 0)
		marginLeft += 32.f / 2;
	result.x = marginLeft + (q + r / 2) * 32.f;
	result.y = 42.f + r * 32.f;

	return result;
}

void Grid::assignBubble(int r, int q, Bubble* b) {
	hexagons[r][(N / 2 - 1) + q]->hookBubble(b);
	Hex* target = hexagons[r][(N / 2 - 1) + q];
	vector<Hex*> conn = BFS(target);
	if (conn.size() >= 3) {

		// Remove bubbles
		for (unsigned int i = 0; i < conn.size(); i++) {
			Bubble* b = conn[i]->removeBubble();
			Game::instance().getScene().removeBubble(b);
		}

		// Find non floating bubbles
		std::vector<Hex*> top;
		for (unsigned int i = 0; i < 8; i++) {
			Hex* h = hexagons[0][(N / 2 - 1) + i];
			if (h != NULL && h->getValue() != -1) {
				top.push_back(h);
			}
		}
		std::vector<Hex*> nonFloatingBubbles = findNonFloating(top);

		// Remove floating
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= N; j++) {
				Hex* h = hexagons[i][j];
				if (h != NULL) {
					if (std::find(nonFloatingBubbles.begin(), nonFloatingBubbles.end(), h) == nonFloatingBubbles.end() &&
						h->getValue() != -1) {
						Bubble* b = h->removeBubble();
						Game::instance().getScene().removeBubble(b);
					}
				}
			}
		}
	}
}


glm::vec2& Grid::pixelToHexCoord(glm::vec2& position) {
	float w = 32.f;
	float radius = 32.f / 2;
	float x = position.x,
		y = position.y;

	x -= 208.f - radius;
	y -= 42.f - radius;
	int row = (int)(y / (w /** 3 / 4*/));
	int col;

	if (row % 2 == 0) {
		col = (int)(x / w);
	}
	else {
		col = (int)((x - radius) / w);
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
std::vector<Hex*> Grid::findNonFloating(std::vector<Hex*> top) {

	std::vector<Hex*> visited;
	std::queue<Hex*> frontier;
	for (unsigned int i = 0; i < top.size(); i++) {
		if (std::find(visited.begin(), visited.end(), top[i]) == visited.end()) {
			frontier.push(top[i]);
			visited.push_back(top[i]);

			while (!frontier.empty()) {
				Hex* current = frontier.front(); frontier.pop();

				for (unsigned int j = 0; j < 6; j++) {
					Hex* n = getNeighbour(current, j);
					bool v = std::find(visited.begin(), visited.end(), n) != visited.end();

					if (n != NULL && !v && n->getValue() != -1) {
						frontier.push(n);
						visited.push_back(n);
					}
				}
			}
		}
	}

	return visited;
}

std::vector<Hex*> Grid::BFS(Hex* start) {
	std::queue<Hex*> frontier;
	std::vector<Hex*> visited;
	visited.push_back(start);

	frontier.push(start);
	while (!frontier.empty()) {
		Hex* current = frontier.front(); frontier.pop();
		int value = current->getValue();

		for (int i = 0; i < 6; i++) {
			Hex* neighbour = getNeighbour(current, i);
			bool v = std::find(visited.begin(), visited.end(), neighbour) != visited.end();

			if (neighbour != NULL && !v && neighbour->getValue() == value) {
				frontier.push(neighbour);
				visited.push_back(neighbour);
			}
		}
	}

	return visited;
}

bool Grid::loadLevel(const string &levelFile, vector<Bubble*> &map, vector<Bubble*> &bubbles, ShaderProgram &shaderProgram){
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char bubble;
	int rows;
	
	fin.open(levelFile.c_str());
	if(!fin.is_open())
		return false;
	getline(fin, line);
	if(line.compare(0, 9, "BOBBLEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> rows;
	
	//std::vector<Bubble*> map;
	map.clear();
	bubbles.clear();

	for(int j=0; j<rows; j++)
	{
		int col = ( j%2==0 ? 8 : 7 );
		getline(fin, line);
		for(int i=0; i<col; i++)
		{
			bubble = line[i];
			if(bubble >= '0' && bubble <= '9'){
				int b = bubble - '0';
				Bubble* b_obj = new Bubble();
				Bubble::Color c;
				switch (b) {
				case 0:
					c = Bubble::Color::Blue; break;
				case 1:
					c = Bubble::Color::Dark; break;
				case 2:
					c = Bubble::Color::Green; break;
				case 3:
					c = Bubble::Color::Orange; break;
				case 4:
					c = Bubble::Color::Purple; break;
				case 5:
					c = Bubble::Color::Red; break;
				case 6:
					c = Bubble::Color::White; break;
				case 7:
					c = Bubble::Color::Yellow; break;
			}
				b_obj->init(c, shaderProgram, true);
				map.push_back(b_obj);
				bubbles.push_back(b_obj);
			}
			else map.push_back(NULL);
		}
	}
	fin.close();

	return true;
}