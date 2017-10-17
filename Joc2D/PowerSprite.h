#include "Sprite.h"


class PowerSprite : public Sprite
{

public:
  void setRotation(const float &rotation);
  void pauseAnimation();
  void resumeAnimation();
  void setAnimationDirection(int direction);
  void setFramePersistanceAnimation(int nAmin);

private:
  float rotation;
	glm::vec2 center_position;
  int anim_direction;
  vector<int> previous_anim_keyframe;
  bool pause;
}
