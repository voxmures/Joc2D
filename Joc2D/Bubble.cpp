#include "Bubble.h"


Texture Bubble::textures[8] = {};

void Bubble::init(Bubble::Color color, ShaderProgram &shaderProgram){
    this->color = color;
    sprite = Sprite::createSprite(glm::vec2(32,32), glm::vec2(1/6.f,1/4.f), &Bubble::textures[color], &shaderProgram);
    sprite->setNumberAnimations(4);
    sprite->setAnimationSpeed(Active, 8);
    sprite->addKeyframe(Active, glm::vec2(0.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(1/6.f,0.f));
    sprite->addKeyframe(Active, glm::vec2(2/6.f,0.f));
    sprite->changeAnimation(Active);
    sprite->setPosition(glm::vec2(100,100));
}

void Bubble::update(int deltaTime){

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