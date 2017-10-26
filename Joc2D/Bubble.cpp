#include "Bubble.h"


Texture Bubble::textures[8] = {};

void Bubble::init(Bubble::Color color, ShaderProgram &shaderProgram){
    this->color = color;
    sprite = Sprite::createSprite(glm::vec2(32,32), glm::vec2(1/6.f,1/4.f), &Bubble::textures[color], &shaderProgram);
    sprite->setNumberAnimations(4);
    sprite->setAnimationSpeed(Active, 4);
    sprite->addKeyframe(Active, glm::vec2(0.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(1/6.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(2/6.f,0.f));
    sprite->changeAnimation(Active);
}

void Bubble::update(int deltaTime){
    //sprite->update(deltaTime);

    
    glm::vec2 newPos = position + direction;
    //194 447 sin contar bola
    //202 439 contando bola
    if (newPos.x <= 202 or newPos.x >= 439){
        direction.x *= -1;
        position += direction;
    }
    else{
        position = newPos;
    }

    sprite->setPosition(position);

}
void Bubble::render(){
    sprite->render();
}

void Bubble::load_textures(){
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
    direction = dir;
}