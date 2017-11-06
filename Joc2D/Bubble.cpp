#define _USE_MATH_DEFINES
#include <cmath>

#include "Bubble.h"

#include "Game.h"
#include <iostream>


Texture Bubble::textures[8] = {};

void Bubble::init(Bubble::Color c, ShaderProgram &shaderProgram, bool hooked){
    color = c;
	m_hooked = hooked;
    sprite = Sprite::createSprite(glm::vec2(64,64), glm::vec2(1/6.f,1/4.f), &Bubble::textures[c], &shaderProgram);
    sprite->setNumberAnimations(4);
    sprite->setAnimationSpeed(Active, 4);
    sprite->addKeyframe(Active, glm::vec2(0.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(1/6.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(2/6.f,0.f));
    sprite->changeAnimation(Active);
}

void Bubble::update(int deltaTime){
    //sprite->update(deltaTime);

	if (direction.x != 0 || direction.y != 0) {
		glm::vec2 newPos = position + direction;
		//194 447 sin contar bola
		//202 439 contando bola
		if (newPos.x <= 202 || newPos.x >= 439) {
			direction.x *= -1;
			position += direction;
		}
		else {
			position = newPos;
		}

		sprite->setPosition(position);

		std::cout << position.x << ", " << position.y << std::endl;
		//Check next hex
		Grid* g = Game::instance().getScene().getGrid();

		glm::vec2 current = g->getHexCoord(position);
		if (current != hexCoord && g->isValidHex(current)) {	// Moved to a new Hex -> Check next hex
			hexCoord = current;
			std::cout << "Hex found!" << std::endl;
			std::cout << hexCoord.x << ", " << hexCoord.y << std::endl;

			glm::vec2 c = g->getHexCentre(hexCoord.x, hexCoord.y);
			float angle = asin(direction.y / (-4)) * 180 / M_PI;
			glm::vec2 hexSizeDir;
			hexSizeDir.x = cos(angle * M_PI / 180) * 32;
			if (direction.x < 0) {
				hexSizeDir.x *= -1;
			}
			hexSizeDir.y = sin(angle * M_PI / 180) * -32;

			glm::vec2 nextP = c + hexSizeDir;
			if (nextP.x <= 202 || nextP.x >= 439) {
				hexSizeDir.x *= -1;
				nextP.x += hexSizeDir.x;
			}

			glm::vec2 next = g->getHexCoord(nextP);
			if (g->isValidHex(next) && g->isOccupiedHex(next.x, next.y)) {
				position = c;
				sprite->setPosition(position);
				direction.x = direction.y = 0;
				m_hooked = true;
				g->assignBubble(hexCoord.x, hexCoord.y, this);
			} 
		}
	}
}

void Bubble::render(){
    sprite->render();
}

int Bubble::getValue() {
	return color;
}

float Bubble::getRadius() {
	return /*sprite->getSize()*/ 64.f / 2;
}

void Bubble::load_textures() {
    Bubble::textures[Blue].loadFromFile("images/bubbles/bubble_blue_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Dark].loadFromFile("images/bubbles/bubble_dark_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Green].loadFromFile("images/bubbles/bubble_green_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Orange].loadFromFile("images/bubbles/bubble_orange_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Purple].loadFromFile("images/bubbles/bubble_purple_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Red].loadFromFile("images/bubbles/bubble_red_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[White].loadFromFile("images/bubbles/bubble_white_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
    Bubble::textures[Yellow].loadFromFile("images/bubbles/bubble_yellow_spritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

void Bubble::setPosition(const glm::vec2 &pos)
{
	position = pos;
	sprite->setPosition(pos);
}

void Bubble::launch(const glm::vec2 &dir){
	std::cout << "LAUNCH!" << std::endl;
    direction = dir;
	hexCoord = Game::instance().getScene().getGrid()->getHexCoord(position);
}