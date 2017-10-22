#ifndef _GRID_INCLUDE
#define _GRID_INCLUDE

#include<utility>			// std::pair
#include<vector>			// std::vector
#include<queue>				// std::queue
#include<unordered_map>		// std::unordered_map

#include<iostream>

const int N = 12;

class Hex
{
public:
	Hex(int r, int q) : m_r(r), m_q(q), m_value(-1) {}
	Hex(int r, int q, int v) : m_r(r), m_q(q), m_value(v) {}

	std::pair<int, int> getCoord() {
		return std::pair<int, int>(m_r, m_q);
	}

	std::pair<int, int> getNeighbourCoord(int direction)
	{
		std::pair<int, int> result (m_r, m_q);
		switch (direction) 
		{
		case 0:	// Right neighbour
			result.second += 1;
			break;
		case 1:	// Bottom-right neighbour
			result.first += 1;
			break;
		case 2:	// Bottom-left neighbour
			result.first += 1;
			result.second -= 1;
			break;
		case 3:	// Left neighbour
			result.second -= 1;
			break;
		case 4:	// Upper-left neighbour
			result.first -= 1;
			break;
		case 5:	// Upper-right neighbour
			result.first -= 1;
			result.second += 1;
			break;
		}
		return result;
	}

	int getValue() {
		return m_value;
	}

private:
	const int m_r, m_q;

	/*	0: Red / Invader
		1: Yellow / Pulpul
		2: Green / Drunk
		3: Blue / Zen-Chan
		4: Purple / Monsta
		5: Orange / Banebou
		6: Black / Hidegonsu
		7: White / Mighta
	*/
	int m_value;		
};

class Grid
{
public:
	Grid() {
		for (int i = 0; i < N; i++) {
			std::vector<Hex *> row;
			int padding = 5 - (i / 2);
			for (int j = 0; j <= N; j++) {
				if (j < padding || j >= (padding + 8 - (i % 2))) {
					row.push_back(NULL);
				} 
				else {
					row.push_back(new Hex(i, j - padding - (i / 2)));
				}
			}
			hexagons.push_back(row);
		}
	}

	Grid(std::vector<int> &map) {
		unsigned int k = 0;
		for (int i = 0; i < N; i++) {
			std::vector<Hex *> row;
			int padding = 5 - (i / 2);
			for (int j = 0; j <= N; j++) {
				if (j < padding || j >= (padding + 8 - (i % 2))) {
					row.push_back(NULL);
				}
				else {
					int value = (k >= map.size() ? -1 : map[k++]);
					row.push_back(new Hex(i, j - padding - (i / 2), value));
				}
			}
			hexagons.push_back(row);
		}
	}

	void testGrid() {
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

		Hex* testHex = new Hex(5, -1, 1);
		checkThrow(testHex);
	}

private:
	std::vector< std::vector<Hex *> > hexagons;

	Hex* getNeighbour(Hex* hex, int direction) {
		std::pair<int, int> nCoord = hex->getNeighbourCoord(direction);
		int i = nCoord.first,
			j = (N / 2 - 1) + nCoord.second;
		if (i < 0 || i > N - 1 || j < 0 || j > N)
			return NULL;

		return hexagons[i][j];
	}

	void checkThrow(Hex* hex) {
		std::queue<Hex*> frontier;
		std::unordered_map<Hex*, Hex*> came_from;
		came_from[hex] = NULL;

		frontier.push(hex);
		while (!frontier.empty()) {
			Hex* current = frontier.front(); frontier.pop();
			int value = current->getValue();

			std::cout << "CURRENT" << std::endl;
			std::cout << "r: " << current->getCoord().first << ", q: " << current->getCoord().second << ", v: " << value << std::endl;

			std::cout << "NEIGHBOURS" << std::endl;
			for (int i = 0; i < 6; i++) {
				Hex* neighbour = getNeighbour(current, i);

				if (neighbour != NULL && came_from[current] != neighbour && neighbour->getValue() == value) {
					frontier.push(neighbour);
					came_from[neighbour] = current;
					std::cout << "r: " << neighbour->getCoord().first << ", q: " << neighbour->getCoord().second << ", v: " << neighbour->getValue() << std::endl;
				}
			}
		}
	}

};

#endif //_GRID_INCLUDE