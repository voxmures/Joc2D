#ifndef _BUBBLE_INCLUDE
#define _BUBBLE_INCLUDE

#include <utility>      // std::pair, std::make_pair
#include "Sprite.h"
#include "Texture.h"



enum Color { Blue, Dark, Green, Orange, Purple, Red, White, Yellow, NoColor };

class Bubble {


    static Texture textures[8];

    public:

        enum Color { Blue, Dark, Green, Orange, Purple, Red, White, Yellow, NoColor };
        enum BubbleState {Active, Shading, Exploding, Dead};
        void init(Color color, ShaderProgram &shaderProgram);
        //void init(int color, ShaderProgram &shaderProgram);

        static void load_textures();

        void update(int deltaTime);
        void render();
        
        void setPosition(const glm::vec2 &pos);

        void launch(const glm::vec2 &dir);




    private:

        Color color;
        //pair <int,int> position;
        glm::vec2 position;
        glm::vec2 direction;
        Sprite *sprite;
        
        
};

#endif // _BUBBLE_INCLUDE