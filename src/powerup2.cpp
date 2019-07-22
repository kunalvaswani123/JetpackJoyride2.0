#include "powerup2.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Powerup2::Powerup2(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        0.5f, 1.0f, 2.0f,
        -0.5f, 1.0f, 2.0f,
        0.5f, -1.0f, 2.0f,
        -0.5f, 1.0f, 2.0f,
        -0.5f, -1.0f, 2.0f,
        0.5f, -1.0f, 2.0f,
        1.0f, 0.5f, 2.0f,
        1.0f, -0.5f, 2.0f,
        -1.0f, 0.5f, 2.0f,
        -1.0f, 0.5f, 2.0f,
        -1.0f, -0.5f, 2.0f,
        1.0f, -0.5f, 2.0f
    };
    this->object = create3DObject(GL_TRIANGLES, 4 * 3, vertex_buffer_data, color, GL_FILL);
}

void Powerup2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Powerup2::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Powerup2::tick() {
    this->position.x += 0.1;
    this->position.y = 3 * (double)sin(this->position.x / 2);
}
