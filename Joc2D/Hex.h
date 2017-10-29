#ifndef _HEX_INCLUDE
#define _HEX_INCLUDE

#include<utility> // std::pair

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

#endif // _HEX_INCLUDE