#ifndef _POWERSPRITE_INCLUDE
#define _POWERSPRITE_INCLUDE

#include "Sprite.h"


class PowerSprite : public Sprite
{
    public:
      static PowerSprite *createSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);
      PowerSprite(const glm::vec2 &quadSize, const glm::vec2 &sizeInSpritesheet, Texture *spritesheet, ShaderProgram *program);
      void setRotation(const float &rotation);
      void render() const;
      void update(int deltaTime);
      void setNumberAnimations(int nAnimations);
      void changeAnimation(int animId);
      void pauseAnimation();
      void resumeAnimation();
      void setAnimationDirection(int direction);
      void setFramePersistanceAnimation(int nAmin);

    private:
      float rotation;
      //glm::vec2 center_position;
      int anim_direction;
      vector<int> previous_anim_keyframe;
      bool pause;
};

#endif // _POWERSPRITE_INCLUDE
