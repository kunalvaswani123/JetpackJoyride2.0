#include "main.h"

#ifndef SEVEN_H
#define SEVEN_H


class Seven {
public:
    Seven() {}
    Seven(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int score;
    int lives;
    int level;
private:
    VAO *object;
};

#endif // BALL_H
