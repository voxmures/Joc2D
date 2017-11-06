#ifndef _HEX_INCLUDE
#define _HEX_INCLUDE

#include<utility> // std::pair
#include "Bubble.h"

#define SCREEN_WIDTH 640

class Hex
{
public:
	Hex(int r, int q) : m_r(r), m_q(q), m_bubble(NULL) {}
	Hex(int r, int q, Bubble* b) : m_r(r), m_q(q), m_bubble(b) {
		if (b != NULL) {
			float radius = b->getRadius();
			float marginLeft = /*SCREEN_WIDTH - (8 * radius) / 2*/ 208.f;
			if (r % 2 != 0)
				marginLeft += radius / 2;
			float x = marginLeft + (q + r / 2) * radius,
				y = 42.f + r * radius;
			b->setPosition(glm::vec2(x, y));
		}
	}

	std::pair<int, int> getCoord() {
		return std::pair<int, int>(m_r, m_q);
	}

	std::pair<int, int> getNeighbourCoord(int direction)
	{
		std::pair<int, int> result(m_r, m_q);
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
		if (m_bubble != NULL) {
			return m_bubble->getValue();
		}
		return -1;
	}

	void hookBubble(Bubble* b) {
		m_bubble = b;
	}

	Bubble* removeBubble() {
		Bubble* result = m_bubble;
		m_bubble = NULL;
		return result;
	}

private:
	const int m_r, m_q;

	Bubble* m_bubble;
};

#endif // _HEX_INCLUDE