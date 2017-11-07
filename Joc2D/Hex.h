#ifndef _HEX_INCLUDE
#define _HEX_INCLUDE

#include<utility> // std::pair

#define SCREEN_WIDTH 640

class Hex
{
public:
  Hex(int r, int q) : m_r(r), m_q(q), m_bubble(NULL) {}
  Hex(int r, int q, Bubble *b) : m_r(r), m_q(q), m_bubble(b) {}
  //Hex(int r, int q, Bubble *b);

  std::pair<int, int> getCoord();

  std::pair<int, int> getNeighbourCoord(int direction);

  int getValue();

  void hookBubble(Bubble *b);

  Bubble *removeBubble();

private:
	const int m_r, m_q;

	Bubble* m_bubble;
};

#endif // _HEX_INCLUDE