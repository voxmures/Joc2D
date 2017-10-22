#ifndef _GRID_INCLUDE
#define _GRID_INCLUDE

#include<utility>	// std::pair
#include<vector>	// std::vector
#include<iostream>

const int N = 12;

class Hex
{
public:
	Hex(int r, int q) : m_r(r), m_q(q), value(-1) {}

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

private:
	const int m_r, m_q;
	int value;
		
};

class Grid
{
public:
	Grid() {
		for (int i = 0; i < N; i++) {
			std::vector<Hex *> row;
			int padding = 5 - (i / 2);
			//cout << "i: " << i << endl << "padding: " << padding << endl << "i / 2: " << i / 2 << endl;
			for (int j = 0; j <= N; j++) {
				//cout << "j: " << j << " padding + 8 - (i % 2): " << padding + 8 - (i % 2);
				if (j < padding || j >= (padding + 8 - (i % 2))) {
					//cout << endl;
					row.push_back(NULL);
				} 
				else {
					//cout << " j - padding: " << j - padding << endl;
					row.push_back(new Hex(i, j - padding - (i / 2)));
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
					cout << "r: " << coord.first << ", q: " << coord.second << endl;
				}
			}
		}
	}

private:
	std::vector< std::vector<Hex *> > hexagons;

	Hex* getNeighbour(Hex* hex, int direction) {
		std::pair<int, int> neighbourCoord = hex->getNeighbourCoord(direction);
		return hexagons[neighbourCoord.first][neighbourCoord.second + neighbourCoord.first / 2];
	}

};

#endif //_GRID_INCLUDE