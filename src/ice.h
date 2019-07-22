#include "main.h"

#ifndef ICE_H
#define ICE_H


class Ice {
public:
    Ice() {}
    Ice(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed_x;
    double speed_y;
    bool exist;
private:
    VAO *object;
};

#endif // BALL_H
