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

        static void load_textures();

        void update(int deltaTime);
	    void render();




    private:

        Color color;
        pair <int,int> position;
        Sprite *sprite;
        
        
};

#endif // _BUBBLE_INCLUDE