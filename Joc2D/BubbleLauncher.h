#ifndef _BUBBLELAUNCHER_INCLUDE
#define _BUBBLELAUNCHER_INCLUDE

#include "Sprite.h"
#include "PowerSprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class BubbleLauncher
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);

private:
	int jumpAngle, startY;
    float arrowAngle;
	Texture spritesheet;
    Texture machine_spritesheet;
    PowerSprite *arrow_sprite;
	PowerSprite *machine_sprite;
	PowerSprite *wheel_sprite;
	Sprite *sprite;
	TileMap *map;

};


#endif // _BUBBLELAUNCHER_INCLUDE
