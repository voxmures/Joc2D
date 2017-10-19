#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BubbleLauncher.h"
#include "Game.h"


void BubbleLauncher::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{


	machine_spritesheet.loadFromFile("images/machine.png", TEXTURE_PIXEL_FORMAT_RGBA);

	arrow_sprite = PowerSprite::createSprite(glm::ivec2(64,32) , glm::vec2(1/12.f,0.5), &machine_spritesheet, &shaderProgram);
	arrow_sprite->setNumberAnimations(1);
	arrow_sprite->setAnimationSpeed(0, 8);
	arrow_sprite->addKeyframe(0, glm::vec2(0.0f,0.f));
	arrow_sprite->changeAnimation(0);
	arrow_sprite->setPosition(glm::vec2(208,300));
	arrowAngle = 90;
	arrow_sprite->setRotation(arrowAngle);

	machine_sprite = PowerSprite::createSprite(glm::ivec2(64,32) , glm::vec2(1/12.f,0.5), &machine_spritesheet, &shaderProgram);
	machine_sprite->setNumberAnimations(1);
		machine_sprite->setAnimationSpeed(0, 8);
		machine_sprite->addKeyframe(0, glm::vec2(0/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(1/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(2/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(3/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(4/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(5/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(6/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(7/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(8/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(9/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(10/12.f,0.5f));
		machine_sprite->addKeyframe(0, glm::vec2(11/12.f,0.5f));

	machine_sprite->changeAnimation(0);
	machine_sprite->setPosition(glm::vec2(208,300));





}

void BubbleLauncher::update(int deltaTime)
{
	//sprite->update(deltaTime);
	arrow_sprite->update(deltaTime);
	machine_sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		arrowAngle-=2;
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		arrowAngle+=2;
	}

	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	//arrow_sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	arrow_sprite->setRotation(arrowAngle);
}

void BubbleLauncher::render()
{
	//sprite->render();
	machine_sprite->render();
	arrow_sprite->render();
}
