#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    double health;
    double flag;
    int move;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
