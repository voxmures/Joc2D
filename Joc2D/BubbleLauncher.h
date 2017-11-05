#ifndef _BUBBLELAUNCHER_INCLUDE
#define _BUBBLELAUNCHER_INCLUDE

#include "Sprite.h"
#include "PowerSprite.h"
#include "TileMap.h"
#include "Bubble.h"

//#define ARROW_X 208 
#define ARROW_X 320 
#define ARROW_Y 400


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.
typedef void(*Callback)(Bubble*, float angle);

class BubbleLauncher
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, Callback cb);
	void update(int deltaTime);
	void render();

	void setPosition(const glm::vec2 &pos);

	void freeLaunch() { launched = false; }

private:
	int jumpAngle, startY;
    float arrowAngle;
	Texture spritesheet;
    Texture machine_spritesheet;
    PowerSprite *arrow_sprite;
	PowerSprite *machine_sprite;
	PowerSprite *wheel_sprite;
	Bubble *primary_bubble;
	Sprite *sprite;
	TileMap *map;

	bool launched;

	Callback m_cb;
};


#endif // _BUBBLELAUNCHER_INCLUDE
