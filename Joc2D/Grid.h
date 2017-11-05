#ifndef _GRID_INCLUDE
#define _GRID_INCLUDE

#include<utility>			// std::pair
#include<vector>			// std::vector
#include<queue>				// std::queue
#include<unordered_map>		// std::unordered_map

#include "Hex.h"

const int N = 12;
const int MAX_BALLS_PER_ROW = 8;

class Grid
{
public:
	Grid();
	Grid(std::vector<Bubble*> &map);

	void checkLaunch(Bubble* bubble, float angle);

	void testGrid();

private:
	std::vector< std::vector<Hex *> > hexagons;

	Hex* getNeighbour(Hex* hex, int direction);
	std::vector<Hex*> BFS(Hex* start);

	Hex* coordToHex(glm::vec2& position);

};

#endif //_GRID_INCLUDE