#include "water.h"
#include "main.h"
#include <cmath>
const int L = 1e5 + 5;

Water::Water(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->exist = true;
    speed_x = 0;
    speed_y = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[L];
    int i, n = 300;
    for (i = 0; i < n; i++)
    {
        vertex_buffer_data[9 * i] = 0.0f;
        vertex_buffer_data[9 * i + 1] = 0.0f;
        vertex_buffer_data[9 * i + 2] = 2.0f;

        vertex_buffer_data[9 * i + 3] = 0.5 * (double)cos((2 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 4] = 0.5 * (double)sin((2 * M_PI * i)/n);
        vertex_buffer_data[9 * i + 5] = 2.0f;
        
        vertex_buffer_data[9 * i + 6] = 0.5 * (double)cos((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 7] = 0.5 * (double)sin((2 * M_PI * (i + 1))/n);
        vertex_buffer_data[9 * i + 8] = 2.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n * 3, vertex_buffer_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
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

void Water::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Water::tick() {
    this->position.x += speed_x / 60;
    this->position.y += speed_y / 60 - (double)10 / (60 * 60);
    speed_y -= (double)20 / 60; 
}
