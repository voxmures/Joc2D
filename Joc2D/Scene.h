#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "BubbleLauncher.h"
#include "Bubble.h"
#include "Sprite.h"
#include "Grid.h"
#include "Text.h"

// Scene contains all the entities of our game.
// It is responsible for updating and render them.
class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	void addBubble(Bubble* b);
	void removeBubble(Bubble* b);

	void addPoints(int points);

	Grid* getGrid() {
		return grid;
	}

private:
	void initShaders();
	void changeLevel(int lvl);
	std::vector<Bubble*> loadBubbleMap();

	static void s_bubbleLaunched(Bubble* bubble);

	Sprite *background;
	Texture bg_texture;
	BubbleLauncher *bubblelauncher;

	std::vector<Bubble*> m_bubbles;

	Grid *grid;

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	int score;
	char scoreBoardBuffer[100];
	Text *scoreBoard;
	// variable to control score text being bigger when score changes.
	int scoreChanged;

	Text *levelBoard;

	int currentLvl;

	std::vector<string> levels;

	int rowOffset;
	

};


#endif // _SCENE_INCLUDE
