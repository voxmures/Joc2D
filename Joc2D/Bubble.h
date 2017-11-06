#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE

#include <utility>      // std::pair, std::make_pair
#include "Sprite.h"
#include "Texture.h"

#define BubbleColors 7



enum Color { Blue, Dark, Green, Orange, Purple, Red, White, Yellow, NoColor };

class Bubble {

    static Texture textures[8];

    public:

        enum Color { Blue, Dark, Green, Orange, Purple, Red, White, Yellow, NoColor };
        enum BubbleState {Active, Shading, Exploding, Dead};
        void init(Color c, ShaderProgram &shaderProgram, bool hooked);
        //void init(int color, ShaderProgram &shaderProgram);

        static void load_textures();

        void update(int deltaTime);
        void render();
        
        void setPosition(const glm::vec2 &pos);

        void launch(const glm::vec2 &dir);

		bool isHooked() { return m_hooked; }

		int getValue();
		float getRadius();
		glm::vec2* getPosition() {
			return &position;
		}

		glm::vec2* getDirection() {
			return &direction;
		}

    private:

        Color color;
        //pair <int,int> position;
        glm::vec2 position;
        glm::vec2 direction;
        Sprite *sprite;

		bool m_hooked;

		glm::vec2 hexCoord;
};

#endif // _BUBBLE_INCLUDE