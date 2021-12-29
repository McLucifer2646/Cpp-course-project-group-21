#pragma once

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component
{
    public:

        Vector2D position;

        TransformComponent()
        {
            position.x = 0.0f;
            position.y = 0.0f;
        }

        TransformComponent(float x, float y)
        {
            position.x = x;
            position.y = y;
        }
        
        // void init() override
        // {
        //     xpos = 0; 
        //     ypos = 0;
        // }

        void update() override
        {
            // xpos++;
            // ypos++;
        }

        // void x(int x) { xpos = x; }
        // void y(int y) { ypos = y; }
        // int x() { return xpos; }
        // int y() { return ypos; }

        // void setPos(int x, int y) { xpos = x; ypos = y; }
};