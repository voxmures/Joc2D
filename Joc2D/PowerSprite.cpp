#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include "PowerSprite.h"


PowerSprite *PowerSprite::createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program)
{
	PowerSprite *quad = new PowerSprite(quadSize, sizeInSpritesheet, spritesheet, program);

	return quad;
}

PowerSprite::PowerSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program):
Sprite(quadSize, sizeInSpritesheet, spritesheet, program)
{
	float vertices[24] = {0.f, 0.f, 0.f, 0.f,
		quadSize.x, 0.f, sizeInSpritesheet.x, 0.f,
		quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y,
		0.f, 0.f, 0.f, 0.f,
		quadSize.x, quadSize.y, sizeInSpritesheet.x, sizeInSpritesheet.y,
		0.f, quadSize.y, 0.f, sizeInSpritesheet.y};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
		posLocation = program->bindVertexAttribute("position", 2, 4*sizeof(float), 0);
		texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4*sizeof(float), (void *)(2*sizeof(float)));
		texture = spritesheet;
		shaderProgram = program;
		currentAnimation = -1;
		position = glm::vec2(0.f);
		center_position = glm::vec2(quadSize.x/2,quadSize.y/2);
		rotation = 0;
		anim_direction = 1;
		pause = false;
	}

 void PowerSprite::update(int deltaTime)
{
	if(currentAnimation >= 0 and not pause)
	{
		timeAnimation += deltaTime;
		while(timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + anim_direction) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}


void PowerSprite::render() const
{
	//glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	modelview = glm::translate(modelview, glm::vec3(center_position.x,center_position.y,0));
	modelview = glm::rotate(modelview, rotation, glm::vec3(0,0,1));
	modelview = glm::translate(modelview, glm::vec3(-center_position.x,-center_position.y,0));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}

void PowerSprite::setNumberAnimations(int nAnimations)
{
	animations.clear();
	animations.resize(nAnimations);
	previous_anim_keyframe.clear();
	previous_anim_keyframe.assign(nAnimations,-1);
}

void PowerSprite::changeAnimation(int animId)
{
	if(animId < int(animations.size()))
	{
		if (previous_anim_keyframe[currentAnimation] != -1 ){
			previous_anim_keyframe[currentAnimation] = currentKeyframe;
		}
		currentAnimation = animId;
		if (previous_anim_keyframe[animId] != -1) {
			currentKeyframe = previous_anim_keyframe[animId];
		}
		else	currentKeyframe = 0;
		timeAnimation = 0.f;
		texCoordDispl = animations[animId].keyframeDispl[0];
	}
}

void PowerSprite::setFramePersistanceAnimation(int animId){
	if(animId < int(animations.size())) {
		previous_anim_keyframe[animId] = 0;
	}
}

void PowerSprite::setRotation(const float &angle)
{
	rotation = M_PI*angle/180;
}

void PowerSprite::pauseAnimation() {
	pause = true;
	timeAnimation = 0;
}
void PowerSprite::resumeAnimation() {
	pause = false;
}
