#ifndef _HEX_INCLUDE
#define _HEX_INCLUDE

#include<utility> // std::pair
#include "Hex.h"
#include "Bubble.h"

#define SCREEN_WIDTH 640

Hex::Hex(int r, int q, Bubble* b) : m_r(r), m_q(q), m_bubble(b) {
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

std::pair<int, int> Hex::getCoord() {
	return std::pair<int, int>(m_r, m_q);
}

std::pair<int, int> Hex::getNeighbourCoord(int direction)
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

int Hex::getValue() {
	if (m_bubble != NULL) {
		return m_bubble->getValue();
	}
	return -1;
}

void Hex::hookBubble(Bubble* b) {
	m_bubble = b;
}

Bubble* Hex::removeBubble() {
	Bubble* result = m_bubble;
	m_bubble = NULL;
	return result;
}

#endif // _HEX_INCLUDE