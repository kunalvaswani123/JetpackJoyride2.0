#include "main.h"

#ifndef BEAM_H
#define BEAM_H


class Beam {
public:
    Beam() {}
    Beam(float x, float y, double rand_y, color_t color);
    glm::vec3 position;
    float rotation;
    double size;
    double count;
    double rand_y;
    bool flag;
    int move;
    color_t color;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
