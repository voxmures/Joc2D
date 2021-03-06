#ifndef _GRID_INCLUDE
#define _GRID_INCLUDE

#include<utility>			// std::pair
#include<vector>			// std::vector
#include<queue>				// std::queue
#include<unordered_map>		// std::unordered_map
#include<algorithm>			// std:find

#include "Hex.h"

const int N = 12;
const int MAX_BALLS_PER_ROW = 8;

class Grid
{
public:
	Grid();
	Grid(std::vector<Bubble*> &map);

	bool isOccupiedHex(int r, int q);
	glm::vec2 getHexCoord(glm::vec2& position);
	bool isValidHex(glm::vec2 coord);
	glm::vec2 getHexCentre(int r, int q);
	void assignBubble(int r, int q, Bubble* b);

	void setMarginTop(float margin) {
		m_margin = margin;
	}

	void testGrid();

	static bool loadLevel(const string &levelFile, vector<Bubble*> &map, vector<Bubble*> &bubbles, ShaderProgram &shaderProgram);

private:
	std::vector< std::vector<Hex *> > hexagons;

	Hex* getNeighbour(Hex* hex, int direction);
	//bool hasTop(Hex* current, std::unordered_map<Hex*, bool>& visited);
	std::vector<Hex*> BFS(Hex* start);
	std::vector<Hex*> findNonFloating(std::vector<Hex*> top);
	glm::vec2 pixelToHexCoord(glm::vec2& position);

	float m_margin;

};

#endif //_GRID_INCLUDE