#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BubbleLauncher.h"
#include "Game.h"
#include "Bubble.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void BubbleLauncher::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, Callback cb)
{
	this->shaderProgram = shaderProgram;

	srand(time(NULL));

	machine_spritesheet.loadFromFile("images/machine.png", TEXTURE_PIXEL_FORMAT_RGBA);

	m_cb = cb;

	arrow_sprite = PowerSprite::createSprite(glm::ivec2(128,64) , glm::vec2(1/12.f,0.5), &machine_spritesheet, &shaderProgram);
	arrow_sprite->setNumberAnimations(1);
	arrow_sprite->setAnimationSpeed(0, 8);
	arrow_sprite->addKeyframe(0, glm::vec2(0.0f,0.f));
	arrow_sprite->changeAnimation(0);
	arrow_sprite->setPosition(glm::vec2(ARROW_X,ARROW_Y));
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

	primary_bubble = new Bubble;
	Bubble::Color c = Bubble::Color(rand() % BubbleColors);
	primary_bubble->init(c, shaderProgram, false);
	//primary_bubble->setPosition(glm::vec2(ARROW_X,ARROW_Y-9));	
	primary_bubble->setPosition(glm::vec2(ARROW_X,ARROW_Y));

	secondary_bubble = new Bubble;
	Bubble::Color c2 = Bubble::Color(rand() % BubbleColors);
	secondary_bubble->init(c2, shaderProgram, false);
	secondary_bubble->setPosition(glm::vec2(ARROW_X-45,ARROW_Y+45));
}

void BubbleLauncher::update(int deltaTime)
{

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
	else if(Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		if (launched_bubble == NULL) {
			float bubX = cos(arrowAngle*M_PI/180)*-4;
			float bubY = sin(arrowAngle*M_PI/180)*-4;
			launched_bubble = primary_bubble;
			primary_bubble = secondary_bubble;
			primary_bubble->setPosition(glm::vec2(ARROW_X,ARROW_Y));

			secondary_bubble = new Bubble;
			Bubble::Color c = Bubble::Color(rand() % BubbleColors);
			secondary_bubble->init(c,shaderProgram, false);
			secondary_bubble->setPosition(glm::vec2(ARROW_X-45,ARROW_Y+45));
			
			launched_bubble->launch(glm::vec2(bubX,bubY));
			m_cb(launched_bubble);
		}
	}

	if (launched_bubble != NULL) {	// check hook
		if (launched_bubble->isHooked()) {
			launched_bubble = NULL;
		}
	}

	arrow_sprite->setRotation(arrowAngle);
}

void BubbleLauncher::render()
{
	arrow_sprite->render();
	primary_bubble->render();
	secondary_bubble->render();
	//if ( launched_bubble != NULL ){
	//	launched_bubble->render();
	//}
}
