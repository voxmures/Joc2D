#define _USE_MATH_DEFINES
#include <cmath>

#include "Bubble.h"

#include "Game.h"
#include <iostream>


Texture Bubble::textures[8] = {};

void Bubble::init(Bubble::Color color, ShaderProgram &shaderProgram){
    this->color = color;
    sprite = Sprite::createSprite(glm::vec2(64,64), glm::vec2(1/6.f,1/4.f), &Bubble::textures[color], &shaderProgram);
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

		//Check next hex
		Grid* g = Game::instance().getScene().getGrid();

		glm::vec2 current = g->getHexCoord(position);
		if (current != hexCoord && g->isValidHex(current)) {	// Moved to a new Hex -> Check next hex
			hexCoord = current;
			std::cout << hexCoord.x << ", " << hexCoord.y << std::endl;

			glm::vec2 dirCopy = glm::vec2(direction);
			glm::vec2 next;
			glm::vec2 nextP = glm::vec2(position);
			bool found = false;
			while (!found) {
				nextP += dirCopy;
				if (nextP.x <= 202 || nextP.x >= 439) {
					dirCopy.x *= -1;
					nextP += dirCopy;
				}
				next = g->getHexCoord(nextP);
				if (next != hexCoord && g->isValidHex(next)) {
					found = true;
					if (g->isOccupiedHex(next.x, next.y)) {
						position = g->getHexCentre(hexCoord.x, hexCoord.y);
						direction.x = direction.y = 0.f;
					}
				}
			}
		}

		sprite->setPosition(position);
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